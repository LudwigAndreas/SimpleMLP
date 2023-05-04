#ifndef SIMPLEMLP_MLPMATRIXMODEL2_HPP
#define SIMPLEMLP_MLPMATRIXMODEL2_HPP

#include <algorithm>
#include <fstream>

#include "../utils/ActivationFunction.hpp"
// #include "../../libs21/libs21.h"
#include "../utils/IMLPModel.hpp"
#include "MLPMatrixLayer.hpp"
#include "Matrix.hpp"

namespace s21 {

class MLPMatrixModel : public s21::IMLPModel {
 private:
  std::vector<size_t> units_per_layer;
  std::vector<MLPMatrixLayer*> layers;
  bool auto_decrease;

  ActivationFunction af;
  float lr;
  float start_lr;

		explicit MLPMatrixModel(std::vector<size_t> units_per_layer,
								ActivationFunction func,
								bool use_auto_decrease = true,
								float lr = .05f);

	public:
		const std::vector<size_t> &get_units_per_layer() const;

		const std::vector<MLPMatrixLayer *> &get_layers() const;

		float get_lr() const;

		const ActivationFunction &get_af() const;

		void set_units_per_layer(const std::vector<size_t> &unitsPerLayer);

		void set_layers(std::vector<MLPMatrixLayer *> l);

		void set_lr(float lr);

		void set_af(ActivationFunction &af);

		Matrix<float> NormalizedInput(Matrix<float> matrix);

		std::vector<float> Forward(Matrix<float> matrix) override;
		
		void Backward(Matrix<float> target) override;

		// float TestOutput(std::vector<s21::Sample> samples, bool silent_mode = false, std::string filename = "") override;

		int Predict(Matrix<float> x) override;

		static IMLPModel *MakeModel(size_t in_channels, size_t out_channels,
									size_t hidden_units_per_layer,
									int hidden_layers, float lr, 
									ActivationFunction func, 
									bool use_auto_decrease = true);
	};

	template <typename T>
	static std::vector< s21::Matrix<T> > readVectorMatrix(std::istream &input, size_t size) {
		std::vector<s21::Matrix<T>>	result;
		s21::Matrix<T>				matrix;

		result.reserve(size);
		for (size_t i = 0; i < size; ++i) {
			input >> matrix;
			result.push_back(matrix);
		}
		return (std::move(result));
	}

	std::istream &operator>>(std::istream &is, MLPMatrixModel &model);

	std::ostream &operator<<(std::ostream &os, const MLPMatrixModel &model);
}

#endif

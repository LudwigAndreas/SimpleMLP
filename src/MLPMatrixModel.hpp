#ifndef SIMPLEMLP_MLPMATRIXMODEL_HPP
#define SIMPLEMLP_MLPMATRIXMODEL_HPP

#include "IMLPModel.hpp"
#include "Matrix.hpp"

namespace s21 {
	template <typename T>
	class MLPMatrixModel : s21::IMLPModel {
	private:
		std::vector<size_t> units_per_layer;
		std::vector<Matrix<T>> bias_vectors;
		std::vector<Matrix<T>> weight_matrices;
		std::vector<Matrix<T>> activations;

		float lr;

		explicit MLPMatrixModel(std::vector<size_t> units_per_layer, float lr);

	public:
		MLPMatrixModel() = delete;

		MLPMatrixModel &operator=(const MLPMatrixModel<T> matrix) = delete;

		MLPMatrixModel(MLPMatrixModel<T> const &) = delete;


		const std::vector<size_t> &getUnitsPerLayer() const {
			return units_per_layer;
		}

		const std::vector<Matrix<T>> &getBiasVectors() const {
			return bias_vectors;
		}

		const std::vector<Matrix<T>> &getWeightMatrices() const {
			return weight_matrices;
		}

		const std::vector<Matrix<T>> &getActivations() const {
			return activations;
		}

		float getLr() const {
			return lr;
		}


		int Forward(Matrix<T> target) {
			return 0;
		}

		void Backward(Matrix<T> target) {
			return 0;
		}

		int Import() override {
			return 0;
		}

		int Export() override {
			return 0;
		}

		int Train() override {
			return 0;
		}

		int Test() override {
			return 0;
		}

		int Predict() override {
			return 0;
		}

		IMLPModel *MakeModel(size_t in_channels, size_t out_channels, size_t hidden_units_per_layer, int hidden_layers, float lr) override;
	};
}

#endif //SIMPLEMLP_MLPMATRIXMODEL_HPP

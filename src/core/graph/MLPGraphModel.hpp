#pragma once

#include <fstream>

#include "../utils/IMLPModel.hpp"
#include "../utils/ActivationFunction.hpp"
#include "../graph/MLPGraphLayer.hpp"

namespace s21 {
	typedef float T;

	class MLPGraphModel : public IMLPModel<T> {
	private:
		std::vector<size_t>				units_per_layer;
		std::vector<MLPGraphLayer *>	layers;
		ActivationFunction				*af;
		float							start_lr;
		float							lr;
		
		bool							auto_decrease;
		
	
	public:
		explicit MLPGraphModel(std::vector<size_t> units_per_layer,
								ActivationFunction *func,
								bool use_auto_decrease = true,
								float lr = .05f);
								
		MLPGraphLayer *AddLayer(MLPGraphLayer *layer);

		virtual std::vector<T> Forward(Matrix<T>);
		virtual void Backward(Matrix<T>);
		virtual float Train(DatasetGroup samples, bool b = false);
		virtual float Test(DatasetGroup samples, bool b = false);
		virtual int Predict(Matrix<float>);
		virtual float TestOutput(std::vector<Sample> samples, bool silent_mode = false, std::string filename = "");
	};

	std::istream &operator>>(std::istream &is, MLPGraphModel &model);
	std::ostream &operator<<(std::ostream &os, MLPGraphModel &model);
}
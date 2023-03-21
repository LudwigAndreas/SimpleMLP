#pragma once

#include "../utils/IMLPModel.hpp"
#include "../utils/ActivationFunction.hpp"
#include "../graph/MLPGraphLayer.hpp"

namespace s21 {
	typedef float T;

	class MLPGraphModel : public IMLPModel<T> {
	private:
		std::vector<size_t>				upl;
		std::vector<MLPGraphLayer *>	layers;
		ActivationFunction				*af;
	
	public:
		MLPGraphModel *AddLayer(MLPGraphLayer *layer);

		virtual std::vector<T> Forward(Matrix<T>);
		virtual void Backward(Matrix<T>);
		virtual float Train(DatasetGroup samples, bool b = false);
		virtual float Test(DatasetGroup samples, bool b = false);
		virtual int Predict(Matrix<float>);
		virtual float TestOutput(std::vector<Sample> samples, bool silent_mode = false, std::string filename = "");
	};

}
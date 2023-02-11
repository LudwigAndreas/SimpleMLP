#ifndef SIMPLEMLP_IMLPMODELBUILDER_HPP
#define SIMPLEMLP_IMLPMODELBUILDER_HPP

#include "IMLPModel.hpp"
#include "ActivationFunction.hpp"

namespace s21 {
	template <typename T>
	class IMLPModelBuilder {
	public:
		enum PerceptronBase {
			Matrix = 1,
			Graph = 2
		};

		virtual ~IMLPModelBuilder()= default;
		virtual void PerceptionBase(PerceptronBase flag) = 0;
		virtual void HiddenLayers(int hidden_layers)  = 0;
		virtual void ActivationFunc(ActivationFunction::ActivationFunctionFlags flag)  = 0;
		virtual void HiddenUnitsPerLayer(int hidden_units_per_layer)  = 0;
		virtual void LearningRate(float learning_rate, bool use_auto_decrease)  = 0;
		virtual IMLPModel<T> *GetResult()  = 0;
	};
}

#endif

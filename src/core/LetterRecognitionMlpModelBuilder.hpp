//
// Created by LudwigAndreas on 2/11/23.
//

#ifndef SIMPLEMLP_LETTERRECOGNITIONMLPMODELBUILDER_HPP
#define SIMPLEMLP_LETTERRECOGNITIONMLPMODELBUILDER_HPP

#include "IMLPModelBuilder.hpp"

namespace s21 {
	class LetterRecognitionMLPModelBuilder : IMLPModelBuilder<float> {
		IMLPModel<float> *model;
		PerceptronBase base;
		int hidden_layers;
		ActivationFunction *func;
		int hidden_units_per_layer;
		float learning_rate;

	public:
		LetterRecognitionMLPModelBuilder();

		virtual ~LetterRecognitionMLPModelBuilder();

		void PerceptionBase(PerceptronBase flag) override;

		void HiddenLayers(int hidden_layers) override;

		void ActivationFunc(
				ActivationFunction::ActivationFunctionFlags flag) override;

		void HiddenUnitsPerLayer(int hidden_units_per_layer) override;

		void LearningRate(float learning_rate,
						  bool use_auto_decrease) override;

		IMLPModel<float> * GetResult() override;

	};
}


#endif //SIMPLEMLP_LETTERRECOGNITIONMLPMODELBUILDER_HPP

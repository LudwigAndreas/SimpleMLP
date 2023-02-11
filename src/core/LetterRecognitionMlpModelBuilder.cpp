#include "LetterRecognitionMlpModelBuilder.hpp"
#include "MLPMatrixModelv2.hpp"

void s21::LetterRecognitionMLPModelBuilder::PerceptionBase(
		s21::IMLPModelBuilder<float>::PerceptronBase flag) {
	if (flag == PerceptronBase::Matrix) {
		base = flag;
	} else if (flag == PerceptronBase::Graph) {
		std::cerr << "there is no implementation for graph model";
	}
}

void
s21::LetterRecognitionMLPModelBuilder::HiddenLayers(int hidden_layers) {
	this->hidden_layers = hidden_layers;
}

void s21::LetterRecognitionMLPModelBuilder::ActivationFunc(
		s21::ActivationFunction::ActivationFunctionFlags flag) {
	this->func = ActivationFunction::getFunctionByFlag(flag);
}

void s21::LetterRecognitionMLPModelBuilder::HiddenUnitsPerLayer(
		int hidden_units_per_layer) {
	this->hidden_units_per_layer = hidden_units_per_layer;
}

void s21::LetterRecognitionMLPModelBuilder::LearningRate(float learning_rate,
														 bool use_auto_decrease) {
	this->learning_rate = learning_rate;
}

s21::IMLPModel<float> *
s21::LetterRecognitionMLPModelBuilder::GetResult() {
	if (base == 0) {
		base = Matrix;
	}
	if (hidden_units_per_layer == 0) {
		hidden_units_per_layer = 28 * 28 + 26;
	}
	if (hidden_layers == 0) {
		hidden_layers = 2;
	}
	if (learning_rate == 0) {
		learning_rate = 0.5f;
	}
	if (func == nullptr) {
		func = ActivationFunction::getFunctionByFlag(ActivationFunction::Sigmoid);
	}
	if (base == PerceptronBase::Matrix) {
		return MLPMatrixModelv2::MakeModel(28 * 28, 26, hidden_units_per_layer, hidden_layers, learning_rate, func);
	} else if (base == PerceptronBase::Graph) {
		return nullptr;
	}
	return nullptr;
}

s21::LetterRecognitionMLPModelBuilder::~LetterRecognitionMLPModelBuilder() {
	delete func;
//	if (model)
//		delete model;
}

s21::LetterRecognitionMLPModelBuilder::LetterRecognitionMLPModelBuilder() {
//	this->Reset();
}

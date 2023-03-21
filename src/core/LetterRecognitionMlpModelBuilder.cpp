#include "LetterRecognitionMlpModelBuilder.hpp"
#include "matrix/MLPMatrixModelv2.hpp"

s21::LetterRecognitionMLPModelBuilder *
s21::LetterRecognitionMLPModelBuilder::PerceptionBase(
		s21::IMLPModelBuilder<float>::PerceptronBase flag) {
	if (flag == PerceptronBase::Matrix) {
		base = flag;
	} else if (flag == PerceptronBase::Graph) {
		std::cerr << "there is no implementation for graph model";
	}
	return this;
}

s21::LetterRecognitionMLPModelBuilder *
s21::LetterRecognitionMLPModelBuilder::PerceptionBase(
		const std::string base) {
	if (base == "Matrix") {
		this->base = LetterRecognitionMLPModelBuilder::Matrix;
	} else if (base == "Graph") {
		std::cerr << "there is no implementation for graph model";
	}
	return this;
}

s21::LetterRecognitionMLPModelBuilder *
s21::LetterRecognitionMLPModelBuilder::HiddenLayers(int hidden_layers) {
	this->hidden_layers = hidden_layers;
	return this;
}

s21::LetterRecognitionMLPModelBuilder *
s21::LetterRecognitionMLPModelBuilder::ActivationFunc(
		s21::ActivationFunction::Flags flag) {
	this->func = ActivationFunction::getFunctionByFlag(flag);
	return this;
}

s21::LetterRecognitionMLPModelBuilder *
s21::LetterRecognitionMLPModelBuilder::ActivationFunc(
		const std::string func_name) {
	this->func = ActivationFunction::getFunctionByName(func_name); //TODO Doesn't work with non-lowercase func name
	return this;
}

s21::LetterRecognitionMLPModelBuilder *
s21::LetterRecognitionMLPModelBuilder::HiddenUnitsPerLayer(
		int hidden_units_per_layer) {
	this->hidden_units_per_layer = hidden_units_per_layer;
	return this;
}

s21::LetterRecognitionMLPModelBuilder *
s21::LetterRecognitionMLPModelBuilder::LearningRate(
		float learning_rate, bool use_auto_decrease) {
	this->learning_rate = learning_rate;
	this->use_auto_decrease = use_auto_decrease;
	return this;
}

s21::IMLPModel<float> *
s21::LetterRecognitionMLPModelBuilder::GetResult() {
	if (base == 0) {
		base = Matrix;
	}
	if (hidden_units_per_layer == 0) {
		hidden_units_per_layer = in_channels + out_channels;
	}
	if (hidden_layers == 0) {
		hidden_layers = 2;
	}
	if (learning_rate == 0) {
		learning_rate = 0.5f;
	}
	if (func == nullptr) {
		func = ActivationFunction::getFunctionByFlag(
				ActivationFunction::Sigmoid
				);
	}
	if (base == PerceptronBase::Matrix) {
		return MLPMatrixModelv2::MakeModel(
				in_channels,
				out_channels,
				hidden_units_per_layer,
				hidden_layers,
				learning_rate,
				func,
				use_auto_decrease
				);
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
	this->Reset();
}

void s21::LetterRecognitionMLPModelBuilder::Reset() {
	base = PerceptronBase::Matrix;
	hidden_layers = 0;
	func = ActivationFunction::getFunctionByFlag(ActivationFunction::Sigmoid);
	hidden_units_per_layer = 0;
	learning_rate = 0;
	use_auto_decrease = true;
}

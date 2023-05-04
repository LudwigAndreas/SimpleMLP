#include "MLPGraphModel.hpp"

#include "libs21/include/libs21.h"

namespace s21 {
	MLPGraphModel::MLPGraphModel(std::vector<size_t> units_per_layer,
							const ActivationFunction &func,
							bool use_auto_decrease,
							float lr) :
							units_per_layer(units_per_layer), af(func),
							auto_decrease(use_auto_decrease), lr(lr) {
		start_lr = lr;
		MLPGraphLayer *input_layer = nullptr;
		for (auto size : units_per_layer) 
			input_layer = AddLayer(new MLPGraphLayer(size, af, input_layer));
		for (auto layer : layers)
			layer->GenerateLayer();
	}

	MLPGraphLayer	*MLPGraphModel::AddLayer(MLPGraphLayer *layer) {

		if (layers.size()) {
			layer->SetInputLayer(layers.back());
			layers.back()->SetOutputLayer(layer);
		}
		layers.push_back(layer);
		return layer;
	}

	std::vector<T>	MLPGraphModel::Forward(Matrix<T> input) {
		layers.front()->SetLayerValues(input);
		for (auto it = layers.begin() + 1; it < layers.end(); ++it) {
			(*it)->CalculateLayer(af);
		}
		return layers.back()->GetResultingVector();
	}

	void	MLPGraphModel::Backward(Matrix<T> target) {
		assert(std::get<1>(target.get_shape()) == units_per_layer.back());

		layers.back()->CalculateError(&(target.ToVector()));
		for (size_t i = layers.size() - 2; i > 0; --i) {
			layers[i]->CalculateError();
		}
		for (size_t i = layers.size() - 1; i > 0; --i)
			layers[i]->UpdateWeights(lr);
	}

	float	MLPGraphModel::Train(DatasetGroup samples, bool silent_mode) {
		int correct_guesses = 0;
		for (size_t i = 0; i < samples.size(); ++i) {
			if (Predict(samples[i].x) == getMostProbablePrediction(samples[i].y.ToVector()))
				++correct_guesses;
			else
				Backward(samples[i].y);
		}
		float accuracy = ((float) correct_guesses / (float) samples.size());
		if (!silent_mode)
			std::cerr << "Train: " << accuracy * 100 << "% accuracy" << std::endl;
		// if (auto_decrease) {
		// 	lr = start_lr * (1 - std::min(accuracy, 0.99f));
		// }
		return accuracy;
	}

	float	MLPGraphModel::Test(DatasetGroup samples, bool silent_mode) { 
		int correct_guesses = 0;
		float accuracy;
		for (size_t i = 0; i < samples.size(); ++i) {
			if (Predict(samples[i].x) == getMostProbablePrediction(samples[i].y.ToVector()))
				++correct_guesses;
		}
		accuracy = ((float)correct_guesses / samples.size());
		if (!silent_mode)
			std::cerr << "Test: " << accuracy * 100 << "% accuracy" << std::endl;
		return accuracy;

	}

	int	MLPGraphModel::Predict(Matrix<float> x) {
		return getMostProbablePrediction(Forward(x));
	}

	const std::vector<size_t> &MLPGraphModel::getUnitsPerLayer() const {
		return units_per_layer;
	}

	void MLPGraphModel::setUnitsPerLayer(const std::vector<size_t> &unitsPerLayer) {
		units_per_layer = unitsPerLayer;
	}

	const std::vector<MLPGraphLayer *> &MLPGraphModel::get_layers() const {
		return layers;
	}

	void MLPGraphModel::set_layers(const std::vector<MLPGraphLayer *> &layers) {
		MLPGraphModel::layers = layers;
	}

	const ActivationFunction &MLPGraphModel::getAf() const {
		return af;
	}

	void MLPGraphModel::setAf(ActivationFunction &af) {
		MLPGraphModel::af = af;
	}

	float MLPGraphModel::getStartLr() const {
		return start_lr;
	}

	void MLPGraphModel::setStartLr(float startLr) {
		start_lr = startLr;
	}

	float MLPGraphModel::getLr() const {
		return lr;
	}

	void MLPGraphModel::setLr(float lr) {
		MLPGraphModel::lr = lr;
	}

	bool MLPGraphModel::isAutoDecrease() const {
		return auto_decrease;
	}

	void MLPGraphModel::setAutoDecrease(bool autoDecrease) {
		auto_decrease = autoDecrease;
	}

	std::vector<MLPGraphLayer *> &MLPGraphModel::get_layers() {
		return layers;
	}

	IMLPModel *MLPGraphModel::MakeModel(size_t in_channels, size_t out_channels,
								size_t hidden_units_per_layer, 
								int hidden_layers, float lr, 
								ActivationFunction func, 
								bool use_auto_decrease) {
		std::vector<size_t> units_per_layer;
		units_per_layer.push_back(in_channels);

		for (int i = 0; i < hidden_layers; ++i)
			units_per_layer.push_back(hidden_units_per_layer);

		units_per_layer.push_back(out_channels);
		auto *model = new MLPGraphModel(units_per_layer, func, use_auto_decrease, lr);
		return model;
	}

	std::istream &operator>>(std::istream &is, MLPGraphModel &model) {
		
		std::string units_per_layer_str;
		std::string af_str;
		// std::string line;
		std::getline(is, units_per_layer_str);
		std::getline(is, af_str);

		auto upls = s21::split(units_per_layer_str, " ");
		auto af = ActivationFunction(af_str);
		std::vector<size_t> units_per_layer;
		for (auto i = upls.begin(); i < upls.end() - 1; ++i)
			units_per_layer.push_back(std::atoi(i->data()));
		model.setUnitsPerLayer(units_per_layer);
		model.setLr(std::atoi(upls.rbegin()->data()));
		model.setAf(af);

		MLPGraphLayer *input_layer = nullptr;
		for (auto size : units_per_layer) 
			input_layer = model.AddLayer(new MLPGraphLayer(size, ActivationFunction(model.getAf()), input_layer));
		auto &layers = model.get_layers();
		for (size_t i = 1; i < layers.size(); ++i)
			is >> *layers[i];
		return is;
	}

	std::ostream &operator<<(std::ostream &os, MLPGraphModel &model) {
		// os << "G" << std::endl;
		for (auto unit : model.getUnitsPerLayer())
			os << unit << ' ';
		os << model.getLr() << std::endl;
		os << model.getAf() << std::endl;
		for (auto it = model.get_layers().begin() + 1; it != model.get_layers().end(); ++it) {
			os << **it;
		}
		return os;
	}
}

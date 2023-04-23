#include "MLPMatrixModel.hpp"

namespace s21 {

	MLPMatrixModel::MLPMatrixModel(std::vector<size_t> units_per_layer,
							ActivationFunction *func,
							bool use_auto_decrease,
							float lr) :
							units_per_layer(units_per_layer),
							auto_decrease(use_auto_decrease), lr(lr) {
		af 		 = func;
		start_lr = lr;
		
		for (size_t i = 0; i < units_per_layer.size(); ++i) {
			MLPMatrixLayer* layer 		= nullptr;
			size_t 			in_channels = units_per_layer[i];
			if (i != units_per_layer.size() - 1) {
				size_t out_channels = units_per_layer[i + 1];
				layer = new MLPMatrixLayer(GenerateNDMatrix<float>
										(in_channels, out_channels),
										GenerateNDMatrix<float>
										(1, out_channels));
			}
			else {
				layer = new MLPMatrixLayer(in_channels);
			}
			layers.push_back(layer);
		}
	}

	const std::vector<size_t> &MLPMatrixModel::get_units_per_layer() const {
		return units_per_layer;
	}

	const std::vector<MLPMatrixLayer *> &MLPMatrixModel::get_layers() const {
		return layers;
	}

	float MLPMatrixModel::get_lr() const {
		return lr;
	}

	void MLPMatrixModel::set_units_per_layer(const std::vector<size_t> &unitsPerLayer) {
		units_per_layer = unitsPerLayer;
		//TODO: add check for setter logic
	}

	void MLPMatrixModel::set_layers(std::vector<MLPMatrixLayer *> l) {
		this->layers = l;
		//TODO: add check for setter logic
	}

	void MLPMatrixModel::set_lr(float lr) {
		MLPMatrixModel::lr = lr;
	}

	Matrix<float> MLPMatrixModel::NormalizedInput(Matrix<float> matrix) {
		std::vector<float>::iterator begin = matrix.ToVector().begin(), end = matrix.ToVector().end();
		float min, max;
		max = *std::max_element(begin, end);
		min = *std::min_element(begin, end);
		if (min == max)
			return matrix;
		for (auto it = begin; it < end; ++it)
			*it = std::min(1.f, std::max(0.f, (*it - min) * (1.f / (max - min))));
		return (matrix);
	}

	std::vector<float> MLPMatrixModel::Forward(Matrix<float> matrix) {
		assert(std::get<1>(matrix.get_shape()) == units_per_layer[0] && std::get<1>(matrix.get_shape()));
		layers[0]->neuron_values = matrix;
		layers[0]->raw = matrix;
		for (int i = 0; i < units_per_layer.size() - 1; ++i) {
			Matrix<float> y = layers[i]->neuron_values * layers[i]->weight_matrices;
			y = y + layers[i]->bias;
			layers[i + 1]->raw = y;
			y = y.apply_function(af->getFunction());
			layers[i + 1]->neuron_values = y;
		}
		return softmax(layers.back()->neuron_values.ToVector());
	}
	
	void MLPMatrixModel::Backward(Matrix<float> target) {
		assert(std::get<1>(target.get_shape()) == units_per_layer.back());
		layers[layers.size() - 2]->error = (layers.back()->neuron_values - target);
		
		for (int i = (int) units_per_layer.size() - 3; i >= 0; --i) {
			layers[i]->error = (layers[i + 1]->error.matmulTransposed(layers[i + 1]->weight_matrices))
				& layers[i + 1]->raw.apply_function(af->getDerivative());
		}
		for (size_t i = 0; i < units_per_layer.size() - 1; ++i) {
			layers[i]->weight_matrices = layers[i]->weight_matrices - (layers[i]->neuron_values.T() * layers[i]->error * .1f);
			layers[i]->bias = layers[i]->bias - (layers[i]->error * .1f);
		}
	}

	float MLPMatrixModel::TestOutput(std::vector<s21::Sample> samples, bool silent_mode, std::string filename) {
		// std::fstream		output;
		int					correct_guesses = 0;
		float				accuracy;
		std::vector<float>	y_hat;
		int					index;

		// if (!filename.empty())
		// 	output.open(filename, std::ofstream::out | std::ofstream::trunc);
		for (auto & sample : samples) {
			y_hat = Forward(sample.x);
			index = getMostProbablePrediction(y_hat);
			if (index == getMostProbablePrediction(sample.y.ToVector()))
				++correct_guesses;
//				if (output.is_open())
//					log(output, getMostProbablePrediction(sample.y.ToVector()), index, y_hat[index]);
		}
		accuracy = ((float)correct_guesses / samples.size());
		if (!silent_mode)
			std::cerr << "Test: " << accuracy * 100 << "% accuracy" << std::endl;
		return accuracy;
	}

	int MLPMatrixModel::Predict(Matrix<float> x) {
		return getMostProbablePrediction(Forward(x));
	}

	IMLPModel *MLPMatrixModel::MakeModel(size_t in_channels, size_t out_channels, size_t hidden_units_per_layer, int hidden_layers, float lr, ActivationFunction *func, bool use_auto_decrease) {
		std::vector<size_t> units_per_layer;
		units_per_layer.push_back(in_channels);

		for (int i = 0; i < hidden_layers; ++i)
			units_per_layer.push_back(hidden_units_per_layer);

		units_per_layer.push_back(out_channels);
		auto *model = new MLPMatrixModel(units_per_layer, func, use_auto_decrease, lr);
		return model;
	}

	std::ostream &operator<<(std::ostream &os, const MLPMatrixModel &model) {
		for (auto unit: model.get_units_per_layer()) {
			os << unit << " ";
		}
		os << model.get_lr() << '\n';
		for (const auto &layer : model.get_layers())
			os << *layer;
		return os;
	}

	std::istream &operator>>(std::istream &is, MLPMatrixModel &model) {
		std::vector<MLPMatrixLayer *> layers;
		std::string units_per_layer_str;
		
		// std::string line;
		std::getline(is, units_per_layer_str);

		auto upls = split(units_per_layer_str, " ");
		std::vector<size_t> units_per_layer;
		for (auto i = upls.begin(); i < upls.end() - 1; ++i)
			units_per_layer.push_back(std::atoi(i->data()));
		model.set_units_per_layer(units_per_layer);
		model.set_lr(std::atof(upls.rbegin()->data()));

		for (int i = 0; i < units_per_layer.size() - 1; ++i) {
			Matrix<float> w, b;
			is >> w >> b;
			layers.push_back(new MLPMatrixLayer(w, b));
		}
		layers.push_back(new MLPMatrixLayer(units_per_layer.back()));
		model.set_layers(std::move(layers));
		
		return is;
	}

}
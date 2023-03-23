#include "MLPGraphModel.hpp"

namespace s21 {
		MLPGraphModel::MLPGraphModel(std::vector<size_t> units_per_layer,
								ActivationFunction *func,
								bool use_auto_decrease,
								float lr) :
								units_per_layer(units_per_layer),
								auto_decrease(use_auto_decrease), lr(lr) {
			af = func;
			start_lr = lr;
			MLPGraphLayer *input_layer = nullptr;
			for (auto size : units_per_layer) 
				input_layer = AddLayer(new MLPGraphLayer(size, af, input_layer));
			for (auto layer : layers)
				layer->GenerateLayer();
			// dedt.resize(units_per_layer.size() - 1);
			// dedw.resize(units_per_layer.size() - 1);
			// dedb.resize(units_per_layer.size() - 1);
			// dedh.resize(units_per_layer.size() - 2);
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

		void			MLPGraphModel::Backward(Matrix<T> target) {
			assert(std::get<1>(target.get_shape()) == units_per_layer.back());

			layers.back()->CalculateError(&(target.ToVector()));
			for (int i = (int) layers.size() - 2; i > 0; --i) {
				layers[i]->CalculateError();
				layers[i]->UpdateWeights(lr);
			}
		}

		float			MLPGraphModel::Train(DatasetGroup samples, bool silent_mode) {
			int correct_guesses = 0;
			for (int i = 0; i < (int) samples.size(); ++i) {
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

		float			MLPGraphModel::Test(DatasetGroup samples, bool silent_mode) { 
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

		int				MLPGraphModel::Predict(Matrix<float> x) {
			return getMostProbablePrediction(Forward(x));
		}

		float			MLPGraphModel::TestOutput(std::vector<Sample> samples, bool silent_mode, std::string filename) {
			// std::fstream		output;
			// int					correct_guesses = 0;
			// float				accuracy;
			// std::vector<float>	y_hat;
			// int					index;

			// if (!filename.empty())
			// 	output.open(filename, std::ofstream::out | std::ofstream::trunc);
			// for (auto & sample : samples) {
			// 	y_hat = Forward(sample.x);
			// 	index = getMostProbablePrediction(y_hat);
			// 	if (index == getMostProbablePrediction(sample.y.ToVector()))
			// 		++correct_guesses;
			// 	if (output.is_open())
			// 		log(output, getMostProbablePrediction(sample.y.ToVector()), index, y_hat[index]);
			// }
			// accuracy = ((float)correct_guesses / samples.size());
			// if (!silent_mode)
			// 	std::cerr << "Test: " << accuracy * 100 << "% accuracy" << std::endl;
			// return accuracy;
			return 1;
		}
}

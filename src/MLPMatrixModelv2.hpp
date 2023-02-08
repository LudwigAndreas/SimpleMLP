#ifndef SIMPLEMLP_MLPMATRIXMODEL2_HPP
#define SIMPLEMLP_MLPMATRIXMODEL2_HPP

#include <fstream>

#include "IMLPModel.hpp"
#include "Matrix.hpp"
#include "ActivationFunction.hpp"

namespace s21 {
	

	class MLPMatrixModelv2 : s21::IMLPModel<float> {
	private:
		std::vector<size_t>			units_per_layer;
		std::vector<Matrix<float>>	bias;
		std::vector<Matrix<float>>	weight_matrices;
		std::vector<Matrix<float>>	neuron_values;
		std::vector<Matrix<float>>	error;
		ActivationFunction			*af;
		float						lr;

		explicit MLPMatrixModelv2(std::vector<size_t> units_per_layer, float lr = .1f) :
								units_per_layer(units_per_layer), lr(lr) {
			// af = ActivationFunction::getFunctionByName("bounded linear");
			af = ActivationFunction::getFunctionByName("ReLU");
			// af = ActivationFunction::getFunctionByName("sigmoid");
			// af = ActivationFunction::getFunctionByName("bipolar sigmoid");
			for (size_t i = 0; i < units_per_layer.size() - 1; ++i) {
				size_t in_channels = units_per_layer[i];
				size_t out_channels = units_per_layer[i + 1];

				weight_matrices.push_back(GenerateNDMatrix<float>(out_channels, in_channels));
				bias.push_back(GenerateNDMatrix<float>(out_channels, 1));
			}
			for (size_t i = 0; i < units_per_layer.size(); ++i) {
				neuron_values.push_back(Matrix<float>(units_per_layer[i], 1));
				error.push_back(Matrix<float>(units_per_layer[i], 1));
			}
		}

		int getMostProbablePrediction(std::vector<float> value) {
			double max = value[0];
			int prediction = 0;
			double tmp;
			for (int j = 1; j < value.size(); j++) {
				tmp = value[j];
				if (tmp > max) {
					prediction = j;
					max = tmp;
				}
			}
			return prediction; // +1 for dataset (who tf thought that it would be a good idea to numerate dataset choices from 1 and not from 0)
		}

	public:
		// MLPMatrixModelv2() = delete;

		// MLPMatrixModelv2 &operator=(const MLPMatrixModelv2 matrix) = delete;

		// MLPMatrixModelv2(MLPMatrixModelv2 const &) = delete;

		const std::vector<size_t> &get_units_per_layer() const {
			return units_per_layer;
		}

		const std::vector<Matrix<float>> &get_bias_vectors() const {
			return bias;
		}

		const std::vector<Matrix<float>> &get_weight_matrices() const {
			return weight_matrices;
		}

		const std::vector<Matrix<float>> &get_neuron_values() const {
			return neuron_values;
		}

		const std::vector<Matrix<float>> &get_error() const {
			return error;
		}

		float get_lr() const {
			return lr;
		}

		void set_units_per_layer(const std::vector<size_t> &unitsPerLayer) {
			units_per_layer = unitsPerLayer;
			// neuron_values.resize(0);
			// error.resize(0);

			// for (size_t i = 0; i < units_per_layer.size(); ++i) {
			// 	neuron_values.push_back(Matrix<float>(units_per_layer[i], 1));
			// 	error.push_back(Matrix<float>(units_per_layer[i], 1));
			// }
			//TODO: add check for setter logic
		}

		void set_lr(float lr) {
			MLPMatrixModelv2::lr = lr;
		}

		void set_bias(std::vector<Matrix<float>> bias) {
			this->bias = bias;
			//TODO: add check for setter logic
		}

		void set_weight_martices(std::vector<Matrix<float>> weight_matrices) {
			this->weight_matrices = weight_matrices;

			//TODO: add check for setter logic
		}

		void set_neuron_values(std::vector<Matrix<float>> neuron_values) {
			this->neuron_values = neuron_values;
			//TODO: add check for setter logic
		}

		void set_error(std::vector<Matrix<float>> error) {
			this->error = error;
			//TODO: add check for setter logic
		}

		std::vector<float> Forward(Matrix<float> matrix) override {
			// std::vector<float>	normalized_vector;
			// float				length = 0;

			neuron_values[0] = matrix;
			for (int i = 1; i < units_per_layer.size(); ++i)
				neuron_values[i] = ((weight_matrices[i - 1] * neuron_values[i - 1])
									+ bias[i - 1]).apply_function(af->getFunction());
			// normalized_vector = neuron_values.back().ToVector();
			
			// for (auto &elem : normalized_vector)
			// 	length += elem * elem;
			return neuron_values.back().ToVector();
		}

		// void Backward(Matrix<float> target) override {
		// 	assert(std::get<0>(target.get_shape()) == units_per_layer.back());
		// 	const int last_layer_index = units_per_layer.size() - 1;
		// 	Matrix<float> diff = (target - neuron_values.back());
		// 	Matrix<float> d_neuron = neuron_values.back().apply_function(af->getDerivative()).T();

		// 	error[last_layer_index] = diff.matmul(d_neuron);
		// 	// for (int i = 0; i < units_per_layer.back(); ++i)
		// 		// error[units_per_layer.size() - 1](i, 0) = 
		// 			// (target(0, i) - neuron_values[units_per_layer.size() - 1](i, 0)) *
		// 				// af->applyDerivative(neuron_values[units_per_layer.size() - 1](i, 0));
		// 	for (int i = units_per_layer.size() - 2; i > 0; --i)
		// 		for (int j = 0; j < units_per_layer[i]; ++j)
		// 			error[i](j, 0) *= af->applyFunction(neuron_values[i](j, 0));
		// 	UpdateWeights();
		// }


		// void UpdateWeights() {
		// 	for (int i = 0; i < units_per_layer.size() - 1; ++i)
		// 		for (int j = 0; j < units_per_layer[i + 1]; ++j)
		// 			for (int k = 0; k < units_per_layer[i]; ++k)
		// 				weight_matrices[i](j, k) += neuron_values[i](k, 0) * error[i + 1](j, 0) * lr;
		// 	for (int i = 0; i < units_per_layer.size() - 1; ++i) {
		// 		for (int j = 0; j < units_per_layer[i + 1]; ++j) {
		// 			bias[i](j, 0) += error[i + 1](j, 0) * lr;
		// 		}
		// 	}
		// }

		void Backward(Matrix<float> target) override {
			assert(std::get<0>(target.get_shape()) == units_per_layer.back());

			Matrix<float> y = target;
			Matrix<float> y_hat = neuron_values.back();
			Matrix<float> diff = (y - y_hat).T();

			for (int i = weight_matrices.size() - 1; i >= 0; --i) {
				Matrix<float> wt = weight_matrices[i];
				Matrix<float> prev_errors = diff.matmul(wt);

				Matrix<float> d_outputs = neuron_values[i + 1].apply_function(d_sigmoid);
				Matrix<float> gradients = diff.multiply_elementwise(d_outputs);
				gradients = gradients.multiply_scalar(lr);
				Matrix<float> a_trans = neuron_values[i];
				Matrix<float> weight_gradients = gradients.matmul(a_trans);

				bias[i] = bias[i].add(gradients);
				weight_matrices[i] = weight_matrices[i].add(weight_gradients);
				diff = prev_errors;
			}
		}

		float Train(DatasetGroup samples, bool silent_mode = false) override {
			int correct_guesses = 0;
			float accuracy;
			for (int i = 0; i < samples.size(); ++i) {
				if (Predict(samples[i].x) == getMostProbablePrediction(samples[i].y.ToVector()))
					++correct_guesses;
				else 
					Backward(samples[i].y);
			}
			accuracy = ((float)correct_guesses / samples.size());
			if (!silent_mode)
				std::cerr << "Train: " << accuracy * 100 << "% accuracy" << std::endl;
			lr *= .999;
			return accuracy;
		}

		float CrossValidation(Dataset dataset, bool silent_mode = false) override {
			float training_accuracy;
			float testing_accuracy;
			int trained_on;
			for (int i = 0; i < dataset.size(); ++i) {
				training_accuracy = 0;
				testing_accuracy = 0;
				trained_on = 0;
				for (int j = 0; j < dataset.size(); ++j) {
					std::cerr << "\rEpoch #" << i << ", " << trained_on << '/' << dataset.size() - 1 << " groups trained on. ";
					if (j)
						std::cerr << "Current accuracy: " << (training_accuracy * 100) / (trained_on) << '%'; 
					if (j != dataset.current_iteration && ++trained_on)
						training_accuracy += Train(dataset[j], true);
					
				}
				std::cerr << "\rEpoch #" << i + 1 << ", " << trained_on << '/' << dataset.size() << " groups trained on.\n";
				std::cerr << "Train: " << (training_accuracy * 100) / (trained_on) << "% accuracy" << std::endl;
				testing_accuracy = Test(dataset[dataset.current_iteration], true);
				std::cerr << "Test:  " << testing_accuracy * 100 << "% accuracy" << std::endl;
				++dataset.current_iteration;
			}
			return testing_accuracy;
		}

		float Test(DatasetGroup samples, bool silent_mode = false) override {
			int correct_guesses = 0;
			float accuracy;
			for (int i = 0; i < samples.size(); ++i) {
				if (Predict(samples[i].x) == getMostProbablePrediction(samples[i].y.ToVector()))
					++correct_guesses;
			}
			accuracy = ((float)correct_guesses / samples.size());
			if (!silent_mode)
				std::cerr << "Test: " << accuracy * 100 << "% accuracy" << std::endl;
			return accuracy;
		}

		void log(std::fstream &file, int y, int y_hat, float probability) {
			file << ((y == y_hat) ? "✅" : "❌") << ' '
				<< char('A' + y) << " "
				<< char('A' + y_hat) << ' ' 
				<< probability * 100 << "%" << std::endl;
		}

		float TestOutput(DatasetGroup samples, bool silent_mode = false, std::string filename = "") override {
			std::fstream		output;
			int					correct_guesses = 0;
			float				accuracy;
			std::vector<float>	y_hat;
			int					index;

			if (!filename.empty())
				output.open(filename, std::ofstream::out | std::ofstream::trunc);
			for (int i = 0; i < samples.size(); ++i) {
				y_hat = Forward(samples[i].x);
				index = getMostProbablePrediction(y_hat);
				if (index == getMostProbablePrediction(samples[i].y.ToVector()))
					++correct_guesses;
				if (output.is_open())
					log(output, getMostProbablePrediction(samples[i].y.ToVector()), index, y_hat[index]);
			}
			accuracy = ((float)correct_guesses / samples.size());
			if (!silent_mode)
				std::cerr << "Test: " << accuracy * 100 << "% accuracy" << std::endl;
			return accuracy;
		}

		int Predict(Matrix<float> x) override {
			return getMostProbablePrediction(Forward(x));
		}

		static IMLPModel<float> *MakeModel(size_t in_channels, size_t out_channels, size_t hidden_units_per_layer, int hidden_layers, float lr){
			std::vector<size_t> units_per_layer;
			units_per_layer.push_back(in_channels);

			for (int i = 0; i < hidden_layers; ++i)
				units_per_layer.push_back(hidden_units_per_layer);

			units_per_layer.push_back(out_channels);
			auto *model = new MLPMatrixModelv2(units_per_layer, lr);
			return model;
		}
	};
}

#endif //SIMPLEMLP_MLPMATRIXMODEL_HPP

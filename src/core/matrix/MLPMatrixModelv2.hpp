#ifndef SIMPLEMLP_MLPMATRIXMODEL2_HPP
#define SIMPLEMLP_MLPMATRIXMODEL2_HPP

#include <fstream>
#include <algorithm>

#include "../utils/IMLPModel.hpp"
#include "Matrix.hpp"
#include "../utils/ActivationFunction.hpp"

namespace s21 {
	

	class MLPMatrixModelv2 : s21::IMLPModel<float> {
	private:
		std::vector<size_t> units_per_layer;
		std::vector<Matrix<float>> bias;
		std::vector<Matrix<float>> weight_matrices;
		std::vector<Matrix<float>> neuron_values;
		std::vector<Matrix<float>> error;
		std::vector<Matrix<float>> raw;
		bool auto_decrease;

		ActivationFunction			*af;
		float						lr;
		float						start_lr;

		explicit MLPMatrixModelv2(std::vector<size_t> units_per_layer,
								  ActivationFunction *func,
								  bool use_auto_decrease = true,
								  float lr = .05f) :
								units_per_layer(units_per_layer),
								auto_decrease(use_auto_decrease), lr(lr) {
			af = func;
			start_lr = lr;
			for (size_t i = 0; i < units_per_layer.size() - 1; ++i) {
				size_t in_channels = units_per_layer[i];
				size_t out_channels = units_per_layer[i + 1];

				auto W = GenerateNDMatrix<float>(in_channels,
												 out_channels);
				weight_matrices.push_back(W);

				auto b = GenerateNDMatrix<float>(1,
												 out_channels);
				bias.push_back(b);
			}
			for (unsigned long & i : units_per_layer) {
				neuron_values.emplace_back(1, i);
				raw.emplace_back(1, i);
				error.emplace_back(1, i);
			}
			// dedt.resize(units_per_layer.size() - 1);
			// dedw.resize(units_per_layer.size() - 1);
			// dedb.resize(units_per_layer.size() - 1);
			// dedh.resize(units_per_layer.size() - 2);
		}

		static int getMostProbablePrediction(std::vector<float> value) {
			double max = value[0];
			int prediction = 0;
			double tmp;
			for (int j = 1; j < (int) value.size(); j++) {
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
			// h.resize(0);
			// error.resize(0);

			// for (size_t i = 0; i < units_per_layer.size(); ++i) {
			// 	h.push_back(Matrix<float>(units_per_layer[i], 1));
			// 	error.push_back(Matrix<float>(units_per_layer[i], 1));
			// }
			//TODO: add check for setter logic
		}

		void set_lr(float lr) {
			MLPMatrixModelv2::lr = lr;
		}

		void set_bias(std::vector<Matrix<float>> b) {
			this->bias = b;
			//TODO: add check for setter logic
		}

		void set_weight_martices(std::vector<Matrix<float>> W) {
			this->weight_matrices = W;

			//TODO: add check for setter logic
		}

		void set_neuron_values(std::vector<Matrix<float>> h) {
			this->neuron_values = h;
			//TODO: add check for setter logic
		}

		void set_error(std::vector<Matrix<float>> error) {
			this->error = error;
			//TODO: add check for setter logic
		}

		Matrix<float> softmax(Matrix<float> matrix) {
			std::vector<float>	values;
			float	sum;

			for (auto val : matrix.ToVector())
				values.push_back(std::exp(val));
			sum = std::accumulate(values.begin(), values.end(), 0);
			std::transform(values.begin(), values.end(),
						   values.begin(), [sum](float x){ return x / sum; });
			return s21::Matrix<float>(values);
		}

		std::vector<float> Forward(Matrix<float> matrix) override {
		assert(std::get<1>(matrix.get_shape()) == units_per_layer[0] && std::get<1>(matrix.get_shape()));

		neuron_values[0] = matrix;
		raw[0] = matrix;
		for (int i = 0; i < units_per_layer.size() - 1; ++i) {
			Matrix<float> y = neuron_values[i] * weight_matrices[i];
			y = y + bias[i];
			raw[i + 1] = y;
			y = y.apply_function(af->getFunction());
			neuron_values[i + 1] = y;
		}
		return neuron_values.back().ToVector();
		}
		
		void Backward(Matrix<float> target) override {
			assert(std::get<1>(target.get_shape()) == units_per_layer.back());

			error[units_per_layer.size() - 1] = (neuron_values.back() - target);
			for (int i = (int) units_per_layer.size() - 2; i >= 0; --i) {
					error[i] = (error[i + 1] * weight_matrices[i].T()) & raw[i].apply_function(af->getDerivative());
			}
			for (size_t i = 0; i < units_per_layer.size() - 1; ++i) {
				weight_matrices[i] = weight_matrices[i] - (neuron_values[i].T() * error[i + 1] * lr);
				bias[i] = bias[i] - error[i + 1] * lr;
			}
		}

		float Train(DatasetGroup samples, bool silent_mode = false) override {
			static float lower_bound = 0;
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
			if (auto_decrease) {
//				lr *= (1.f - bsigmoid((accuracy - lower_bound) / (1 - lower_bound)));
//				lower_bound = accuracy;
//				std::cerr << lr << std::endl;
				lr = start_lr * (1 - accuracy);
			}
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

		float TestOutput(std::vector<s21::Sample> samples, bool silent_mode = false, std::string filename = "") override {
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

		static IMLPModel<float> *MakeModel(size_t in_channels, size_t out_channels, size_t hidden_units_per_layer, int hidden_layers, float lr, ActivationFunction *func, bool use_auto_decrease = true){
			std::vector<size_t> units_per_layer;
			units_per_layer.push_back(in_channels);

			for (int i = 0; i < hidden_layers; ++i)
				units_per_layer.push_back(hidden_units_per_layer);

			units_per_layer.push_back(out_channels);
			auto *model = new MLPMatrixModelv2(units_per_layer, func, use_auto_decrease, lr);
			return model;
		}
	};
}

#endif

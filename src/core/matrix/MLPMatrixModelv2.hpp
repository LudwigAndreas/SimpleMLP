#ifndef SIMPLEMLP_MLPMATRIXMODEL2_HPP
#define SIMPLEMLP_MLPMATRIXMODEL2_HPP

#include <fstream>

#include "../utils/IMLPModel.hpp"
#include "Matrix.hpp"
#include "../utils/ActivationFunction.hpp"

namespace s21 {
	

	class MLPMatrixModelv2 : s21::IMLPModel<float> {
	private:
		std::vector<size_t>			units_per_layer;
		std::vector<Matrix<float>>	W;
		std::vector<Matrix<float>>	b;
		std::vector<Matrix<float>>	t;
		std::vector<Matrix<float>>	h;
		// std::vector<Matrix<float>>	error;
		std::vector<Matrix<float>>	dedt;
		std::vector<Matrix<float>>	dedw;
		std::vector<Matrix<float>>	dedb;
		std::vector<Matrix<float>>	dedh;
		Matrix<float>				output_vector;
		ActivationFunction			*af;
		float						lr;

		explicit MLPMatrixModelv2(std::vector<size_t> units_per_layer, float lr = .05f) :
								units_per_layer(units_per_layer), lr(lr) {
			af = ActivationFunction::getFunctionByName("ReLU");
			// af = ActivationFunction::getFunctionByName("sigmoid");
			for (size_t i = 0; i < units_per_layer.size() - 1; ++i) {
				size_t in_channels = units_per_layer[i];
				size_t out_channels = units_per_layer[i + 1];

				W.push_back(GenerateNDMatrix<float>(in_channels, out_channels));
				b.push_back(GenerateNDMatrix<float>(1, out_channels));
			}
			for (size_t i = 0; i < units_per_layer.size(); ++i) {
				h.push_back(Matrix<float>(units_per_layer[i], 1));
				t.push_back(Matrix<float>(units_per_layer[i], 1));
			}
			dedt.resize(units_per_layer.size() - 1);
			dedw.resize(units_per_layer.size() - 1);
			dedb.resize(units_per_layer.size() - 1);
			dedh.resize(units_per_layer.size() - 2);
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
			return b;
		}

		const std::vector<Matrix<float>> &get_weight_matrices() const {
			return W;
		}

		const std::vector<Matrix<float>> &get_neuron_values() const {
			return h;
		}

		const std::vector<Matrix<float>> &get_error() const {
			return dedw;
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
			this->b = b;
			//TODO: add check for setter logic
		}

		void set_weight_martices(std::vector<Matrix<float>> W) {
			this->W = W;

			//TODO: add check for setter logic
		}

		void set_neuron_values(std::vector<Matrix<float>> h) {
			this->h = h;
			//TODO: add check for setter logic
		}

		void set_error(std::vector<Matrix<float>> error) {
			this->dedw = error;
			//TODO: add check for setter logic
		}

		void PrintConfig() {
			for (int i = 0; i < W.size(); ++i)
				std::cout << "W[" << i << "] shape: " << W[i].get_rows() << 'x' << W[i].get_cols() << std::endl;
			std::cout << " -----\n";
			for (int i = 0; i < b.size(); ++i)
				std::cout << "b[" << i << "] shape: " << b[i].get_rows() << 'x' << b[i].get_cols() << std::endl;
			std::cout << " -----\n";
			for (int i = 0; i < t.size(); ++i)
				std::cout << "t[" << i << "] shape: " << t[i].get_rows() << 'x' << t[i].get_cols() << std::endl;
			std::cout << " -----\n";
			for (int i = 0; i < h.size(); ++i)
				std::cout << "h[" << i << "] shape: " << h[i].get_rows() << 'x' << h[i].get_cols() << std::endl;
			std::cout << " -----\n";
			for (int i = 0; i < dedw.size(); ++i)
				std::cout << "dedw[" << i << "] shape: " << dedw[i].get_rows() << 'x' << dedw[i].get_cols() << std::endl;
			std::cout << " -----\n";
			for (int i = 0; i < dedb.size(); ++i)
				std::cout << "dedb[" << i << "] shape: " << dedb[i].get_rows() << 'x' << dedb[i].get_cols() << std::endl;
			std::cout << " -----\n";
			for (int i = 0; i < dedt.size(); ++i)
				std::cout << "dedt[" << i << "] shape: " << dedt[i].get_rows() << 'x' << dedt[i].get_cols() << std::endl;
			std::cout << " -----\n";
			for (int i = 0; i < dedh.size(); ++i)
				std::cout << "dedh[" << i << "] shape: " << dedh[i].get_rows() << 'x' << dedh[i].get_cols() << std::endl;
		}

		Matrix<float> softmax(Matrix<float> matrix) {
			float	sum;

			sum = 0;
			for (auto val : matrix.ToVector())
				sum += std::exp(val);
			return matrix * (1. / sum);
		}

		std::vector<float> Forward(Matrix<float> matrix) override {
			t[0] = matrix;
			h[0] = matrix;
			for (int i = 1; i < units_per_layer.size(); ++i)
			{
				t[i] = ((h[i - 1] * W[i - 1]) + b[i - 1]);
				if (i != units_per_layer.size() - 1)
					h[i] = Matrix<float>(t[i]).apply_function(af->getFunction());
				// else
				//  	h[i] = softmax(t[i]);
			}
			// add cross entropy
			return h.back().ToVector();
		}

		void Backward(Matrix<float> target) override {
			assert(std::get<1>(target.get_shape()) == units_per_layer.back());
			const int last_layer_index = units_per_layer.size() - 3;
			// Matrix<float> diff = (h.back() - target);
			// Matrix<float> d_neuron = h.back().apply_function(af->getDerivative());

			dedt.back() = h.back() - target;
			dedw.back() = h[h.size() - 2].T() * dedt.back();
			dedb.back() = dedt.back();
			for (int i = last_layer_index; i >= 0; --i)
			{
				dedh[i] = dedt[i + 1] * W[i + 1].T();
				dedt[i] = dedh[i] & t[i + 1].apply_function(af->getDerivative());
				dedw[i] = h[i].T() * dedt[i];
				dedb[i] = dedt[i];
			}
			// dedh[0] = dedt[1] * W[1].T();
			// dedt[0] = dedh[0] & t[1].apply_function(af->getDerivative());
			// dedw[0] = h[0].T() * dedt[0];
			// dedb[0] = dedt[0];
			
			// for (int i = last_layer_index; i >= 0; --i)
			// {
			// 	dedh[i] = dedt[i + 1] * W[i + 1].T();
			// 	dedt[i] = dedh[i] & t[i + 1].apply_function(af->getDerivative());
			// 	dedw[i] = h[i + 1].T() * dedt[i];
			// 	dedb[i] = dedt[i];
			// }

			// dedt[1] = h[2] - target;
			// dedw[1] = h[1].T() * dedt[1];
			// dedb[1] = dedt[1];
			// dedh[0] = dedt[1] * W[1].T();
			// dedt[0] = dedh[0] & t[1].apply_function(af->getDerivative());
			// dedw[0] = h[0].T() * dedt[0];
			// dedb[0] = dedt[0];


			
			UpdateWeights();
		}


		void UpdateWeights() {
			for (int i = 0; i < W.size(); ++i)
				W[i] = W[i] - (dedw[i] * lr);
			for (int i = 0; i < b.size(); ++i)
				b[i] = b[i] - (dedb[i] * lr);
			// for (int i = 0; i < units_per_layer.size() - 1; ++i)
			// 	for (int j = 0; j < units_per_layer[i + 1]; ++j)
			// 		for (int k = 0; k < units_per_layer[i]; ++k)
			// 			W[i](j, k) += h[i](k, 0) * error[i + 1](j, 0) * lr;
			// for (int i = 0; i < units_per_layer.size() - 1; ++i) {
			// 	for (int j = 0; j < units_per_layer[i + 1]; ++j) {
			// 		b[i](j, 0) += error[i + 1](j, 0) * lr;
			// 	}
			// }
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

#endif

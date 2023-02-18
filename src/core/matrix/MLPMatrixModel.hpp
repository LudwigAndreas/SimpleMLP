#ifndef SIMPLEMLP_MLPMATRIXMODEL_HPP
#define SIMPLEMLP_MLPMATRIXMODEL_HPP

#include "IMLPModel.hpp"
#include "Matrix.hpp"
#include "ActivationFunction.hpp"

namespace s21 {


	template <typename T>
	class MLPMatrixModel : s21::IMLPModel<T> {
	private:
		std::vector<size_t> units_per_layer;
		std::vector<Matrix<T>> bias;
		std::vector<Matrix<T>> weight_matrices;
		std::vector<Matrix<T>> neuron_values;
		std::vector<Matrix<T>> error;

		float lr;

		explicit MLPMatrixModel(std::vector<size_t> units_per_layer, float lr = .001f): units_per_layer(units_per_layer), lr(lr) {
			for (size_t i = 0; i < units_per_layer.size() - 1; ++i) {
				size_t in_channels = units_per_layer[i];
				size_t out_channels = units_per_layer[i + 1];

				auto W = GenerateNDMatrix<T>(out_channels, in_channels);
				weight_matrices.push_back(W);

				auto b = GenerateNDMatrix<T>(out_channels, 1);
				bias.push_back(b);
			}
			for (size_t i = 0; i < units_per_layer.size(); ++i) {
				neuron_values.push_back(Matrix<T>(units_per_layer[i], 1));
				error.push_back(Matrix<T>(units_per_layer[i], 1));
			}
		}

		static IMLPModel<T> *MakeModel(size_t in_channels, size_t out_channels, size_t hidden_units_per_layer, int hidden_layers, float lr){
			std::vector<size_t> units_per_layer;
			units_per_layer.push_back(in_channels);

			for (int i = 0; i < hidden_layers; ++i) {
				units_per_layer.push_back(hidden_units_per_layer);
			}

			units_per_layer.push_back(out_channels);
			auto *model = new MLPMatrixModel<T>(units_per_layer, lr);
			return model;
		}

	public:
		MLPMatrixModel() = delete;

		MLPMatrixModel &operator=(const MLPMatrixModel<T> matrix) = delete;

		MLPMatrixModel(MLPMatrixModel<T> const &) = delete;


		const std::vector<size_t> &get_units_per_layer() const {
			return units_per_layer;
		}

		const std::vector<Matrix<T>> &get_bias_vectors() const {
			return bias;
		}

		const std::vector<Matrix<T>> &get_weight_matrices() const {
			return weight_matrices;
		}

		const std::vector<Matrix<T>> &get_neuron_values() const {
			return neuron_values;
		}

		float get_lr() const {
			return lr;
		}

		void set_units_per_layer(const std::vector<size_t> &unitsPerLayer) {
			units_per_layer = unitsPerLayer;
			neuron_values.resize(0);
			error.resize(0);

			for (size_t i = 0; i < units_per_layer.size(); ++i) {
				neuron_values.push_back(Matrix<T>(units_per_layer[i], 1));
				error.push_back(Matrix<T>(units_per_layer[i], 1));
			}
			//TODO: add check for setter logic
		}

		void set_lr(float lr) {
			MLPMatrixModel::lr = lr;
		}

		void set_bias(std::vector<Matrix<T>> bias) {
			this->bias = bias;
			//TODO: add check for setter logic
		}

		void set_weight_martices(std::vector<Matrix<T>> weight_matrices) {
			this->weight_matrices = weight_matrices;

			//TODO: add check for setter logic
		}

		void set_neuron_values(std::vector<Matrix<T>> neuron_values) {
			this->neuron_values = neuron_values;
			//TODO: add check for setter logic
		}

//		std::vector<T> Forward(Matrix<T> x) override {
//			assert(std::get<0>(x.get_shape()) == units_per_layer[0] && std::get<1>(x.get_shape()));
//
//			neuron_values[0] = x;
//			Matrix<T> prev(x);
//			for (int i = 0; i < units_per_layer.size() - 1; ++i) {
//				Matrix<T> y = weight_matrices[i].matmul(prev);
//				y = y + bias[i];
//				y = y.apply_function(sigmoid);
//				neuron_values[i + 1] = y;
//				prev = y;
//			}
//			return prev.ToVector();
//		}

		std::vector<T> Forward(Matrix<T> matrix) override {
			std::vector<T>	normalized_vector;
			T				length = 0;

			neuron_values[0] = matrix;
			for (int i = 1; i < units_per_layer.size(); ++i)
				neuron_values[i] = ((weight_matrices[i - 1] * neuron_values[i - 1]) + bias[i - 1]).apply_function(s21::sigmoid);
			normalized_vector = neuron_values.back().ToVector();
			
			for (auto &elem : normalized_vector)
				length += elem * elem;
			// std::cout << length << std::endl;
			// length = std::sqrt(length);
			// for (auto &elem : normalized_vector)
			// 	elem /= length;
			return neuron_values.back().ToVector();
		}

		void Backward(Matrix<T> target) override {
			assert(std::get<0>(target.get_shape()) == units_per_layer.back());

			for (int i = 0; i < units_per_layer.back(); ++i)
				error[units_per_layer.size() - 1](i, 0) = (target(0, i) - neuron_values[units_per_layer.size() - 1](i, 0)) *
						s21::d_sigmoid(neuron_values[units_per_layer.size() - 1](i, 0));
			for (int i = units_per_layer.size() - 2; i > 0; --i) {
				// error[i] = (weight_matrices[i].T() * error[i + 1]).apply_function(d_sigmoid);
				for (int j = 0; j < units_per_layer[i]; ++j)
					error[i](j, 0) *= d_sigmoid(neuron_values[i](j, 0));
			}
			UpdateWeights();
		}


		void UpdateWeights() {
			for (int i = 0; i < units_per_layer.size() - 1; ++i)
				for (int j = 0; j < units_per_layer[i + 1]; ++j)
					for (int k = 0; k < units_per_layer[i]; ++k)
						weight_matrices[i](j, k) += neuron_values[i](k, 0) * error[i + 1](j, 0) * lr;
			for (int i = 0; i < units_per_layer.size() - 1; ++i) {
				for (int j = 0; j < units_per_layer[i + 1]; ++j) {
					bias[i](j, 0) += error[i + 1](j, 0) * lr;
				}
			}
		}

		// void Backward(Matrix<T> target) override {
		// 	assert(std::get<0>(target.get_shape()) == units_per_layer.back());

		// 	Matrix<T> y = target;
		// 	Matrix<T> y_hat = neuron_values.back();
		// 	Matrix<T> diff = y - y_hat;

		// 	for (int i = weight_matrices.size() - 1; i >= 0; --i) {
		// 		Matrix<T> wt = weight_matrices[i].T();
		// 		Matrix<T> prev_errors = wt.matmul( diff);

		// 		Matrix<T> d_outputs = neuron_values[i + 1].apply_function(d_sigmoid);
		// 		Matrix<T> gradients = diff.multiply_elementwise(d_outputs);
		// 		gradients = gradients.multiply_scalar(lr);
		// 		Matrix<T> a_trans = neuron_values[i].T();
		// 		Matrix<T> weight_gradients = gradients.matmul(a_trans);

		// 		bias[i] = bias[i].add(gradients);
		// 		weight_matrices[i] = weight_matrices[i].add(weight_gradients);
		// 		diff = prev_errors;
		// 	}
		// }

		int Train(std::vector<Sample> samples, int groups) override {
			return 0;
		}

		int Test() override {
			return 0;
		}

		int Predict(Matrix<float> x) override {
			return 0;
		}

		static IMLPModel<T> *Instance(size_t in_channels, size_t out_channels, size_t hidden_units_per_layer, int hidden_layers, float _lr){
			static IMLPModel<T> *model = MakeModel(in_channels, out_channels, hidden_units_per_layer, hidden_layers, _lr);
			return model;
		}
	};
}

#endif //SIMPLEMLP_MLPMATRIXMODEL_HPP

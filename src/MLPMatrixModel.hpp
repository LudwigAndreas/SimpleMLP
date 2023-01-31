#ifndef SIMPLEMLP_MLPMATRIXMODEL_HPP
#define SIMPLEMLP_MLPMATRIXMODEL_HPP

#include "IMLPModel.hpp"
#include "Matrix.hpp"

namespace s21 {
	inline auto sigmoid(float x) {
		return 1.0f / (1 + exp(-x));
	}

	inline auto d_sigmoid(float x){
		return (x * (1 - x));
	}

	template <typename T>
	class MLPMatrixModel : s21::IMLPModel<T> {
	private:
		std::vector<size_t> units_per_layer;
		std::vector<Matrix<T>> bias_vectors;
		std::vector<Matrix<T>> weight_matrices;
		std::vector<Matrix<T>> activations;

		float lr;

		explicit MLPMatrixModel(std::vector<size_t> units_per_layer, float lr = .001f): units_per_layer(units_per_layer), lr(lr) {
			for (size_t i = 0; i < units_per_layer.size() - 1; ++i) {
				size_t in_channels = units_per_layer[i];
				size_t out_channels = units_per_layer[i + 1];

				auto W = GenerateNDMatrix<T>(out_channels, in_channels);
				weight_matrices.push_back(W);

				auto b = GenerateNDMatrix<T>(out_channels, 1);
				bias_vectors.push_back(b);

				activations.resize(units_per_layer.size());
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


		const std::vector<size_t> &getUnitsPerLayer() const {
			return units_per_layer;
		}

		const std::vector<Matrix<T>> &getBiasVectors() const {
			return bias_vectors;
		}

		const std::vector<Matrix<T>> &getWeightMatrices() const {
			return weight_matrices;
		}

		const std::vector<Matrix<T>> &getActivations() const {
			return activations;
		}

		float getLr() const {
			return lr;
		}

		virtual std::vector<T> Forward(Matrix<T> x) override {
			assert(std::get<0>(x.get_shape()) == units_per_layer[0] && std::get<1>(x.get_shape()));

			activations[0] = x;
			Matrix<T> prev(x);
			for (int i = 0; i < units_per_layer.size() - 1; ++i) {
				Matrix<T> y = weight_matrices[i].matmul(prev);
				y = y + bias_vectors[i];
				y = y.apply_function(sigmoid);
				activations[i + 1] = y;
				prev = y;
			}
			return prev.ToVector();
		}

		virtual void Backward(Matrix<T> target) override {
			assert(std::get<0>(target.get_shape()) == units_per_layer.back());

			Matrix<T> y = target;
			Matrix<T> y_hat = activations.back();
			Matrix<T> error = y - y_hat;

			for (int i = weight_matrices.size() - 1; i >= 0; --i) {
				Matrix<T> wt = weight_matrices[i].T();
				Matrix<T> prev_errors = wt.matmul(error);

				Matrix<T> d_outputs = activations[i + 1].apply_function(d_sigmoid);
				Matrix<T> gradients = error.multiply_elementwise(d_outputs);
				gradients = gradients.multiply_scalar(lr);
				Matrix<T> a_trans = activations[i].T();
				Matrix<T> weight_gradients = gradients.matmul(a_trans);

				bias_vectors[i] = bias_vectors[i].add(gradients);
				weight_matrices[i] = weight_matrices[i].add(weight_gradients);
				error = prev_errors;
			}
		}

		int Import() override {
			return 0;
		}

		int Export() override {
			return 0;
		}

		int Train() override {
			return 0;
		}

		int Test() override {
			return 0;
		}

		int Predict() override {
			return 0;
		}

		static IMLPModel<T> *Instance(size_t in_channels, size_t out_channels, size_t hidden_units_per_layer, int hidden_layers, float _lr){
			static IMLPModel<T> *model = MakeModel(in_channels, out_channels, hidden_units_per_layer, hidden_layers, _lr);
			return model;
		}
	};
}

#endif //SIMPLEMLP_MLPMATRIXMODEL_HPP

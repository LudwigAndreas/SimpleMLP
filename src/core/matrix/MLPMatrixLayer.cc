#include "MLPMatrixLayer.h"

namespace s21 {

	MLPMatrixLayer::MLPMatrixLayer(Matrix<float> w, Matrix<float> b) : bias(b), weight_matrices(w), is_output_layer(false) {

		error			= Matrix<float>(1, weight_matrices.get_cols());
		neuron_values	= Matrix<float>(1, weight_matrices.get_rows());
		raw				= Matrix<float>(1, weight_matrices.get_rows());
	}

	MLPMatrixLayer::MLPMatrixLayer(int in) : is_output_layer(true) {
		neuron_values	= Matrix<float>(1, in);
		raw				= Matrix<float>(1, in);
	}

	std::istream &operator>>(std::istream &is, MLPMatrixLayer &layer) {
		is >> layer.weight_matrices;
		is >> layer.bias;
		return is;
	}

	std::ostream &operator<<(std::ostream &os, const MLPMatrixLayer &layer) {
		if (!layer.is_output_layer) {
			os << layer.weight_matrices;
			os << layer.bias;
		}
		return os;
	}
}
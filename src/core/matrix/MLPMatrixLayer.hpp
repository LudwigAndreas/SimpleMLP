#ifndef MLPMATRIXLAYER_HPP
#define MLPMATRIXLAYER_HPP

#include "../utils/IMLPLayer.hpp"
#include "../matrix/Matrix.hpp"

namespace s21 {
	struct MLPMatrixLayer : public IMLPLayer {
		MLPMatrixLayer(Matrix<float> w, Matrix<float> b);
		explicit MLPMatrixLayer(int in);

		Matrix<float> bias;
		Matrix<float> weight_matrices;
		Matrix<float> neuron_values;
		Matrix<float> error;
		Matrix<float> raw;
		const bool 	  is_output_layer;
	};

	std::istream &operator>>(std::istream &is, MLPMatrixLayer &layer);
	std::ostream &operator<<(std::ostream &os, const MLPMatrixLayer &layer);
}

#endif
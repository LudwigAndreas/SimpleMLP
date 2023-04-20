#ifndef MLPMATRIXLAYER_HPP
#define MLPMATRIXLAYER_HPP

#include "../utils/IMLPLayer.hpp"
#include "../matrix/Matrix.hpp"

namespace s21 {
	struct MLPMatrixLayer : public IMLPLayer {
		Matrix<float> bias;
		Matrix<float> weight_matrices;
		Matrix<float> neuron_values;
		Matrix<float> incorrect_values;
		Matrix<float> error;
		Matrix<float> raw;
	};

	std::istream &operator>>(std::istream &is, MLPMatrixLayer &layer);
	std::ostream &operator<<(std::ostream &os, const MLPMatrixLayer &layer);
}

#endif
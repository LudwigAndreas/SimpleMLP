#include "MLPMatrixLayer.hpp"

namespace s21 {
	std::istream &operator>>(std::istream &is, MLPMatrixLayer &layer) {
		is >> layer.weight_matrices;
		is >> layer.bias;
		return is;
	}

	std::ostream &operator<<(std::ostream &os, const MLPMatrixLayer &layer) {
		
		return os;
	}
}
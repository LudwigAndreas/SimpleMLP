#include "MLPMatrixLayer.h"

namespace s21 {

MLPMatrixLayer::MLPMatrixLayer(Matrix<float> w, Matrix<float> b)
    : bias(b), weight_matrices(w), is_output_layer(false) {}

MLPMatrixLayer::MLPMatrixLayer() : is_output_layer(true) {}

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
}  // namespace s21
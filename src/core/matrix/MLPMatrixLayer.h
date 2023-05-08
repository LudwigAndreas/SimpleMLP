#ifndef MLPMATRIXLAYER_H
#define MLPMATRIXLAYER_H

#include "../matrix/Matrix.h"
#include "../utils/IMLPLayer.h"

namespace s21 {
struct MLPMatrixLayer : public IMLPLayer {
  MLPMatrixLayer(Matrix<float> w, Matrix<float> b);
  MLPMatrixLayer();

  Matrix<float> bias;
  Matrix<float> weight_matrices;
  Matrix<float> neuron_values;
  Matrix<float> error;
  Matrix<float> raw;
  const bool is_output_layer;
};

std::istream &operator>>(std::istream &is, MLPMatrixLayer &layer);
std::ostream &operator<<(std::ostream &os, const MLPMatrixLayer &layer);
} // namespace s21

#endif

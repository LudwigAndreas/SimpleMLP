#ifndef SIMPLEMLP_AFLIBRARY_H
#define SIMPLEMLP_AFLIBRARY_H

#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>

namespace s21 {
  float linear(float x);
  float d_linear(float x);

  float sigmoid(float x);
  float d_sigmoid(float x);

  float bsigmoid(float x);
  float d_bsigmoid(float x);

  float relu(float x);
  float d_relu(float x);

  float bounded_linear(float x);
  float d_bounded_linear(float x);

  std::vector<float> softmax(std::vector<float> matrix);
}
#endif  //SIMPLEMLP_AFLIBRARY_H

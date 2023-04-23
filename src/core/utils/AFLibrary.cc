#include "AFLibrary.h"

namespace s21 {
  std::vector<float> softmax(std::vector<float> matrix) {
    std::vector<float>	values;
    float	sum;

    for (auto val : matrix)
      values.push_back(std::exp(val));
    sum = std::accumulate(values.begin(), values.end(), 0.);
    std::transform(values.begin(), values.end(),
                   values.begin(), [sum](float x){ return x / sum; });
    return {values};
  }

  float linear(float x) {
    return x;
  }

  float d_linear(float x) {
    return 1;
  }

  float sigmoid(float x) {
    return 1.0f / (1 + std::exp(-x));
  }

  float d_sigmoid(float x){
    return std::exp(x) / ((std::exp(x) + 1) * (std::exp(x) + 1));
  }

  float bsigmoid(float x) {
    return 2.0f / (1 + std::exp(-x)) - 1;
  }

  float d_bsigmoid(float x){
    return (2 * d_sigmoid(x));
  }

  float relu(float x) {
    if (x >= 0) {
      return x;
    } else {
      return x * 0.01f;
    }
  }

  float d_relu(float x) {
    if (x >= 0) {
      return 1;
    } else {
      return 0.01;
    }
  }

  float bounded_linear(float x) {
    if (x < -1)
      return -1;
    if (x > 1)
      return 1;
    return x;
  }

  float d_bounded_linear(float x) {
    if (x < -1 || x > 1)
      return 0;
    return 1;
  }
}
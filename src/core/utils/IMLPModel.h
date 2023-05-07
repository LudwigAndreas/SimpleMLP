#ifndef IMLPMODEL_H
#define IMLPMODEL_H

#include <vector>

#include "ActivationFunction.h"
#include "IMLPLayer.h"
#include "Sample.h"

namespace s21 {
class IMLPModel {
 protected:
 public:
  virtual std::vector<float> Forward(Matrix<float>) = 0;
  virtual void Backward(Matrix<float>) = 0;
  virtual int Predict(Matrix<float>) = 0;

  int GetMostProbablePrediction(std::vector<float> value) {
    double max = value[0];
    int prediction = 0;
    double tmp;
    for (size_t j = 1; j < value.size(); ++j) {
      tmp = value[j];
      if (tmp > max) {
        prediction = j;
        max = tmp;
      }
    }
    return prediction;  // +1 for dataset (who tf thought that it would be a
                        // good idea to numerate dataset choices from 1 and not
                        // from 0)
  }
  virtual ~IMLPModel() {}
};
}  // namespace s21

#endif
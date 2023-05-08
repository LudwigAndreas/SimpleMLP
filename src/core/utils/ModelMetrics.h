#ifndef SIMPLEMLP_MODELMETRICS_H
#define SIMPLEMLP_MODELMETRICS_H

#include <vector>

#include "ConfusionMatrix.h"
namespace s21 {

float CalculateRecall(std::vector<s21::ConfusionMatrix> *result, int size);

float CalculatePrecision(std::vector<s21::ConfusionMatrix> *result, int size);

float CalculateAccuracy(std::vector<s21::ConfusionMatrix> *result, int size);

int CalculateSize(std::vector<s21::ConfusionMatrix> *result);
} // namespace s21
#endif // SIMPLEMLP_MODELMETRICS_H

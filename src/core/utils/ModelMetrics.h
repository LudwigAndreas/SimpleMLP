#ifndef SIMPLEMLP_MODELMETRICS_H
#define SIMPLEMLP_MODELMETRICS_H

#include <vector>

#include "ConfusionMatrix.h"
namespace s21 {

float calculate_recall(std::vector<s21::ConfusionMatrix> *result, int size);

float calculate_precision(std::vector<s21::ConfusionMatrix> *result, int size);

float calculate_accuracy(std::vector<s21::ConfusionMatrix> *result, int size);

int calculate_size(std::vector<s21::ConfusionMatrix> *result);
} // namespace s21
#endif // SIMPLEMLP_MODELMETRICS_H

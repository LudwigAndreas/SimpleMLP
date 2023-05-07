#include "ModelMetrics.h"
namespace s21 {
float CalculateRecall(std::vector<s21::ConfusionMatrix> *result, int size) {
  float recall = 0;
  for (auto &i : *result) {
    if (i.tp + i.fn != 0)
      recall += (float)(i.tp * (i.tp + i.fn)) / (i.tp + i.fn);
  }
  return ((float)recall / size) * 100;
}

float CalculatePrecision(std::vector<s21::ConfusionMatrix> *result, int size) {
  float precision = 0;
  for (auto &i : *result) {
    if (i.tp + i.fp != 0)
      precision += (float)(i.tp * (i.tp + i.fn)) / (i.tp + i.fp);
  }
  return ((float)precision / size) * 100;
}

float CalculateAccuracy(std::vector<s21::ConfusionMatrix> *result, int size) {
  int tp = 0;
  for (auto conf_matrix : *result) {
    tp += conf_matrix.tp;
  }
  return ((float)tp / (size * result->size())) * 100;
}

int CalculateSize(std::vector<s21::ConfusionMatrix> *result) {
  if (result != nullptr && result->size() > 1) {
    int size = 0;
    size += result[0].data()->tp;
    size += result[0].data()->fp;
    size += result[0].data()->tn;
    size += result[0].data()->fn;
    return size;
  }
  return -1;  // TODO exception
}
}  // namespace s21
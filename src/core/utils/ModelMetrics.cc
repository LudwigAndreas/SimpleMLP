#include "ModelMetrics.h"
namespace s21 {
float calculate_recall(std::vector<s21::ConfusionMatrix> *result, int size) {
    float recall = 0;
    for (auto &i : *result) {
        if (i.tp + i.fn != 0)
            recall += (float)(i.tp * (i.tp + i.fn)) / (i.tp + i.fn);
    }
    return ((float)recall / size) * 100;
}

float calculate_precision(std::vector<s21::ConfusionMatrix> *result, int size) {
    float precision = 0;
    for (auto &i : *result) {
        if (i.tp + i.fp != 0)
            precision += (float)(i.tp * (i.tp + i.fn)) / (i.tp + i.fp);
    }
    return ((float)precision / size) * 100;
}

float calculate_accuracy(std::vector<s21::ConfusionMatrix> *result, int size) {
    int tp = 0;
    int tn = 0;
    for (auto conf_matrix : *result) {
        tp += conf_matrix.tp;
        tn += conf_matrix.tn;
    }
    return ((float)tp / (size * result->size())) * 100;
}

int calculate_size(std::vector<s21::ConfusionMatrix> *result) {
    if (result != nullptr && result->size() > 1) {
        int size = 0;
        size += result[0].data()->tp;
        size += result[0].data()->fp;
        size += result[0].data()->tn;
        size += result[0].data()->fn;
        return size;
    }
    return -1; // TODO exception
}
} // namespace s21
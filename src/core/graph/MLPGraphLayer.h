#ifndef MLPGRAPHLAYER_H
#define MLPGRAPHLAYER_H

#include <algorithm>
#include <sstream>
#include <vector>

#include "../exceptions/UploadFileException.h"
#include "../matrix/Matrix.h"
#include "../utils/ActivationFunction.h"
#include "MLPGraphNode.h"

namespace s21 {
class MLPGraphLayer {
private:
    MLPGraphLayer *input;
    MLPGraphLayer *output;
    size_t size;
    ActivationFunction af;

    std::vector<MLPGraphNode> neurons;

public:
    MLPGraphLayer(size_t size, const ActivationFunction &af,
                  MLPGraphLayer *input = nullptr,
                  MLPGraphLayer *output = nullptr);

    MLPGraphLayer(MLPGraphLayer &) = default;
    MLPGraphLayer(MLPGraphLayer &&) = default;
    MLPGraphLayer &operator=(MLPGraphLayer &) = default;

    void GenerateLayer();

    const MLPGraphNode &operator[](int index) const;
    MLPGraphNode &operator[](int index);

    void set_layer_values(Matrix<float> &values);
    void set_error(Matrix<float> &target);

    void set_input_layer(MLPGraphLayer *input);
    void set_output_layer(MLPGraphLayer *output);

    std::vector<float> get_resulting_vector();

    void CalculateLayer(ActivationFunction &af);
    void CalculateError(std::vector<float> *target = nullptr);
    void UpdateWeights(float lr);

    size_t InputSize() const;
    size_t Size() const;
};

std::istream &operator>>(std::istream &is, MLPGraphLayer &layer);

std::ostream &operator<<(std::ostream &os, const MLPGraphLayer &layer);
}  // namespace s21

#endif
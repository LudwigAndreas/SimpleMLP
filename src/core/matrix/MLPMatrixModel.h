#ifndef SIMPLEMLP_MLPMATRIXMODEL2_HPP
#define SIMPLEMLP_MLPMATRIXMODEL2_HPP

#include <algorithm>
#include <fstream>

#include "../utils/ActivationFunction.hpp"
#include "../utils/IMLPModel.hpp"
#include "MLPMatrixLayer.hpp"
#include "Matrix.hpp"

namespace s21 {

class MLPMatrixModel : public s21::IMLPModel {
 private:
  std::vector<size_t> units_per_layer;
  std::vector<MLPMatrixLayer*> layers;
  bool auto_decrease;

  ActivationFunction* af;
  float lr;
  float start_lr;

  explicit MLPMatrixModel(std::vector<size_t> units_per_layer,
                          ActivationFunction* func,
                          bool use_auto_decrease = true, float lr = .05f)
      : units_per_layer(units_per_layer),
        auto_decrease(use_auto_decrease),
        lr(lr) {
    af = func;
    start_lr = lr;

    for (size_t i = 0; i < units_per_layer.size(); ++i) {
      MLPMatrixLayer* layer = nullptr;
      size_t in_channels = units_per_layer[i];
      if (i != units_per_layer.size() - 1) {
        size_t out_channels = units_per_layer[i + 1];
        layer = new MLPMatrixLayer(
            GenerateNDMatrix<float>(in_channels, out_channels),
            GenerateNDMatrix<float>(1, out_channels));
      } else {
        layer = new MLPMatrixLayer(in_channels);
      }
      layers.push_back(layer);
    }
  }

 public:
  [[nodiscard]] const std::vector<size_t>& get_units_per_layer() const {
    return units_per_layer;
  }

  void set_units_per_layer(const std::vector<size_t>& upl) {
    this->units_per_layer = upl;
  }

  void SetLayers(std::vector<MLPMatrixLayer*> l) {
    this->layers = l;
    //TODO: add check for setter logic
  }

  [[nodiscard]] const std::vector<MLPMatrixLayer*>& GetLayers() const {
    return layers;
    //TODO: add check for setter logic
  }

  [[nodiscard]] float get_lr() const { return lr; }

  int Predict(Matrix<float> x) override {
    return getMostProbablePrediction(Forward(x));
  }
  void set_lr(float lr) { MLPMatrixModel::lr = lr; }

  std::vector<float> Forward(Matrix<float> matrix) override {
    assert(std::get<1>(matrix.get_shape()) == units_per_layer[0] &&
           std::get<1>(matrix.get_shape()));
    layers[0]->neuron_values = matrix;
    layers[0]->raw = matrix;
    for (int i = 0; i < units_per_layer.size() - 1; ++i) {
      Matrix<float> y = layers[i]->neuron_values * layers[i]->weight_matrices;
      y = y + layers[i]->bias;
      layers[i + 1]->raw = y;
      y = y.apply_function(af->getFunction());
      layers[i + 1]->neuron_values = y;
    }
    return softmax(layers.back()->neuron_values.ToVector());
  }

  void Backward(Matrix<float> target) override {
    assert(std::get<1>(target.get_shape()) == units_per_layer.back());
    layers[layers.size() - 2]->error = (layers.back()->neuron_values - target);
    for (int i = (int)units_per_layer.size() - 3; i >= 0; --i) {
      layers[i]->error = (layers[i + 1]->error.matmulTransposed(
                             layers[i + 1]->weight_matrices)) &
                         layers[i + 1]->raw.apply_function(af->getDerivative());
    }
    for (size_t i = 0; i < units_per_layer.size() - 1; ++i) {
      layers[i]->weight_matrices =
          layers[i]->weight_matrices -
          (layers[i]->neuron_values.T() * layers[i]->error * lr);
      layers[i]->bias = layers[i]->bias - layers[i]->error * lr;
    }
  }

  float TestOutput(std::vector<s21::Sample> samples, bool silent_mode = false,
                   std::string filename = "") override {
    std::fstream output;
    int correct_guesses = 0;
    float accuracy;
    std::vector<float> y_hat;
    int index;

    if (!filename.empty())
      output.open(filename, std::ofstream::out | std::ofstream::trunc);
    for (auto& sample : samples) {
      y_hat = Forward(sample.x);
      index = getMostProbablePrediction(y_hat);
      if (index == getMostProbablePrediction(sample.y.ToVector()))
        ++correct_guesses;
      //				if (output.is_open())
      //					log(output, getMostProbablePrediction(sample.y.ToVector()), index, y_hat[index]);
    }
    accuracy = ((float)correct_guesses / samples.size());
    if (!silent_mode)
      std::cerr << "Test: " << accuracy * 100 << "% accuracy" << std::endl;
    return accuracy;
  }

  static IMLPModel* MakeModel(size_t in_channels, size_t out_channels,
                              size_t hidden_units_per_layer, int hidden_layers,
                              float lr, ActivationFunction* func,
                              bool use_auto_decrease = true) {
    std::vector<size_t> units_per_layer;
    units_per_layer.push_back(in_channels);

    for (int i = 0; i < hidden_layers; ++i)
      units_per_layer.push_back(hidden_units_per_layer);

    units_per_layer.push_back(out_channels);
    auto* model =
        new MLPMatrixModel(units_per_layer, func, use_auto_decrease, lr);
    return model;
  }
};

std::istream& operator>>(std::istream& is, MLPMatrixModel& model);

std::ostream& operator<<(std::ostream& os, const MLPMatrixModel& model);
}  // namespace s21

#endif
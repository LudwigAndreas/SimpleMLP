#ifndef MLPGRAPHMODEL_H
#define MLPGRAPHMODEL_H (x)

#include <fstream>

#include "../DatasetReading.h"
#include "../graph/MLPGraphLayer.h"
#include "../utils/ActivationFunction.h"
#include "../utils/IMLPModel.h"

namespace s21 {
typedef float T;

class MLPGraphModel : public IMLPModel {
private:
  std::vector<size_t> units_per_layer;
  ActivationFunction af;
  bool auto_decrease;
  float lr;
  float start_lr;
  std::vector<MLPGraphLayer *> layers;

public:
  explicit MLPGraphModel(std::vector<size_t> units_per_layer,
                         const ActivationFunction &func,
                         bool use_auto_decrease = true, float lr = .05f);

  MLPGraphModel() : af(ActivationFunction()) {}

  ~MLPGraphModel() {
    for (auto layer : layers)
      delete layer;
  }

  MLPGraphLayer *AddLayer(MLPGraphLayer *layer);

  const std::vector<size_t> &get_units_per_layer() const;
  void set_units_per_layer(const std::vector<size_t> &unitsPerLayer);

  const std::vector<MLPGraphLayer *> &get_layers() const;
  void set_layers(const std::vector<MLPGraphLayer *> &layers);

  const ActivationFunction &get_af() const;
  void set_af(ActivationFunction &af);

  float get_start_lr() const;
  void set_start_lr(float startLr);

  float get_lr() const;
  void set_lr(float lr);

  bool is_auto_decrease() const;
  void set_auto_decrease(bool auto_decrease);

  std::vector<MLPGraphLayer *> &get_layers();
  static IMLPModel *MakeModel(size_t in_channels, size_t out_channels,
                              size_t hidden_units_per_layer, int hidden_layers,
                              float lr, ActivationFunction func,
                              bool use_auto_decrease = true);

  virtual std::vector<T> Forward(Matrix<T>);
  virtual void Backward(Matrix<T>);
  virtual float Train(DatasetGroup samples, bool b = false);
  virtual float Test(DatasetGroup samples, bool b = false);
  virtual int Predict(Matrix<float>);
};

std::istream &operator>>(std::istream &is, MLPGraphModel &model);
std::ostream &operator<<(std::ostream &os, MLPGraphModel &model);
} // namespace s21

#endif

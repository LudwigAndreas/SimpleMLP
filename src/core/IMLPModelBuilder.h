#ifndef SIMPLEMLP_IMLPMODELBUILDER_H
#define SIMPLEMLP_IMLPMODELBUILDER_H

#include "utils/ActivationFunction.h"
#include "utils/IMLPModel.h"

namespace s21 {
class IMLPModelBuilder {
 public:
  enum PerceptronBase { Matrix = 1, Graph = 2 };

  virtual ~IMLPModelBuilder() = default;
  virtual IMLPModelBuilder *PerceptionBase(PerceptronBase flag) = 0;
  virtual IMLPModelBuilder *HiddenLayers(int hidden_layers) = 0;
  virtual IMLPModelBuilder *ActivationFunc(ActivationFunction::Flags flag) = 0;
  virtual IMLPModelBuilder *HiddenUnitsPerLayer(int hidden_units_per_layer) = 0;
  virtual IMLPModelBuilder *LearningRate(float learning_rate,
                                         bool use_auto_decrease) = 0;
  virtual void Reset() = 0;
  virtual IMLPModel *GetResult() = 0;
};
}  // namespace s21

#endif

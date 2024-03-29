#ifndef SIMPLEMLP_LETTERRECOGNITIONMLPMODELBUILDER_HPP
#define SIMPLEMLP_LETTERRECOGNITIONMLPMODELBUILDER_HPP

#include "IMLPModelBuilder.h"

namespace s21 {
class LetterRecognitionMLPModelBuilder : IMLPModelBuilder {
  PerceptronBase base;
  int hidden_layers;
  ActivationFunction func;
  int hidden_units_per_layer;
  float learning_rate;
  bool use_auto_decrease;

  static const int in_channels = 28 * 28;
  static const int out_channels = 26;

 public:
  LetterRecognitionMLPModelBuilder();

  ~LetterRecognitionMLPModelBuilder();

  LetterRecognitionMLPModelBuilder *PerceptionBase(
      PerceptronBase flag) override;

  LetterRecognitionMLPModelBuilder *PerceptionBase(const std::string base);

  LetterRecognitionMLPModelBuilder *HiddenLayers(int hidden_layers) override;

  LetterRecognitionMLPModelBuilder *ActivationFunc(
      ActivationFunction::Flags flag) override;

  LetterRecognitionMLPModelBuilder *ActivationFunc(const std::string func_name);

  LetterRecognitionMLPModelBuilder *HiddenUnitsPerLayer(
      int hidden_units_per_layer) override;

  LetterRecognitionMLPModelBuilder *LearningRate(
      float learning_rate, bool use_auto_decrease) override;

  IMLPModel *GetResult() override;

  void Reset() override;
};
}  // namespace s21

#endif  // SIMPLEMLP_LETTERRECOGNITIONMLPMODELBUILDER_HPP

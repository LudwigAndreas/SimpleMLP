#include <vector>

#include "core/matrix/MLPMatrixModel.h"
#include "gtest/gtest.h"

TEST(MLPMatrixModelTest, InitializationTest) {
  s21::ActivationFunction af = s21::ActivationFunction::Flags::Sigmoid;
  int in_channels = 2;
  int out_channels = 1;
  int hidden_layers = 2;
  int units_per_layer = 4;
  float lr = 0.1f;

  s21::MLPMatrixModel *model =
      static_cast<s21::MLPMatrixModel *>(s21::MLPMatrixModel::MakeModel(
          in_channels, out_channels, units_per_layer, hidden_layers, lr, af));
  EXPECT_EQ(model->get_units_per_layer().at(1), units_per_layer);
  EXPECT_EQ(model->get_af(), af);
  EXPECT_EQ(model->get_lr(), lr);
  EXPECT_EQ(model->get_units_per_layer().front(), in_channels);
  EXPECT_EQ(model->get_units_per_layer().back(), out_channels);
  EXPECT_EQ(model->get_layers().size() - 2, hidden_layers);
  delete model;
}

TEST(MLPMatrixModelTest, ForwardTest) {
  s21::ActivationFunction af = s21::ActivationFunction::Sigmoid;
  float lr = 0.1f;

  auto model = s21::MLPMatrixModel::MakeModel(2, 2, 3, 1, lr, af, true);
  s21::Matrix<float> input = s21::Matrix<float>({0.5, 0.5}, 1, 2);
  auto output = model->Forward(input);

  EXPECT_EQ(output.size(), 2);
  for (const auto &o : output) {
    EXPECT_GE(o, 0.0f);
    EXPECT_LE(o, 1.0f);
  }
  EXPECT_FLOAT_EQ(std::accumulate(output.begin(), output.end(), 0.f), 1);
  delete model;
}

TEST(MLPMatrixModelTest, BackwardTest) {
  s21::ActivationFunction af = s21::ActivationFunction::Sigmoid;
  float lr = 0.1f;

  s21::MLPMatrixModel *model = static_cast<s21::MLPMatrixModel *>(
      s21::MLPMatrixModel::MakeModel(2, 2, 3, 1, lr, af, true));
  s21::Matrix<float> input = s21::Matrix<float>({0.5, 0.5}, 1, 2);
  s21::Matrix<float> target = s21::Matrix<float>({1, 0}, 1, 2);
  std::vector<s21::Matrix<float>> weights;
  std::vector<s21::Matrix<float>> biases;
  for (auto it = model->get_layers().begin();
       it < model->get_layers().end() - 1; ++it) {
    weights.push_back((*it)->weight_matrices);
    biases.push_back((*it)->bias);
  }
  model->Forward(input);
  model->Backward(target);

  for (size_t i = 0; i < model->get_layers().size() - 1; ++i) {
    EXPECT_NE(model->get_layers()[i]->weight_matrices, weights[i]);
    EXPECT_NE(model->get_layers()[i]->bias, biases[i]);
  }
  delete model;
}

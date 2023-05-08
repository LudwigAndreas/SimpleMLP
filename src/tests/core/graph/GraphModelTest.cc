#include <vector>

#include "core/graph/MLPGraphModel.h"
#include "core/matrix/Matrix.h"
#include "gtest/gtest.h"

TEST(MLPGraphModelTest, InitializationTest) {
    s21::ActivationFunction af = s21::ActivationFunction::Sigmoid;
    std::vector<size_t> units_per_layer{2, 4, 4, 1};
    float lr = 0.1f;

    s21::MLPGraphModel *model =
        new s21::MLPGraphModel(units_per_layer, af, true, lr);
    EXPECT_EQ(model->get_units_per_layer(), units_per_layer);
    EXPECT_EQ(model->get_af(), af);
    EXPECT_EQ(model->get_lr(), lr);
    EXPECT_TRUE(model->is_auto_decrease());
    delete model;
}

TEST(MLPGraphModelTest, ForwardTest) {
    s21::ActivationFunction af = s21::ActivationFunction::Sigmoid;
    std::vector<size_t> units_per_layer{2, 4, 4, 2};
    float lr = 0.1f;

    s21::MLPGraphModel *model =
        new s21::MLPGraphModel(units_per_layer, af, true, lr);
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

TEST(MLPGraphModelTest, BackwardTest) {
    s21::ActivationFunction af = s21::ActivationFunction::Sigmoid;
    std::vector<size_t> units_per_layer{2, 4, 4, 2};
    float lr = 0.1f;

    s21::MLPGraphModel *model =
        new s21::MLPGraphModel(units_per_layer, af, true, lr);
    s21::Matrix<float> input = s21::Matrix<float>({0.5, 0.5}, 1, 2);
    s21::Matrix<float> target = s21::Matrix<float>({1, 0}, 1, 2);
    auto output = model->Forward(input);
    model->Backward(target);
    auto new_output = model->Forward(input);
    EXPECT_NE(output, new_output);
    delete model;
}

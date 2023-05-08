#include <vector>

#include "core/graph/MLPGraphModel.h"
#include "core/matrix/Matrix.h"
#include "gtest/gtest.h"

TEST(MLPGraphLayerTest, InitializationTest) {
    s21::ActivationFunction af = s21::ActivationFunction::Sigmoid;
    size_t size = 4;
    auto vals = s21::Matrix<float>({1, 2, 3, 4}, 1, 4);

    auto layer = new s21::MLPGraphLayer(4, af);
    layer->GenerateLayer();
    EXPECT_EQ(layer->Size(), size);

    layer->set_layer_values(vals);
    for (size_t i = 0; i < layer->Size(); ++i) {
        EXPECT_EQ((*layer)[i].value, i + 1);
    }
    delete layer;
}

TEST(MLPGraphLayerTest, ResultingVector) {
    s21::ActivationFunction af = s21::ActivationFunction::Sigmoid;
    size_t size = 4;
    auto vals = s21::Matrix<float>({1, 2, 3, 4}, 1, 4);

    auto layer = new s21::MLPGraphLayer(4, af);
    layer->GenerateLayer();
    EXPECT_EQ(layer->Size(), size);

    layer->set_layer_values(vals);
    auto resulting_vector = layer->get_resulting_vector();
    for (size_t i = 0; i < layer->Size(); ++i) {
        EXPECT_EQ((*layer)[i].value, resulting_vector[i]);
    }
    delete layer;
}

TEST(MLPGraphLayerTest, CalculateLayer) {
    s21::ActivationFunction af = s21::ActivationFunction::Sigmoid;
    auto vals = s21::Matrix<float>({1, 2, 3, 4}, 1, 4);
    auto outvals = s21::Matrix<float>({1, 2}, 1, 2);

    auto layer = new s21::MLPGraphLayer(4, af);
    auto out_layer = new s21::MLPGraphLayer(2, af, layer);
    layer->set_output_layer(out_layer);
    layer->GenerateLayer();
    out_layer->GenerateLayer();
    EXPECT_EQ(layer->Size(), 4);
    EXPECT_EQ(out_layer->InputSize(), 4);
    EXPECT_EQ(out_layer->Size(), 2);

    layer->set_layer_values(vals);
    out_layer->set_layer_values(outvals);
    out_layer->CalculateLayer(af);
    auto resulting_vector = out_layer->get_resulting_vector();
    for (size_t i = 0; i < out_layer->Size(); ++i) {
        EXPECT_NE(outvals[i], resulting_vector[i]);
    }
    delete layer;
    delete out_layer;
}

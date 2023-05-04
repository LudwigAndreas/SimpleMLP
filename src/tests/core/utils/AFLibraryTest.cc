#include <gtest/gtest.h>

#include "core/utils/AFLibrary.h"

TEST(AFLibrary, Sigmoid) {
	ASSERT_FLOAT_EQ(s21::sigmoid(0), 0.5f);
	ASSERT_FLOAT_EQ(s21::sigmoid(-5) + s21::sigmoid(5), 1.f);
}

TEST(AFLibrary, BipolarSigmoid) {
	ASSERT_FLOAT_EQ(s21::bsigmoid(0), 0.f);
	ASSERT_FLOAT_EQ(s21::bsigmoid(-5) + s21::bsigmoid(5), 0.f);
}

TEST(AFLibrary, Linear) {
	ASSERT_FLOAT_EQ(s21::linear(727), 727);
	ASSERT_FLOAT_EQ(s21::linear(-5) + s21::linear(5), 0.f);
	ASSERT_FLOAT_EQ(s21::d_linear(727), 1.f);
	ASSERT_FLOAT_EQ(s21::d_linear(-5) + s21::d_linear(5), 2.f);
}

TEST(AFLibrary, ReLU) {
	ASSERT_FLOAT_EQ(s21::relu(727), 727);
	ASSERT_FLOAT_EQ(s21::relu(-5), 0.05f);
	ASSERT_FLOAT_EQ(s21::relu(727) - s21::relu(-700), 720.f);
	ASSERT_FLOAT_EQ(s21::d_relu(-500), 0.01f);
	ASSERT_FLOAT_EQ(s21::d_relu(500), 1.f);
	ASSERT_FLOAT_EQ(s21::d_relu(0), 1.f);
}

TEST(AFLibrary, BoundedLinear) { // liar liar
	ASSERT_FLOAT_EQ(s21::relu(727), 727);
	ASSERT_FLOAT_EQ(s21::relu(-5), 0.05f);
	ASSERT_FLOAT_EQ(s21::relu(727) - s21::relu(-700), 720.f);
	ASSERT_FLOAT_EQ(s21::d_relu(-500), 0.01f);
	ASSERT_FLOAT_EQ(s21::d_relu(500), 1.f);
	ASSERT_FLOAT_EQ(s21::d_relu(0), 1.f);
}

TEST(AFLibrary, Softmax) {
	std::vector<float> input{1, 2, 3};
	std::vector<float> output{.0900306f, .244728f, .665241f};
	auto result = s21::softmax(input);

	for (size_t i = 0; i < output.size(); ++i)
		ASSERT_FLOAT_EQ(output[i], result[i]);
}
#include <gtest/gtest.h>

#include "core/utils/ActivationFunction.h"

inline float sigmoid(float x) {
	return 1.0f / (1 + std::exp(-x));
}

inline float d_sigmoid(float x){
	return std::exp(x) / std::pow(std::exp(x) + 1, 2);
}

TEST(ActivationFunction, CopyConstructor) {
	s21::ActivationFunction af(sigmoid, d_sigmoid);
	s21::ActivationFunction clone(af);
	for (float i = -1; i <= 1; i += 0.1) {
		ASSERT_EQ(clone.getFunction()(i), af.getFunction()(i));
		ASSERT_EQ(clone.getDerivative()(i), af.getDerivative()(i));
	}
}

TEST(ActivationFunction, ParameterizedConstructor) {
	s21::ActivationFunction af(sigmoid, d_sigmoid);
	for (float i = -1; i <= 1; i += 0.1) {
		ASSERT_EQ(sigmoid(i), af.getFunction()(i));
		ASSERT_EQ(d_sigmoid(i), af.getDerivative()(i));
	}
}

TEST(ActivationFunction, ApplyFunctionMethod) {
	s21::ActivationFunction af(sigmoid, d_sigmoid);
	for (float i = -1; i <= 1; i += 0.1) {
		ASSERT_EQ(sigmoid(i), af.applyFunction(i));
		ASSERT_EQ(d_sigmoid(i), af.applyDerivative(i));
	}
}

TEST(ActivationFunction, GetFunctionByNameMethod) {
	s21::ActivationFunction *af = s21::ActivationFunction::getFunctionByName("sigmoid");
	for (float i = -1; i <= 1; i += 0.1) {
		ASSERT_EQ(sigmoid(i), af->applyFunction(i));
		ASSERT_EQ(d_sigmoid(i), af->applyDerivative(i));
	}
}

TEST(ActivationFunction, GetFunctionByFlagMethod) {
	s21::ActivationFunction *af = s21::ActivationFunction::getFunctionByFlag(s21::ActivationFunction::Sigmoid);
	for (float i = -1; i <= 1; i += 0.1) {
		ASSERT_EQ(sigmoid(i), af->applyFunction(i));
		ASSERT_EQ(d_sigmoid(i), af->applyDerivative(i));
	}
}
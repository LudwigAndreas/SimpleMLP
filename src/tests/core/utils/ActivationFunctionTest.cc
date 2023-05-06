#include <gtest/gtest.h>

#include "core/utils/ActivationFunction.h"

TEST(ActivationFunction, GetFunctionByFlagMethod) {
    s21::ActivationFunction af = s21::ActivationFunction(s21::ActivationFunction::Sigmoid);
    ASSERT_EQ(s21::sigmoid, af.getFunction());
    ASSERT_EQ(s21::d_sigmoid, af.getDerivative());
    for (float i = -1; i <= 1; i += 0.1) {
        ASSERT_EQ(s21::sigmoid(i), af.applyFunction(i));
        ASSERT_EQ(s21::d_sigmoid(i), af.applyDerivative(i));
    }
}

TEST(ActivationFunction, GetFunctionByNameMethod) {
    s21::ActivationFunction af = s21::ActivationFunction("linear");
    for (float i = -1; i <= 1; i += 0.1) {
        ASSERT_EQ(s21::linear(i), af.applyFunction(i));
        ASSERT_EQ(s21::d_linear(i), af.applyDerivative(i));
    }
}

TEST(ActivationFunction, GetFunctionByNoArguments) {
    s21::ActivationFunction af = s21::ActivationFunction();
    for (float i = -1; i <= 1; i += 0.1) {
        ASSERT_EQ(s21::sigmoid(i), af.applyFunction(i));
        ASSERT_EQ(s21::d_sigmoid(i), af.applyDerivative(i));
    }
}

TEST(ActivationFunction, CopyConstructor) {
    s21::ActivationFunction af(s21::ActivationFunction::Flags::BipolarSigmoid);
    s21::ActivationFunction clone(af);
    for (float i = -1; i <= 1; i += 0.1) {
        ASSERT_EQ(clone.applyFunction(i), af.applyFunction(i));
        ASSERT_EQ(clone.applyFunction(i), af.applyDerivative(i));
    }
}

TEST(ActivationFunction, GetFunction) {
    s21::ActivationFunction af(s21::ActivationFunction::Flags::BipolarSigmoid);
    for (float i = -1; i <= 1; i += 0.1) {
        ASSERT_EQ(af.getFunction()(i), af.applyFunction(i));
        ASSERT_EQ(af.getDerivative()(i), af.applyDerivative(i));
    }
}

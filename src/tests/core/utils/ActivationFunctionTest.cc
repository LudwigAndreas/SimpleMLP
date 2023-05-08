#include <gtest/gtest.h>

#include "core/utils/ActivationFunction.h"

TEST(ActivationFunction, GetFunctionByFlagMethod) {
    s21::ActivationFunction af =
        s21::ActivationFunction(s21::ActivationFunction::Sigmoid);
    ASSERT_EQ(s21::sigmoid, af.GetFunction());
    ASSERT_EQ(s21::d_sigmoid, af.GetDerivative());
    for (float i = -1; i <= 1; i += 0.1) {
        ASSERT_EQ(s21::sigmoid(i), af.ApplyFunction(i));
        ASSERT_EQ(s21::d_sigmoid(i), af.ApplyDerivative(i));
    }
}

TEST(ActivationFunction, GetFunctionByNameMethod) {
    s21::ActivationFunction af = s21::ActivationFunction("linear");
    for (float i = -1; i <= 1; i += 0.1) {
        ASSERT_EQ(s21::linear(i), af.ApplyFunction(i));
        ASSERT_EQ(s21::d_linear(i), af.ApplyDerivative(i));
    }
}

TEST(ActivationFunction, GetFunctionByNoArguments) {
    s21::ActivationFunction af = s21::ActivationFunction();
    for (float i = -1; i <= 1; i += 0.1) {
        ASSERT_EQ(s21::sigmoid(i), af.ApplyFunction(i));
        ASSERT_EQ(s21::d_sigmoid(i), af.ApplyDerivative(i));
    }
}

TEST(ActivationFunction, CopyConstructor) {
    s21::ActivationFunction af(s21::ActivationFunction::Flags::BipolarSigmoid);
    s21::ActivationFunction clone(af);
    for (float i = -1; i <= 1; i += 0.1) {
        ASSERT_EQ(clone.ApplyFunction(i), af.ApplyFunction(i));
        ASSERT_EQ(clone.ApplyFunction(i), af.ApplyDerivative(i));
    }
}

TEST(ActivationFunction, GetFunction) {
    s21::ActivationFunction af(s21::ActivationFunction::Flags::BipolarSigmoid);
    for (float i = -1; i <= 1; i += 0.1) {
        ASSERT_EQ(af.GetFunction()(i), af.ApplyFunction(i));
        ASSERT_EQ(af.GetDerivative()(i), af.ApplyDerivative(i));
    }
}

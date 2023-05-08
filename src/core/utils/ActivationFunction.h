#ifndef ACTIVATIONFUNCTION_H
#define ACTIVATIONFUNCTION_H

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "AFLibrary.h"

namespace s21 {
class ActivationFunction {
public:
    enum Flags {
        Sigmoid = 1,
        BipolarSigmoid = 2,
        ReLU = 4,
        BoundedLinear = 8,
        Softmax = 16,
        Linear = 0
    };

private:
    std::function<float(float)> f;
    std::function<float(float)> df;
    void SetValues(std::function<float(float)> func = sigmoid,
                   std::function<float(float)> derivative = d_sigmoid,
                   Flags flag = Sigmoid);

public:
    ActivationFunction(Flags flag);
    ActivationFunction(std::string name = "");
    bool operator==(const ActivationFunction &rhs) const;
    bool operator!=(const ActivationFunction &rhs) const;
    std::function<float(float)> GetFunction();
    std::function<float(float)> GetDerivative();
    float ApplyFunction(float);
    float ApplyDerivative(float);
    int type;

    explicit operator std::string() const;
};

std::istream &operator>>(std::istream &is, ActivationFunction &af);
std::ostream &operator<<(std::ostream &os, const ActivationFunction &af);
}  // namespace s21

#endif
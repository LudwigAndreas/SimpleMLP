#include "ActivationFunction.h"

#include <utility>

#include "libs21/include/libs21.h"

namespace s21 {

void ActivationFunction::SetValues(std::function<float(float)> func,
                                   std::function<float(float)> derivative,
                                   Flags flag) {
    f = std::move(func);
    df = std::move(derivative);
    type = flag;
}

ActivationFunction::ActivationFunction(Flags flag) {
    if (flag == Sigmoid)
        SetValues(sigmoid, d_sigmoid, flag);
    else if (flag == BipolarSigmoid)
        SetValues(bsigmoid, d_bsigmoid, flag);
    else if (flag == ReLU)
        SetValues(relu, d_relu, flag);
    else if (flag == BoundedLinear)
        SetValues(bounded_linear, d_bounded_linear, flag);
    else if (flag == Linear)
        SetValues(linear, d_linear, flag);
    else
        SetValues();
}

ActivationFunction::ActivationFunction(std::string name) {
    name = s21::to_lower(name);
    if (name == "sigmoid")
        SetValues(sigmoid, d_sigmoid, Flags::Sigmoid);
    else if (name == "bipolar sigmoid")
        SetValues(bsigmoid, d_bsigmoid, Flags::BipolarSigmoid);
    else if (name == "relu")
        SetValues(relu, d_relu, Flags::ReLU);
    else if (name == "bounded linear")
        SetValues(bounded_linear, d_bounded_linear, Flags::BoundedLinear);
    else if (name == "linear")
        SetValues(linear, d_linear, Flags::Linear);
    else
        SetValues();
}

bool ActivationFunction::operator==(const ActivationFunction &rhs) const {
    return std::string(*this) == std::string(rhs);
}

bool ActivationFunction::operator!=(const ActivationFunction &rhs) const {
    return !(*this == rhs);
}

std::function<float(float)> ActivationFunction::GetFunction() {
    return f;
}
std::function<float(float)> ActivationFunction::GetDerivative() {
    return df;
}
float ActivationFunction::ApplyFunction(float input) {
    return f(input);
}
float ActivationFunction::ApplyDerivative(float input) {
    return df(input);
}

ActivationFunction::operator std::string() const {
    if (type == Sigmoid) return "Sigmoid";
    if (type == BipolarSigmoid) return "Bipolar Sigmoid";
    if (type == ReLU) return "ReLU";
    if (type == BoundedLinear) return "Bounded Linear";
    return "";
}

std::istream &operator>>(std::istream &is, ActivationFunction &af) {
    std::string type;

    is >> type;
    af = ActivationFunction(type);
    return is;
}

std::ostream &operator<<(std::ostream &os, const ActivationFunction &af) {
    os << std::string(af);
    return os;
}

}  // namespace s21
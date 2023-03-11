#include "ActivationFunction.hpp"

#include <utility>

namespace s21 {

	inline float sigmoid(float x) {
		return 1.0f / (1 + std::exp(-x));
	}

	inline float d_sigmoid(float x){
		return std::exp(x) / std::pow(std::exp(x) + 1, 2);
	}

	inline float bsigmoid(float x) {
		return 2.0f / (1 + std::exp(-x)) - 1;
	}

	inline float d_bsigmoid(float x){
		return (2 * x * (1 - x));
	}

	inline float relu(float x) {
		return (x >= 0) ? x : x / 100;
	}

	inline float d_relu(float x) {
		return (x >= 0) ? 1 : 1. / 100;
	}

	inline float bounded_linear(float x) {
		if (x < -1)
			return -1;
		if (x > 1)
			return 1;
		return x;
	}

	inline float d_bounded_linear(float x) {
		if (x < -1 || x > 1)
			return 0;
		return 1;
	}

	ActivationFunction::ActivationFunction(
		std::function<float (float)> func, std::function<float (float)> derivative)
		: f(std::move(func)), df(std::move(derivative)) {}

	std::function<float (float)> ActivationFunction::getFunction()		{ return f; }
	std::function<float (float)> ActivationFunction::getDerivative()	{ return df; }
	float ActivationFunction::applyFunction(float input)				{ return f(input); }
	float ActivationFunction::applyDerivative(float input)				{ return df(input); }

	ActivationFunction *
	ActivationFunction::getFunctionByName(const std::string& name) {
		if (name == "sigmoid")
			return new ActivationFunction(sigmoid, d_sigmoid);
		else if (name == "bipolar sigmoid")
			return new ActivationFunction(bsigmoid, d_bsigmoid);
		else if (name == "ReLU")
			return new ActivationFunction(relu, d_relu);
		else if (name == "bounded linear")
			return new ActivationFunction(bounded_linear, d_bounded_linear);
		return (nullptr);
	}

	ActivationFunction *ActivationFunction::getFunctionByFlag(
			ActivationFunction::ActivationFunctionFlags flag) {
		if (flag == Sigmoid)
			return new ActivationFunction(sigmoid, d_sigmoid);
		else if (flag == BipolarSigmoid)
			return new ActivationFunction(bsigmoid, d_bsigmoid);
		else if (flag == ReLU)
			return new ActivationFunction(relu, d_relu);
		else if (flag == BoundedLinear)
			return new ActivationFunction(bounded_linear, d_bounded_linear);
		return (nullptr);
	}

	std::istream &operator>>(std::istream &is, ActivationFunction *af) {
		int type;
		
		is >> type;
		af = ActivationFunction::getFunctionByFlag(
			static_cast<ActivationFunction::ActivationFunctionFlags>(type));
		return is;
	}

	std::ostream &operator<<(std::ostream &os, const ActivationFunction &af) {
		os << af.type;
		return os;
	}
}
#include "ActivationFunction.hpp"

#include <utility>

namespace s21 {

	std::vector<float> softmax(std::vector<float> matrix) {
		std::vector<float>	values;
		float	sum;

		for (auto val : matrix)
			values.push_back(std::exp(val));
		sum = std::accumulate(values.begin(), values.end(), 0.);
		std::transform(values.begin(), values.end(),
						values.begin(), [sum](float x){ return x / sum; });
		return {values};
	}

	inline float sigmoid(float x) {
		return 1.0f / (1 + std::exp(-x));
	}

	inline float d_sigmoid(float x){
		return std::exp(x) / ((std::exp(x) + 1) * (std::exp(x) + 1));
	}

	inline float bsigmoid(float x) {
		return 2.0f / (1 + std::exp(-x)) - 1;
	}

	inline float d_bsigmoid(float x){
		return (2 * d_sigmoid(x));
	}

	inline float relu(float x) {
		if (x >= 0) {
			return x;
		} else {
			return x * 0.01f;
		}
	}

	inline float d_relu(float x) {
		if (x >= 0) {
			return 1;
		} else {
			return 0.01;
		}
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
		if (name == "Sigmoid")
			return new ActivationFunction(sigmoid, d_sigmoid);
		else if (name == "Bipolar Sigmoid")
			return new ActivationFunction(bsigmoid, d_bsigmoid);
		else if (name == "ReLU")
			return new ActivationFunction(relu, d_relu);
		else if (name == "Bounded Linear")
			return new ActivationFunction(bounded_linear, d_bounded_linear);
		return (nullptr);
	}

	ActivationFunction *ActivationFunction::getFunctionByFlag(
			ActivationFunction::Flags flag) {
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
			static_cast<ActivationFunction::Flags>(type));
		return is;
	}

	std::ostream &operator<<(std::ostream &os, const ActivationFunction &af) {
		os << af.type;
		return os;
	}
}
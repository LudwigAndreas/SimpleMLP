#pragma once

#include <functional>
#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

namespace s21 {
	
	std::vector<float> softmax(std::vector<float> matrix) {
		std::vector<float>	values;
		float				sum;

		for (auto val : matrix)
			values.push_back(std::exp(val));
		sum = std::accumulate(values.begin(), values.end(), 0);
		std::transform(values.begin(), values.end(),
						values.begin(), [sum](float x){ return x / sum; });
		return values;
	}
	
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
	

	class ActivationFunction {
	private:
		std::function<float (float)> f;
		std::function<float (float)> df;
	public:
		ActivationFunction(std::function<float (float)> func, std::function<float (float)> derivative);
		std::function<float (float)> getFunction();
		std::function<float (float)> getDerivative();
		float applyFunction(float);
		float applyDerivative(float);
		// static int Sigmoid = 1;
		enum Flags {
			Sigmoid = 1,
			BipolarSigmoid = 2,
			ReLU = 4,
			BoundedLinear = 8,
			Softmax = 16
		};
		int	type;

		static ActivationFunction* getFunctionByName(std::string name)
		{
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

		static ActivationFunction* getFunctionByFlag(Flags flag)
		{
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
	};

	std::istream &operator>>(std::istream &is, ActivationFunction *af);
	std::ostream &operator<<(std::ostream &os, const ActivationFunction &af); 
}
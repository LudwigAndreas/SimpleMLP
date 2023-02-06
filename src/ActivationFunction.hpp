#pragma once

#include <functional>
#include <string>
#include <cmath>

namespace s21 {
	
	inline float sigmoid(float x) {
		return 1.0f / (1 + std::exp(-x));
	}

	inline float d_sigmoid(float x){
		return (x * (1 - x));
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
	

	class ActivationFunction {
	private:
		// using Signature = float (float);
		// using FunctionType = std::function<Signature>;
		std::function<float (float)> f;
		std::function<float (float)> df;
	public:
		ActivationFunction(std::function<float (float)> func, std::function<float (float)> derivative);
		std::function<float (float)> getFunction();
		std::function<float (float)> getDerivative();
		float applyFunction(float);
		float applyDerivative(float);
		static ActivationFunction* getFunctionByName(std::string name)
		{
			if (name == "sigmoid")
				return new ActivationFunction(sigmoid, d_sigmoid);
			if (name == "bipolar sigmoid")
				return new ActivationFunction(bsigmoid, d_bsigmoid);
			else if (name == "ReLU")
				return new ActivationFunction(relu, d_relu);
			return (nullptr);
		}
	};
}
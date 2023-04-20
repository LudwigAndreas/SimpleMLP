#pragma once

#include <functional>
#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

namespace s21 {
	inline float linear(float x) {
		return x;
	}

	inline float d_linear(float x) {
		return 1;
	}

	std::vector<float> softmax(std::vector<float> matrix);
	
	class ActivationFunction {
	private:
		std::function<float (float)> f;
		std::function<float (float)> df;
	public:
		enum Flags {
			Sigmoid = 1,
			BipolarSigmoid = 2,
			ReLU = 4,
			BoundedLinear = 8,
			Softmax = 16,
			Linear = 0
		};

		void SetValues(std::function<float (float)> func = linear, std::function<float (float)> derivative = d_linear, Flags flag = Linear);
		ActivationFunction(Flags flag);
		ActivationFunction(std::string name);
		std::function<float (float)> getFunction();
		std::function<float (float)> getDerivative();
		float applyFunction(float);
		float applyDerivative(float);
		// static int Sigmoid = 1;
		int	type;

		// static ActivationFunction* getFunctionByName(const std::string& name);

		// static ActivationFunction* getFunctionByFlag(Flags flag);

		explicit operator std::string() const;
	};

	std::istream &operator>>(std::istream &is, ActivationFunction &af);
	std::ostream &operator<<(std::ostream &os, const ActivationFunction &af); 
}
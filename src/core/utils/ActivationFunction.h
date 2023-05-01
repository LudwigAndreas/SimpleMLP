#pragma once

#include <functional>
#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#include "AFLibrary.h"

namespace s21 {
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

		void SetValues(std::function<float (float)> func = sigmoid, std::function<float (float)> derivative = d_sigmoid, Flags flag = Sigmoid);
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
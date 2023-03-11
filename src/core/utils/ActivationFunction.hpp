#pragma once

#include <functional>
#include <string>
#include <cmath>
#include <iostream>

namespace s21 {
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
		enum ActivationFunctionFlags {
			Sigmoid = 1,
			BipolarSigmoid = 2,
			ReLU = 4,
			BoundedLinear = 8
		};
		int	type{};

		static ActivationFunction* getFunctionByName(const std::string& name);

		static ActivationFunction* getFunctionByFlag(ActivationFunctionFlags flag);
	};

	std::istream &operator>>(std::istream &is, ActivationFunction *af);
	std::ostream &operator<<(std::ostream &os, const ActivationFunction &af); 
}
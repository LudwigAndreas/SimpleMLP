#include "ActivationFunction.hpp"

#include <utility>

namespace s21 {
	ActivationFunction::ActivationFunction(
		std::function<float (float)> func, std::function<float (float)> derivative)
		: f(std::move(func)), df(std::move(derivative)) {}

	std::function<float (float)> ActivationFunction::getFunction()		{ return f; }
	std::function<float (float)> ActivationFunction::getDerivative()	{ return df; }
	float ActivationFunction::applyFunction(float input)				{ return f(input); }
	float ActivationFunction::applyDerivative(float input)				{ return df(input); }
}
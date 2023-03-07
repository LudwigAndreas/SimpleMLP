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
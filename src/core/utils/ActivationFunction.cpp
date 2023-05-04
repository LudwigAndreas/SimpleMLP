#include "ActivationFunction.hpp"

#include <libs21/include/libs21.h>
#include <utility>

namespace s21 {

	void ActivationFunction::SetValues(std::function<float (float)> func,
									   std::function<float (float)> derivative,
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

	std::function<float (float)> ActivationFunction::getFunction()		{ return f; }
	std::function<float (float)> ActivationFunction::getDerivative()	{ return df; }
	float ActivationFunction::applyFunction(float input)				{ return f(input); }
	float ActivationFunction::applyDerivative(float input)				{ return df(input); }

	// ActivationFunction 
	// ActivationFunction::getFunctionByName(const std::string& name) {
	// 	if (name == "Sigmoid")
	// 		return new ActivationFunction(sigmoid, d_sigmoid, Flags::Sigmoid);
	// 	else if (name == "Bipolar Sigmoid")
	// 		return new ActivationFunction(bsigmoid, d_bsigmoid, Flags::BipolarSigmoid);
	// 	else if (name == "ReLU")
	// 		return new ActivationFunction(relu, d_relu, Flags::ReLU);
	// 	else if (name == "Bounded Linear")
	// 		return new ActivationFunction(bounded_linear, d_bounded_linear, Flags::BoundedLinear);
	// 	return (nullptr);
	// }

	// ActivationFunction *ActivationFunction::getFunctionByFlag(
	// 		ActivationFunction::Flags flag);

	ActivationFunction::operator std::string() const {
		if (type == Sigmoid)
			return "Sigmoid";
		if (type == BipolarSigmoid)
			return "Bipolar Sigmoid";
		if (type == ReLU)
			return "ReLU";
		if (type == BoundedLinear)
			return "Bounded Linear";
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

}
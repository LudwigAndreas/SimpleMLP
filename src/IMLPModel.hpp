#ifndef IMLPMODEL_HPP
#define IMLPMODEL_HPP



#include <vector>
#include "Matrix.hpp"

namespace s21 {
	template <typename T>
	class IMLPModel {
	public:
		virtual std::vector<T> Forward(Matrix<T>) = 0;
		virtual void Backward(Matrix<T>) = 0;
		virtual int Train() = 0;
		virtual int Test() = 0;
		virtual int Predict() = 0;
//		virtual IMLPModel *Instance(size_t in_channels, size_t out_channels, size_t hidden_units_per_layer, int hidden_layers, float lr);
	};
}

#endif
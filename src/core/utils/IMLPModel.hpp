#ifndef IMLPMODEL_HPP
#define IMLPMODEL_HPP

#include <vector>
#include "Sample.hpp"

namespace s21 {
	template <typename T>
	class IMLPModel {
	public:
		virtual std::vector<T> Forward(Matrix<T>) = 0;
		virtual void Backward(Matrix<T>) = 0;
		virtual void Backward(Matrix<T>, Matrix<T>) = 0;
		virtual float Train(DatasetGroup samples, bool b = false) = 0;
		virtual float CrossValidation(Dataset samples, bool b = false) = 0;
		virtual float Test(DatasetGroup samples, bool b = false) = 0;
		virtual int Predict(Matrix<float>) = 0;
		virtual float TestOutput(std::vector<Sample> samples, bool silent_mode = false, std::string filename = "") = 0;

//		virtual IMLPModel *Instance(size_t in_channels, size_t out_channels, size_t hidden_units_per_layer, int hidden_layers, float lr);
	};
}

#endif
#pragma once

#include "MLPGraphNode.hpp"
#include "../matrix/Matrix.hpp"
#include "../utils/ActivationFunction.hpp"

#include <vector>
#include <algorithm>

namespace s21 {
	class MLPGraphLayer {
	private:
		MLPGraphLayer		*input;
		MLPGraphLayer		*output;
		size_t				size;
		ActivationFunction	*af;
		
		std::vector<MLPGraphNode>		neurons;
		// std::vector<float>				raw_value;
		// std::vector<float>				value;
		// std::vector<float>				error;
		// std::vector<std::vector<float>>	weight;
		// std::vector<float>				bias;
		// std::vector<s21::MLPGraphNode>	nodes;
	
	public:
		MLPGraphLayer(size_t size, ActivationFunction *af,
						MLPGraphLayer *input = nullptr,
						MLPGraphLayer *output = nullptr);
		
		void	GenerateLayer();

		const MLPGraphNode	&operator[](int index) const;

		void	SetLayerValues(Matrix<float> &values);
		void	SetError	  (Matrix<float> &target);

		void	SetInputLayer (MLPGraphLayer *input);
		void	SetOutputLayer(MLPGraphLayer *output);

		std::vector<float> GetResultingVector();

		void	CalculateLayer(ActivationFunction *af);
		void	CalculateError(std::vector<float> *target = nullptr);
		void	UpdateWeights(float lr);

		size_t Size();
	};
}

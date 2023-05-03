#pragma once

#include "MLPGraphNode.h"
#include "../matrix/Matrix.h"
#include "../utils/ActivationFunction.h"

#include <vector>
#include <algorithm>

namespace s21 {
	class MLPGraphLayer {
	private:
		MLPGraphLayer		*input;
		MLPGraphLayer		*output;
		size_t				size;
		ActivationFunction	*af;
		
		std::vector<MLPGraphNode>	neurons;
	
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

	std::istream &operator>>(std::istream &is, MLPGraphLayer &layer);

	std::ostream &operator<<(std::ostream &os, const MLPGraphLayer &layer);
}

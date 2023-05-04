#pragma once

#include "MLPGraphNode.h"
#include "../matrix/Matrix.h"
#include "../utils/ActivationFunction.h"
#include "core/exceptions/UploadFileException.h"

#include <vector>
#include <algorithm>
#include <sstream>

namespace s21 {
	class MLPGraphLayer {
	private:
		MLPGraphLayer		*input;
		MLPGraphLayer		*output;
		size_t				size;
		ActivationFunction	af;
		
		std::vector<MLPGraphNode>	neurons;
	
	public:
		MLPGraphLayer(size_t size, const ActivationFunction &af,
						MLPGraphLayer *input = nullptr,
						MLPGraphLayer *output = nullptr);

		MLPGraphLayer(std::vector<MLPGraphNode> &&neurons,
						const ActivationFunction &af,
						MLPGraphLayer *input = nullptr,
						MLPGraphLayer *output = nullptr);
		
		MLPGraphLayer(MLPGraphLayer &) = default;
		MLPGraphLayer(MLPGraphLayer &&) = default;
		MLPGraphLayer& operator=(MLPGraphLayer &) = default;
		
		void	GenerateLayer();

		const MLPGraphNode	&operator[](int index) const;
		MLPGraphNode		&operator[](int index);

		void	SetLayerValues(Matrix<float> &values);
		void	SetError	  (Matrix<float> &target);

		void	SetInputLayer (MLPGraphLayer *input);
		void	SetOutputLayer(MLPGraphLayer *output);

		std::vector<float> GetResultingVector();

		void	CalculateLayer(ActivationFunction &af);
		void	CalculateError(std::vector<float> *target = nullptr);
		void	UpdateWeights(float lr);

		size_t InputSize() const;
		size_t Size() const;
	};

	std::istream &operator>>(std::istream &is, MLPGraphLayer &layer);

	std::ostream &operator<<(std::ostream &os, const MLPGraphLayer &layer);
}

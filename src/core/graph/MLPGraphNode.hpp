#pragma once

#include <vector>
#include <algorithm>
#include "../utils/ActivationFunction.hpp"

namespace s21 {
	class MLPGraphNode {
	private:
		// MLPGraphLayer 		*input_layer;
		// MLPGraphLayer		*output_layer;
		float				raw_value;
		float				value;
		float				error;
		float				bias;
		std::vector<float>	weight;

		// std::vector<float>	error;
	public:
		MLPGraphNode(int input_size);
		MLPGraphNode(float value);

		void	CalculateValue(std::vector<float> input, ActivationFunction *af);
		float	CalculateError(std::vector<float> error, ActivationFunction *af, float lr);
		void	ChangeWeights(std::vector<float> error, float lr);

		operator float() const;
	};
}



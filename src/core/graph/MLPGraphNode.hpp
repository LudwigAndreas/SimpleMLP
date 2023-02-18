#pragma once

#include <vector>

namespace s21 {
	class MLPGraphLayer;
	
	class MLPGraphNode {
	private:
		MLPGraphLayer 		*input_layer;
		MLPGraphLayer		*output_layer;
		float				value;
		std::vector<float>	weight;
		std::vector<float>	neuron_values;
		std::vector<float>	neuron_error;
		float				bias;
	public:
		void CalculateValue();
		operator int() const;
	};
}



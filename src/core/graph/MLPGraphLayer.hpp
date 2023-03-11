#pragma once

#include "MLPGraphNode.hpp"

#include <vector>

namespace s21 {
	class MLPGraphLayer {
	private:
		std::vector<s21::MLPGraphNode> nodes;
	public:
		s21::MLPGraphNode		&operator[](int index);
		const s21::MLPGraphNode &operator[](int index) const;

		void	SetInputLayer (MLPGraphLayer *input);
		void	SetOutputLayer(MLPGraphLayer *output);

		void	CalculateLayer();
	};
}

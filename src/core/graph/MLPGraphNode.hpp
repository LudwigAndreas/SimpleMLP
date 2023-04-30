#pragma once

#include <vector>
#include <algorithm>
#include "../utils/ActivationFunction.hpp"

namespace s21 {
	struct MLPGraphNode {
		float				raw_value;
		float				value;
		float				error;
		float				bias;
		std::vector<float>	weight;
	};
}


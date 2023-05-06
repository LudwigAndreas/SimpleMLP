#ifndef MLPGRAPHNODE_H
#define MLPGRAPHNODE_H

#include <vector>
#include <algorithm>
#include "../utils/ActivationFunction.h"

namespace s21 {
	struct MLPGraphNode {
		float				raw_value;
		float				value;
		float				error;
		float				bias;
		std::vector<float>	weight;
	};
}

#endif
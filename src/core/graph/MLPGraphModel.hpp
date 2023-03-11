#pragma once

#include "../utils/IMLPModel.hpp"
#include "../graph/MLPGraphLayer.hpp"

namespace s21 {
	class MLPGraphModel : public IMLPModel<float> {
	private:
		std::vector<MLPGraphLayer *> layers;
	
	public:
		MLPGraphModel *AddLayer(MLPGraphLayer *layer);
	};

}
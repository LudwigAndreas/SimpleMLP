// #include "MLPGraphNode.hpp"

// namespace s21 {
// 	MLPGraphNode::MLPGraphNode(int input_size) {
// 		weight.resize(input_size);
// 		// error.resize(input_size);
// 		bias = 0;

// 	}

// 	MLPGraphNode::MLPGraphNode(float value) {
// 		this->value = value;
// 	}

// 	void MLPGraphNode::CalculateValue(std::vector<float> input, ActivationFunction *af) {
// 		raw_value = 0;
// 		for (int i = 0; i < weight.size(); ++i)
// 			raw_value += weight[i] * (input)[i];
// 		value = af->applyFunction(raw_value);
// 	}

// 	float MLPGraphNode::CalculateError(std::vector<float> error, ActivationFunction *af, float lr) {
// 		this->error = 0;
// 		for (int i = 0; i < error.size(); ++i)
// 			this->error = error[i] * weight[i];
// 		this->error *= af->getDerivative()(raw_value);
// 		ChangeWeights(error, lr);
// 		return this->error;
// 	}

// 	void MLPGraphNode::ChangeWeights(std::vector<float> error, float lr) {
// 		std::transform(weight.begin(), weight.end(), error.begin(), weight.begin(),
// 			[lr](float lhs, float rhs) { return lhs - lr * rhs; });
// 		bias -= lr * error[0];
// 	}
	
// 	MLPGraphNode::operator float() const {
// 		return value;
// 	}

// }

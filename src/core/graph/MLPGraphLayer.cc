#include "MLPGraphLayer.h"

namespace s21 {
	MLPGraphLayer::MLPGraphLayer(size_t size,
								 ActivationFunction *af,
								 MLPGraphLayer *input,
								 MLPGraphLayer *output) {
		this->size = size;
		this->af = af;
		this->SetInputLayer(input);
		this->SetOutputLayer(output);
	}

	void	MLPGraphLayer::GenerateLayer() {
		neurons = std::vector<MLPGraphNode>(size);
		if (input) {
			std::vector<float>  ndvector = GenerateNDMatrix<float>(size, input->Size()).ToVector();

			for (int i = 0; i < size; ++i) {
				neurons[i].bias = ndvector[i];
				neurons[i].weight = std::vector<float>(ndvector.begin() + input->Size() * i,
													   ndvector.begin() + input->Size() * (i + 1));
			}
		}
	}

	const MLPGraphNode	&MLPGraphLayer::operator[](int index) const {
		return (neurons[index]);
	}

	void	MLPGraphLayer::SetLayerValues(Matrix<float> &values) {
		if (values.size() != size)
			throw std::exception();
		for (int i = 0; i < size; ++i) {
			neurons[i].value = values[i];
		}
	}

	void	MLPGraphLayer::SetInputLayer(MLPGraphLayer *input) {
		this->input = input;
	}

	void	MLPGraphLayer::SetOutputLayer(MLPGraphLayer *output) {
		this->output = output;
	}

	std::vector<float>	MLPGraphLayer::GetResultingVector() {
		std::vector<float> value;
		for (auto &neuron : neurons)
			value.push_back(neuron.value);
		return value;
	}

	void	MLPGraphLayer::CalculateLayer(ActivationFunction *af) {
		for (int i = 0; i < neurons.size(); ++i)
		{
			neurons[i].raw_value = 0;
			for (int j = 0; j < neurons[i].weight.size(); ++j)
				neurons[i].raw_value += neurons[i].weight[j] * (*input)[j].value;

			if (output) {
				if (af)
					neurons[i].value = af->applyFunction(neurons[i].raw_value);
				else
				 	neurons[i].value = neurons[i].raw_value;
			}
		}
		if (!output) {
			std::vector<float> temp;
			for (auto neuron : neurons) 
				temp.push_back(neuron.raw_value);
			temp = softmax(temp);
			for (int i = 0; i < temp.size(); ++i) 
				neurons[i].value = temp[i];
		}
	}

	void	MLPGraphLayer::CalculateError(std::vector<float> *target) {
		if (target) {
			for (int i = 0; i < neurons.size(); ++i) {
				neurons[i].error = neurons[i].value - (*target)[i];
			}
		}
		else if (output) {
			for (int i = 0; i < neurons.size(); ++i) {
				neurons[i].error = 0;
				for (int j = 0; j < output->Size(); ++j) {
					neurons[i].error += (*output)[j].error * (*output)[j].weight[i];
				}
				neurons[i].error *= af->applyDerivative(neurons[i].raw_value);
			}
		}
	}

	void	MLPGraphLayer::UpdateWeights(float lr) {
		for (int i = 0; i < neurons.size(); ++i) {
			for (int j = 0; j < neurons[i].weight.size(); ++j) {
				neurons[i].weight[j] -= (*input)[j].value * neurons[i].error * lr;
			}
		}
		for (auto &neuron : neurons)
			neuron.bias -= lr * neuron.error;
	}

	size_t MLPGraphLayer::Size() {
		return size;
	}

    std::istream &operator>>(std::istream &is, MLPGraphLayer &layer) {return is;}

	std::ostream &operator<<(std::ostream &os, const MLPGraphLayer &layer) {
//		for (auto & node : layer.GetNodes()) {
//			os << node;
//		}
        return os;
	}
}

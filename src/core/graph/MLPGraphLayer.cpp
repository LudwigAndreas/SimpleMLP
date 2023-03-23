#include "MLPGraphLayer.hpp"

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
			// for (auto it = ndvector.begin(); it < ndvector.end(); it += input->Size())
				// weight.push_back(std::vector<float>(it, it + input->Size()));
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
		// value = values.ToVector();
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
			// const std::vector<float>& output_error = output->get_error();
			// const std::vector<std::vector<float>>& 
			// 						  output_weight = output->get_weight_matrices();
			for (int i = 0; i < neurons.size(); ++i) {
				neurons[i].error = 0;
				for (int j = 0; j < output->Size(); ++j) {
					neurons[i].error += (*output)[j].error * (*output)[j].weight[i];
				}
				neurons[i].error *= af->applyDerivative(neurons[i].raw_value);
			}
			// Matrix<float> weight_matrix = Matrix<float>(weight, value.size(), weight.size() / value.size());
			// Matrix<float> temp = Matrix<float>(output_error, output_error.size(), 1);
			// temp = temp.matmulTransposed(weight_matrix);
			// temp = temp & Matrix<float>(raw_value, value.size(), 1);
			// error = temp.ToVector();
			// for (int i = 0; i < error.size(); ++i) {
			// 	error[i] = 0;
			// 	for (int j = 0; j < weight.size(); ++j) {
			// 		error[i] += output_error[j] * weight[j][i];
			// 	}
			// 	error[i] *= af->applyDerivative(raw_value[i]);
			// }

		}
	}

	void	MLPGraphLayer::UpdateWeights(float lr) {
		// const std::vector<float>& output_error = output->get_error();
		// const std::vector<float>& input_values = input->get_neuron_values();
		
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
}

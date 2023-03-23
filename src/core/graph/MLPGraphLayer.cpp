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
		if (input) {
			neurons   = std::vector<MLPGraphNode>(size);
			raw_value = std::vector<float>(size);
			value	  = std::vector<float>(size);
			error	  = std::vector<float>(size);
			bias	  = GenerateNDMatrix<float>(size, 1).ToVector();

			std::vector<float>  ndvector = GenerateNDMatrix<float>(size, input->Size()).ToVector();
			for (auto it = ndvector.begin(); it < ndvector.end(); it += input->Size())
				weight.push_back(std::vector<float>(it, it + input->Size()));
		}
	}

	float	MLPGraphLayer::operator[](int index) const {
		return (value[index]);
	}

	void	MLPGraphLayer::SetLayerValues(Matrix<float> &values) {
		if (values.size() != size)
			throw std::exception();
		value = values.ToVector();
	}

	void	MLPGraphLayer::SetInputLayer(MLPGraphLayer *input) {
		this->input = input;
	}

	void	MLPGraphLayer::SetOutputLayer(MLPGraphLayer *output) {
		this->output = output;
	}

	std::vector<float>	MLPGraphLayer::GetResultingVector() {
		return value;
	}

	void	MLPGraphLayer::CalculateLayer(ActivationFunction *af) {
		for (int i = 0; i < raw_value.size(); ++i)
		{
			raw_value[i] = 0;
			for (int j = 0; j < weight[i].size(); ++j)
				raw_value[i] += weight[i][j] * (*input)[j];

			if (output) {
				if (af)
					value[i] = af->applyFunction(raw_value[i]);
				else
				 	value[i] = raw_value[i];
			}
		}
		if (!output)
			value = softmax(raw_value);
	}

	void	MLPGraphLayer::CalculateError(std::vector<float> *target) {
		if (target)
			std::transform(value.begin(), value.end(),
						   target->begin(), error.begin(),
						   std::minus<float>());
		else if (output) {
			const std::vector<float>& output_error = output->get_error();
			const std::vector<std::vector<float>>& 
									  output_weight = output->get_weight_matrices();
			for (int i = 0; i < error.size(); ++i) {
				error[i] = 0;
				for (int j = 0; j < output_weight.size(); ++j) {
					error[i] += output_error[j] * output_weight[j][i];
				}
				error[i] *= af->applyDerivative(raw_value[i]);
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
		const std::vector<float>& input_values = input->get_neuron_values();
		
		for (int i = 0; i < weight.size(); ++i) {
			for (int j = 0; j < weight[i].size(); ++j) {
				weight[i][j] -= input_values[j] * error[i] * lr;
			}
		}
		std::transform(bias.begin(), bias.end(),
					   error.begin(), bias.begin(),
					   [lr](float lhs, float rhs) { return lhs - lr * rhs; }
		);
	}

	size_t MLPGraphLayer::Size() {
		return size;
	}
}

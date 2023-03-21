#include "MLPGraphLayer.hpp"

namespace s21 {
	MLPGraphLayer::MLPGraphLayer(size_t size,
								 ActivationFunction::Flags flag,
								 MLPGraphLayer *input) {
		this->size = size;
		this->af = ActivationFunction::getFunctionByFlag(flag);
		this->SetInputLayer(input);
	}

	void	MLPGraphLayer::GenerateLayer() {
		if (input) {
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
		GenerateLayer();
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
			
			if (!output) {
				if (af)
					value[i] = af->applyFunction(raw_value[i]);
				else
				 	value[i] = raw_value[i];
			}
		}
		if (!output)
			value = softmax(raw_value);
	}

	void	MLPGraphLayer::CalculateError(std::vector<float> *target = nullptr) {
		if (target)
			std::transform(value.begin(), value.end(),
						   target->begin(), error.begin(),
						   std::minus<float>());
		else if (output) {
			const std::vector<float>& output_error = output->get_error();
			for (int i = 0; i < value.size(); ++i) {
				error[i] = 0;
				for (int j = 0; j < weight.size(); ++j) {
					error[i] += output_error[j] * weight[j][i];
				}
				error[i] *= af->applyDerivative(raw_value[i]);
			}
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
}

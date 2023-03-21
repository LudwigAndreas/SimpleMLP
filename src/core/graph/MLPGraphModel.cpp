#include "MLPGraphModel.hpp"

namespace s21 {
		MLPGraphModel	*MLPGraphModel::AddLayer(MLPGraphLayer *layer) {
			layer->SetInputLayer(layers.back());
			layers.back()->SetOutputLayer(layer);
			layers.push_back(layer);
			return this;
		}

		std::vector<T>	MLPGraphModel::Forward(Matrix<T> input) {
			layers.front()->SetLayerValues(input);
			for (auto it = layers.begin() + 1; it < layers.end(); ++it) {
				(*it)->CalculateLayer(af);
			}
			return layers.back()->GetResultingVector();
		}

		void			MLPGraphModel::Backward(Matrix<T> target) {
			assert(std::get<1>(target.get_shape()) == upl.back());

			layers.back()->CalculateError(&(target.ToVector()));
			for (int i = (int) layers.size() - 2; i > 0; --i) {
				layers[i]->CalculateError(nullptr);
			}
			for (size_t i = 0; i < units_per_layer.size() - 1; ++i) {
				weight_matrices[i] = weight_matrices[i] - (neuron_values[i].T() * error[i + 1] * lr);
				bias[i] = bias[i] - error[i + 1] * lr;
			}
			
		}

		float			MLPGraphModel::Train(DatasetGroup samples, bool b = false);
		float			MLPGraphModel::Test(DatasetGroup samples, bool b = false);
		int				MLPGraphModel::Predict(Matrix<float>);
		float			MLPGraphModel::TestOutput(std::vector<Sample> samples, bool silent_mode = false, std::string filename = "");
}

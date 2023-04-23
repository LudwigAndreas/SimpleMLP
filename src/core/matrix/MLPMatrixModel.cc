#include "MLPMatrixModel.hpp"

namespace s21 {

	std::ostream &operator<<(std::ostream &os, const MLPMatrixModel &model) {
		for (auto unit: model.get_units_per_layer()) {
			os << unit << " ";
		}
		os << model.get_lr() << '\n';
		for (const auto &layer : model.GetLayers())
			os << *layer;
		return os;
	}

	std::istream &operator>>(std::istream &is, MLPMatrixModel &model) {
		// std::vector<float> matrix_values;
		// std::vector<std::string> row_values;
		// std::vector<s21::Matrix<float>> weights_matrices;
		// s21::Matrix<float> matrix;


		std::vector<MLPMatrixLayer *> layers;
		std::string units_per_layer_str;
		
		// std::string line;
		std::getline(is, units_per_layer_str);

		auto upls = split(units_per_layer_str, " ");
		std::vector<size_t> units_per_layer;
		for (auto i = upls.begin(); i < upls.end() - 1; ++i)
			units_per_layer.push_back(std::atoi(i->data()));
		model.set_units_per_layer(units_per_layer);
		model.set_lr(std::atof(upls.rbegin()->data()));

		for (int i = 0; i < units_per_layer.size() - 1; ++i) {
			Matrix<float> w, b;
			is >> w >> b;
			layers.push_back(new MLPMatrixLayer(w, b));
		}
		layers.push_back(new MLPMatrixLayer(units_per_layer.back()));
		model.SetLayers(std::move(layers));
		

		// model.set_weight_martices	(readVectorMatrix<float>(is, units_per_layer.size() - 1));
		// model.set_bias				(readVectorMatrix<float>(is, units_per_layer.size() - 1));
		// model.set_neuron_values		(readVectorMatrix<float>(is, units_per_layer.size()	   ));
		// model.set_error				(readVectorMatrix<float>(is, units_per_layer.size()	   ));
		// model.set_incorrect_values	(readVectorMatrix<float>(is, units_per_layer.size()	   ));
		// model.set_raw				(readVectorMatrix<float>(is, units_per_layer.size()	   ));
		return is;
	}

}
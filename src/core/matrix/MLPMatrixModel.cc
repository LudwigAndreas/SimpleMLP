//
// Created by Ludwig Andreas on 20.04.2023.
//
#include "MLPMatrixModel.hpp"

std::ostream &operator<<(std::ostream &os, const s21::MLPMatrixModel &model) {
//		for (auto unit: model.get_units_per_layer()) {
//			os << unit << " ";
//		}
//		os << model.get_lr() << '\n';
//		for (auto layer : model.GetLayers())
//			os << *layer;
    // for (auto weights: model.get_weight_matrices())
    // 	os << weights;
    // for (auto bias: model.get_bias_vectors())
    // 	os << bias;
    // for (auto neuron_values: model.get_neuron_values())
    // 	os << neuron_values;
    // for (auto error: model.get_error())
    // 	os << error;
    // for (auto incorrect_values: model.get_incorrect_values())
    // 	os << incorrect_values;
    // for (auto raw: model.get_raw())
    // 	os << raw;
    return os;
}

std::istream &operator>>(std::istream &is, s21::MLPMatrixModel &model) {
    // std::vector<float> matrix_values;
    // std::vector<std::string> row_values;
    // std::vector<s21::Matrix<float>> weights_matrices;
    // s21::Matrix<float> matrix;

//		std::string units_per_layer_str;
//		// std::string line;
//		std::getline(is, units_per_layer_str);
//
//		auto upls = split(units_per_layer_str, " ");
//		std::vector<size_t> units_per_layer;
//		for (auto i = upls.begin(); i < upls.end() - 1; ++i)
//			units_per_layer.push_back(std::atoi(i->data()));
//		model.set_units_per_layer(units_per_layer);
//		model.set_lr(std::atof(upls.rbegin()->data()));

    // model.set_weight_martices	(readVectorMatrix<float>(is, units_per_layer.size() - 1));
    // model.set_bias				(readVectorMatrix<float>(is, units_per_layer.size() - 1));
    // model.set_neuron_values		(readVectorMatrix<float>(is, units_per_layer.size()	   ));
    // model.set_error				(readVectorMatrix<float>(is, units_per_layer.size()	   ));
    // model.set_incorrect_values	(readVectorMatrix<float>(is, units_per_layer.size()	   ));
    // model.set_raw				(readVectorMatrix<float>(is, units_per_layer.size()	   ));
    return is;
}
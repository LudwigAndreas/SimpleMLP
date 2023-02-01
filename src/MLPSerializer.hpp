
#ifndef SIMPLEMLP_MLPSERIALIZER_HPP
#define SIMPLEMLP_MLPSERIALIZER_HPP

#include <string>
#include <fstream>

#include "Matrix.hpp"
#include "MLPMatrixModel.hpp"

template <typename T>
class MLPSerializer {
private:
	static std::vector<std::string> split (const std::string& s, const std::string& delimiter) {
		size_t pos_start = 0, pos_end, delim_len = delimiter.length();
		std::string token;
		std::vector<std::string> res;

		while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
			token = s.substr (pos_start, pos_end - pos_start);
			pos_start = pos_end + delim_len;
			res.push_back (token);
		}

		res.push_back (s.substr (pos_start));
		return res;
	}

public:
	static void SerializeMLPMatrixModel(s21::MLPMatrixModel<T> *model, const std::string& filename) {
		std::fstream file;
		file.open(filename, std::ofstream::out | std::ofstream::trunc);

		for (auto unit : model->get_units_per_layer()) {
			file << unit << " ";
		}
		file << model->get_lr();
		file << '\n';
		for (auto weights : model->get_weight_matrices()) {
			file << weights;
		}
		for (auto bias : model->get_bias_vectors()) {
			file << bias;
		}
		file.close();
	}

	static void DeserializeMLPMatrixModel(s21::MLPMatrixModel<T> *model, const std::string& filename) {
		std::fstream file;
		file.open(filename, std::ofstream::in);

		std::string units_per_layer_str;
		std::string line;
		std::getline(file, units_per_layer_str);

		std::vector<float> matrix_values;
		std::vector<std::string> row_values;
		std::vector<s21::Matrix<float>> weights_matrices;
		int weights_index = 0;

		auto upls = split(units_per_layer_str, " ");
		std::vector<size_t> units_per_layer;
		for (auto i = upls.begin(); i < upls.end() - 1; ++i)
			units_per_layer.push_back(std::atoi(i->data()));
		model->set_units_per_layer(units_per_layer);
		model->set_lr(std::atof(upls.rbegin()->data()));


		while (std::getline(file, line)) {
			if (line.empty()) {
				s21::Matrix<float> weights;
				weights.set_data(matrix_values);
				weights.set_cols(units_per_layer[weights_index]);
				weights.set_rows(units_per_layer[++weights_index]);
				weights.set_shape(std::tuple<size_t, size_t> (units_per_layer[weights_index], units_per_layer[weights_index - 1]));
				weights_matrices.push_back(weights);
				matrix_values.resize(0);
				if (weights_index >= units_per_layer.size() - 1)
					break;
			} else {
				row_values = split(line, " ");
				matrix_values.reserve(matrix_values.size() + row_values.size());
				std::transform(row_values.begin(), row_values.end(),
							   std::back_inserter(matrix_values),
							   [](std::string &val) { return std::atof(val.data()); });
			}
		}
		model->set_weight_martices(weights_matrices);

		weights_matrices.resize(0);
		weights_index = 0;
		while (std::getline(file, line)) {
			if (line.empty()) {
				s21::Matrix<float> weights;
				weights.set_data(matrix_values);
				weights.set_cols(1);
				weights.set_rows(units_per_layer[++weights_index]);
				weights.set_shape(std::tuple<size_t, size_t> (units_per_layer[weights_index], 1));
				weights_matrices.push_back(weights);
				matrix_values.resize(0);
				if (weights_index >= units_per_layer.size() - 1)
					break;
			}
			else
				matrix_values.push_back(std::atof(line.data()));
		}
		model->set_bias(weights_matrices);
	}

};


#endif //SIMPLEMLP_MLPSERIALIZER_HPP

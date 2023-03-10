
#ifndef SIMPLEMLP_MLPSERIALIZER_HPP
#define SIMPLEMLP_MLPSERIALIZER_HPP

#include <string>
#include <fstream>
#include <algorithm>

#include "../matrix/Matrix.hpp"
#include "../matrix/MLPMatrixModelv2.hpp"

namespace s21 {
	template<typename T>
	class MLPSerializer {
	private:
		static std::vector<std::string>
		split(const std::string &s, const std::string &delimiter) {
			size_t pos_start = 0, pos_end, delim_len = delimiter.length();
			std::string token;
			std::vector<std::string> res;

			while ((pos_end = s.find(delimiter, pos_start)) !=
				   std::string::npos) {
				token = s.substr(pos_start, pos_end - pos_start);
				pos_start = pos_end + delim_len;
				res.push_back(token);
			}

			res.push_back(s.substr(pos_start));
			return res;
		}

	public:
		static void SerializeMLPMatrixModel(s21::MLPMatrixModelv2 *model,
											const std::string &filename) {
			std::fstream file;
			file.open(filename, std::ofstream::out | std::ofstream::trunc);

			for (auto unit: model->get_units_per_layer()) {
				file << unit << " ";
			}
			file << model->get_lr();
			file << '\n';
			for (auto weights: model->get_weight_matrices()) {
				file << weights;
			}
			for (auto bias: model->get_bias_vectors()) {
				file << bias;
			}
			for (auto neuron_values: model->get_neuron_values()) {
				file << neuron_values;
			}
			for (auto error: model->get_error()) {
				file << error;
			}
			file.close();
		}

		static s21::IMLPModel<T> *DeserializeMLPMatrixModel(const std::string &filename) {
//			int rows = 0, cols = 0;
//			bool read_shape = true;

//			TODO: rewrite model creation to import graph and matrix models and activation funcs
			// auto model = s21::MLPMatrixModelv2::MakeModel(0, 0, 0, 0, 0);

			s21::MLPMatrixModelv2 *model = (s21::MLPMatrixModelv2 *) s21::MLPMatrixModelv2::MakeModel(
					0, 0, 0, 0, 0, ActivationFunction::getFunctionByFlag(ActivationFunction::Sigmoid));
			std::vector<float> matrix_values;
			std::vector<std::string> row_values;
			std::vector<s21::Matrix<float>> weights_matrices;
			s21::Matrix<float> matrix;
//			int weights_index = 0;

			std::fstream file;
			file.open(filename, std::ofstream::in);

			std::string units_per_layer_str;
			std::string line;
			std::getline(file, units_per_layer_str);

			auto upls = split(units_per_layer_str, " ");
			std::vector<size_t> units_per_layer;
			for (auto i = upls.begin(); i < upls.end() - 1; ++i)
				units_per_layer.push_back(std::atoi(i->data()));
			model->set_units_per_layer(units_per_layer);
			model->set_lr(std::atof(upls.rbegin()->data()));

			weights_matrices.reserve(units_per_layer.size());
			for (int i = 0; i < model->get_units_per_layer().size() - 1; ++i) {
				file >> matrix;
				weights_matrices.push_back(matrix);
			}
			model->set_weight_martices(weights_matrices);

			weights_matrices.resize(0);
			weights_matrices.reserve(units_per_layer.size());
			for (int i = 0; i < model->get_units_per_layer().size() - 1; ++i) {
				file >> matrix;
				weights_matrices.push_back(matrix);
			}
			model->set_bias(weights_matrices);

			weights_matrices.resize(0);
			weights_matrices.reserve(units_per_layer.size());
			for (int i = 0; i < model->get_units_per_layer().size(); ++i) {
				file >> matrix;
				weights_matrices.push_back(matrix);
			}
			model->set_neuron_values(weights_matrices);

			weights_matrices.resize(0);
			weights_matrices.reserve(units_per_layer.size());
			for (int i = 0; i < model->get_units_per_layer().size(); ++i) {
				file >> matrix;
				weights_matrices.push_back(matrix);
			}
			model->set_error(weights_matrices);
			return (IMLPModel<float> *)model;

			// while (std::getline(file, line)) {
			// 	if (line.empty()) {
			// 		s21::Matrix<float> weights;
			// 		weights.set_data(matrix_values);

			// 		weights.set_cols(cols);
			// 		weights.set_rows(rows);
			// 		weights.set_shape(std::tuple<size_t, size_t> (rows, cols));
			// 		// weights.set_cols(units_per_layer[weights_index]);
			// 		// weights.set_rows(units_per_layer[++weights_index]);
			// 		// weights.set_shape(std::tuple<size_t, size_t> (units_per_layer[weights_index], units_per_layer[weights_index - 1]));
			// 		weights_matrices.push_back(weights);
			// 		matrix_values.resize(0);
			// 		read_shape = true;
			// 		if (++weights_index >= units_per_layer.size() - 1)
			// 			break;
			// 	} else if (read_shape) {
			// 		upls = split(line, " ");
			// 		rows = std::atoi(upls[0].data());
			// 		cols = std::atoi(upls[1].data());
			// 		read_shape = false;
			// 	} else {
			// 		row_values = split(line, " ");
			// 		matrix_values.reserve(matrix_values.size() + row_values.size());
			// 		std::transform(row_values.begin(), row_values.end(),
			// 					   std::back_inserter(matrix_values),
			// 					   [](std::string &val) { return std::atof(val.data()); });
			// 	}
			// }
			// model->set_weight_martices(weights_matrices);

			// weights_matrices.resize(0);
			// weights_index = 0;
			// while (std::getline(file, line)) {
			// 	if (line.empty()) {
			// 		s21::Matrix<float> weights;
			// 		weights.set_data(matrix_values);
			// 		weights.set_cols(1);
			// 		weights.set_rows(units_per_layer[++weights_index]);
			// 		weights.set_shape(std::tuple<size_t, size_t> (units_per_layer[weights_index], 1));
			// 		weights_matrices.push_back(weights);
			// 		matrix_values.resize(0);
			// 		read_shape = true;
			// 		if (++weights_index >= units_per_layer.size() - 1)
			// 			break;
			// 	} else if (read_shape) {
			// 		upls = split(line, " ");
			// 		rows = std::atoi(upls[0].data());
			// 		cols = std::atoi(upls[1].data());
			// 		read_shape = false;
			// 	}
			// 	else
			// 		matrix_values.push_back(std::atof(line.data()));
			// }
			// model->set_bias(weights_matrices);

			// weights_matrices.resize(0);
			// weights_index = 0;
			// while (std::getline(file, line)) {
			// 	if (line.empty()) {
			// 		s21::Matrix<float> weights;
			// 		weights.set_data(matrix_values);
			// 		weights.set_cols(units_per_layer[weights_index]);
			// 		weights.set_rows(units_per_layer[++weights_index]);
			// 		weights.set_shape(std::tuple<size_t, size_t> (units_per_layer[weights_index], units_per_layer[weights_index - 1]));
			// 		weights_matrices.push_back(weights);
			// 		matrix_values.resize(0);
			// 		read_shape = true;
			// 		if (++weights_index >= units_per_layer.size())
			// 			break;
			// 	} else if (read_shape) {
			// 		upls = split(line, " ");
			// 		rows = std::atoi(upls[0].data());
			// 		cols = std::atoi(upls[1].data());
			// 		read_shape = false;
			// 	} else {
			// 		row_values = split(line, " ");
			// 		matrix_values.reserve(matrix_values.size() + row_values.size());
			// 		std::transform(row_values.begin(), row_values.end(),
			// 					   std::back_inserter(matrix_values),
			// 					   [](std::string &val) { return std::atof(val.data()); });
			// 	}
			// }
			// model->set_neuron_values(weights_matrices);

			// weights_matrices.resize(0);
			// weights_index = 0;
			// while (std::getline(file, line)) {
			// 	if (line.empty()) {
			// 		s21::Matrix<float> weights;
			// 		weights.set_data(matrix_values);
			// 		weights.set_cols(units_per_layer[weights_index]);
			// 		weights.set_rows(units_per_layer[++weights_index]);
			// 		weights.set_shape(std::tuple<size_t, size_t> (units_per_layer[weights_index], units_per_layer[weights_index - 1]));
			// 		weights_matrices.push_back(weights);
			// 		matrix_values.resize(0);
			// 		read_shape = true;
			// 		if (++weights_index >= units_per_layer.size())
			// 			break;
			// 	} else if (read_shape) {
			// 		upls = split(line, " ");
			// 		rows = std::atoi(upls[0].data());
			// 		cols = std::atoi(upls[1].data());
			// 		read_shape = false;
			// 	} else {
			// 		row_values = split(line, " ");
			// 		matrix_values.reserve(matrix_values.size() + row_values.size());
			// 		std::transform(row_values.begin(), row_values.end(),
			// 					   std::back_inserter(matrix_values),
			// 					   [](std::string &val) { return std::atof(val.data()); });
			// 	}
			// }
			// model->set_error(weights_matrices);
			// file.close();
		}
	};
}

#endif //SIMPLEMLP_MLPSERIALIZER_HPP

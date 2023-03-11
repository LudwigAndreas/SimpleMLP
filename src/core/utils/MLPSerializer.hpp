
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
			for (auto weights: model->get_weight_matrices())
				file << weights;
			for (auto bias: model->get_bias_vectors())
				file << bias;
			for (auto neuron_values: model->get_neuron_values())
				file << neuron_values;
			for (auto error: model->get_error())
				file << error;
			for (auto incorrect_values: model->get_incorrect_values())
				file << incorrect_values;
			for (auto raw: model->get_raw())
				file << raw;
			file.close();
		}

		static std::vector< s21::Matrix<T> > readVectorMatrix(std::istream &input, size_t size) {
			std::vector<s21::Matrix<T>>	result;
			s21::Matrix<T>				matrix;

			result.reserve(size);
			for (int i = 0; i < size; ++i) {
				input >> matrix;
				result.push_back(matrix);
			}
			return (std::move(result));
			// model->set_weight_martices(weights_matrices);
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

			model->set_weight_martices	(readVectorMatrix(file, units_per_layer.size() - 1));
			model->set_bias				(readVectorMatrix(file, units_per_layer.size() - 1));
			model->set_neuron_values	(readVectorMatrix(file, units_per_layer.size()	 ));
			model->set_error			(readVectorMatrix(file, units_per_layer.size()	 ));
			model->set_incorrect_values	(readVectorMatrix(file, units_per_layer.size()	 ));
			model->set_raw				(readVectorMatrix(file, units_per_layer.size()	 ));



			// for (unsigned long i : units_per_layer) {
			// 	neuron_values	.emplace_back(1, i);
			// 	incorrect_values.emplace_back(1, i);
			// 	raw				.emplace_back(1, i);
			// 	error			.emplace_back(1, i);
			// }
			return (IMLPModel<float> *)model;
		}
	};	
}

#endif //SIMPLEMLP_MLPSERIALIZER_HPP

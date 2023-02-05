#include <functional>
#include <random>
#include <vector>
#include <cmath>
#include <chrono>
#include <cassert>
#include <iostream>
#include <tuple>
#include <fstream>
#include <string>

#include "MLPMatrixModelv2.hpp"
#include "MLPSerializer.hpp"

int SearchMaxIndex(std::vector<float> value) {
	double max = value[0];
	int prediction = 0;
	double tmp;
	for (int j = 1; j < value.size(); j++) {
		tmp = value[j];
		if (tmp > max) {
			prediction = j;
			max = tmp;
		}
	}
	return prediction;
}
void log(std::fstream &file, const float &x, const s21::Matrix<float> &y, const std::vector<float> &y_hat){
	auto correct_guess = SearchMaxIndex(y.ToVector());
	auto mse = (y(correct_guess, 0) - y_hat[correct_guess]);
	mse = mse*mse;

	file << ((correct_guess == SearchMaxIndex(y_hat)) ? "✅" : "❌") << ' '
		 << char('A' + correct_guess) << " "
		 << char('A' + SearchMaxIndex(y_hat)) << ' ' 
		 << y_hat[SearchMaxIndex(y_hat)] * 100 << "%\t"
		 << mse << std::endl;
}

std::vector<std::string> split (std::string s, std::string delimiter) {
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

int main() {
	s21::IMLPModel<float>		*model = s21::MLPMatrixModelv2::MakeModel(784, 26, 256, 2, .1f);
	std::vector<s21::Sample>	samples;
	samples.reserve(88800);
	std::chrono::time_point<std::chrono::system_clock> start, end;
	// auto model = s21::MLPMatrixModel<float>::Instance(0, 0, 0, 0, 0);
	// MLPSerializer<float>::DeserializeMLPMatrixModel((s21::MLPMatrixModel<float> *)model, "testmodel.mlpmodel");

	std::fstream file;
	std::string str;
	file.open("datasets/emnist-letters-train.csv", std::ofstream::in);	
	while (file >> str) {
		std::vector<std::string> letter = split(str, ",");
		std::vector<float> pixels;
		std::vector<float> answer(26, 0);
		answer[std::atoi(letter[0].data()) - 1] = 1;

		for (auto it = letter.begin() + 1; it < letter.end(); ++it)
			pixels.push_back(std::atoi((*it).data()));
		s21::Sample s(pixels, answer);
		samples.push_back(s);
	}
	file.close();
	std::cerr << "Dataset loaded! " << samples.size() << " samples." << std::endl;
	s21::Dataset dataset(samples, 32);
	std::cerr << "Dataset split on " << dataset.size() << " with " << dataset[0].size() << " samples in each." << std::endl;

	model->CrossValidation(dataset);
	MLPSerializer<float>::SerializeMLPMatrixModel((s21::MLPMatrixModelv2 *)(model), "testmodel.mlpmodel");
		// std::cout << "\nAccuracy: " << ((float)corr / i) * 100 << '%' << std::endl;
}

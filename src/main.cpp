#include <functional>
#include <random>
#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>
#include <tuple>

#include "Matrix.hpp"
#include "IMLPModel.hpp"
#include "MLPMatrixModel.hpp"
#include <fstream>
#include "string"
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
	return prediction + 1;
}
void log(std::fstream &file, const float &x, const s21::Matrix<float> &y, const std::vector<float> &y_hat){
	auto mse = (y(0, 0) - y_hat[0]);
	mse = mse*mse;

	file << mse << " "
		 << x << " "
		 << SearchMaxIndex(y.ToVector()) << " "
		 << SearchMaxIndex(y_hat) << " \n";
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

int main(int argc, char **argv) {
	(void )argc;
	(void )argv;
//	s21::Matrix<float> M = s21::GenerateNDMatrix<float>(3, 3);
//
//	PrintShape(M);
//	std::cout << M << std::endl;
//	std::cout << (M - M) << std::endl;
//	std::cout << M.multiply_scalar(2.f) << std::endl;
//	std::cout << M.multiply_elementwise(M) << std::endl;
//
//	s21::Matrix<float> MT = M.T();
//	std::cout << MT << std::endl;
//	std::cout << MT.matmul(M) << std::endl;
//	std::cout << M.apply_function([](float x){ return x-x; }) << std::endl;

//	s21::IMLPModel<float> *model = s21::MLPMatrixModel<float>::Instance(1, 1, 15, 3, .5f);
//
//	std::fstream file;
//	file.open("data.txt", std::ofstream::out | std::ofstream::trunc);
//	const float PI = 3.14159;
//	for (int i = 0; i < 100000; ++i) {
//		auto x = s21::GenerateNDMatrix<float>(1, 1).multiply_scalar(PI);
//		while (x(0, 0) > PI / 2)
//			x(0, 0) -= PI / 2;
//		while (x(0, 0) < -PI / 2)
//			x(0, 0) += PI / 2;
//		auto y = x.apply_function([](float v) -> float {return sin(v) * sin(v) * sin(v) * sin(v); });
//
//		auto y_hat = model->Forward(x);
//		model->Backward(y);
//
//		if (i % 50 == 0)
//			log(file, x, y, y_hat);
//	}
	s21::IMLPModel<float> *model = s21::MLPMatrixModel<float>::Instance(784, 26, 256, 2, .5f);

	std::fstream file, output;
	file.open("/Users/landreas/42Course/SimpleMLP/datasets/emnist-letters/emnist-letters-train.csv", std::ofstream::in);
	output.open("/Users/landreas/42Course/SimpleMLP/src/data.txt", std::ofstream::out | std::ofstream::trunc);
	std::string str;
	int i = 0;
	while (file >> str) {
		std::vector<std::string> letter = split(str, ",");
		std::vector<float> pixels;
		std::vector<float> answer(26, 0);
		answer[std::atoi(letter[0].data()) - 1] = 1;
		s21::Matrix<float> y(answer);

		for (auto it = letter.begin() + 1; it < letter.end(); ++it)
			pixels.push_back(std::atoi((*it).data()));
		s21::Matrix<float> x(pixels);
		auto y_hat = model->Forward(x);
		model->Backward(y);

		if (++i % 50 == 0)
			log(output, (float)i / 1000, y, y_hat);
	}
}
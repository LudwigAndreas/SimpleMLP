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

	s21::IMLPModel<float> *model = s21::MLPMatrixModel<float>::Instance(1, 1, 15, 3, .5f);

	const float PI = 3.14159;
	for (int i = 0; i < 10000; ++i) {
		auto x = s21::GenerateNDMatrix<float>(1, 1).multiply_scalar(PI);
		auto y = x.apply_function([](float v) -> float {return 2 * v; });

		auto y_hat = model->Forward(x);
		model->Backward(y);

		std::cout << "X = " << x << "Expected: " << y << "Result:   "<< y_hat[0] << "\n\nError:    " << (y(0, 0) - y_hat[0]) * (y(0, 0) - y_hat[0]) << std::endl << "---------------------------" << std::endl;
	}
}
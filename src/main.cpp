#include <functional>
#include <random>
#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>
#include <tuple>

#include "Matrix.hpp"

template <typename T>
struct mtx {
	static Matrix<T> randn(size_t rows, size_t cols) {
		Matrix<T> M(rows, cols);

		std::random_device rd;
		std::mt19937 gen(rd());

		// init Gaussian distr. w/ N(mean=0, stdev=1/sqrt(numel))
		T n(M.get_number_of_elements());
		T stdev(1 / sqrt(n));
		std::normal_distribution <T> d(0, stdev);

		// fill each element w/ draw from distribution
		for (size_t r = 0; r < rows; ++r) {
			for (size_t c = 0; c < cols; ++c) {
				M(r, c) = d(gen);
			}
		}
		return M;
	}
};



int main(int argc, char **argv) {
	(void )argc;
	(void )argv;
	Matrix<float> M = mtx<float>::randn(3, 3);

	PrintShape(M);
	std::cout << M << std::endl;
	std::cout << (M - M) << std::endl;
	std::cout << M.multiply_scalar(2.f) << std::endl;
	std::cout << M.multiply_elementwise(M) << std::endl;

	Matrix<float> MT = M.T();
	std::cout << MT << std::endl;
	std::cout << MT.matmul(M) << std::endl;
	std::cout << M.apply_function([](float x){ return x-x; }) << std::endl;
}
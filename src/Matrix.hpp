#ifndef SIMPLEMLP_MATRIX_HPP
#define SIMPLEMLP_MATRIX_HPP

#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>
#include <tuple>
#include <functional>
#include <random>

template <typename Type>
class Matrix {
private:
	size_t cols;
	size_t rows;
	std::tuple<size_t, size_t> shape;
	int numel = rows * cols;
	std::vector<Type> data;

public:

	/* constructors */
	Matrix() : cols(0), rows(0) {
//		data = std::vector<T>(cols * rows, 0);
//		std::vector<Type> data(cols * rows, Type());
//		data = std::vector<T>(cols * rows, T());
		data.reserve(0);
		shape = (std::tuple<size_t, size_t>) {rows, cols};
	}

	Matrix(size_t rows, size_t cols) : cols(cols), rows(rows) {
//		data = std::vector<T>(cols * rows, T());
//		std::vector<Type> data(cols * rows, Type());
		data.reserve(cols * rows);
		shape = (std::tuple<size_t, size_t>) {rows, cols};
	}

//	Matrix &operator=(const Matrix<T> matrix);

	~Matrix() {}

	/* getters */
	size_t get_cols() const { return cols; }

	size_t get_rows() const { return rows; }

	std::tuple<size_t, size_t> get_shape() const { return shape; }

	int get_number_of_elements() const { return numel; }

	Type& operator()(size_t row, size_t col) {
		return data[row * col + col];
	}

	/*  linear algebra methods */

	/* Matrix multiplication */
	Matrix matmul(Matrix &target) {
		assert(cols == target.get_cols());
		Matrix output(rows, target.get_cols());

		for (size_t r = 0; r < output.get_rows(); ++r) {
			for (size_t c = 0; c < output.get_cols(); ++c) {
				for (size_t k = 0; k < target.get_rows(); ++k) {
					output(r, c) += (*this)(r, k) * target(k, c);
				}
			}
		}
		return output;
	}

	Matrix multiply_elementwise(Matrix &target){
		assert(shape == target.get_shape());
		Matrix output((*this));
		for (size_t r = 0; r < output.get_rows(); ++r) {
			for (size_t c = 0; c < output.get_cols(); ++c) {
				output(r, c) = target(r,c) * (*this)(r, c);
			}
		}
		return output;
	}

	Matrix square() {
		Matrix output((*this));
		output = multiply_elementwise(output);
		return output;
	}

	Matrix multiply_scalar(Type scalar) {
		Matrix output((*this));
		for (size_t r = 0; r < output.get_rows(); ++r) {
			for (size_t c = 0; c < output.get_cols(); ++c) {
				output(r, c) = scalar * (*this)(r, c);
			}
		}
		return output;
	}

	/* Matrix addition */
	Matrix add(Matrix &target) {
		assert(shape == target.get_shape());
		Matrix output(rows, std::get<1>(target.get_shape()));

		for (size_t r = 0; r < output.get_rows(); ++r) {
			for (size_t c = 0; c < output.get_cols(); ++c) {
				output(r, c) = (*this)(r, c) + target(r, c);
			}
		}
		return output;
	}

	Matrix operator+(Matrix &target) {
		return add(target);
	}

	/* Matrix subtraction */
	Matrix operator-() {
		Matrix output(rows, cols);
		for (size_t r = 0; r < rows; ++r) {
			for (size_t c = 0; c < cols; ++c) {
				output(r, c) = -(*this)(r, c);
			}
		}
		return output;
	}


	Matrix sub(Matrix<Type> &target) {
		Matrix neg_target = -target;
		return add(neg_target);
	}

	Matrix operator-(Matrix<Type> &target) {  // for cleaner usage
		return sub(target);
	}

	/* Matrix trasnposing */
	Matrix transpose() {
		size_t new_rows{cols}, new_cols{rows};
		Matrix transposed(new_rows, new_cols);

		for (size_t r = 0; r < new_rows; ++r) {
			for (size_t c = 0; c < new_cols; ++c) {
				transposed(r, c) = (*this)(c, r);  // swap row and col
			}
		}
		return transposed;
	}

	Matrix T(){ // Similar to numpy, etc.
		return transpose();
	}

	Matrix apply_function(const std::function<Type(const Type &)> &function) {
		Matrix output((*this));
		for (size_t r = 0; r < rows; ++r) {
			for (size_t c = 0; c < cols; ++c) {
				output(r, c) = function((*this)(r, c));
			}
		}
		return output;
	}


};

	/* print methods [or move it to another class] */
//template <typename Type>
//std::ostream &operator<<(std::ostream &os, const Matrix<Type> matrix) {
//	for (size_t r = 0; r < matrix.get_rows(); ++r) {
//		for (size_t c = 0; c < matrix.get_cols(); ++c) {
//			os << matrix(r, c) << " ";
//		}
//		os << std::endl;
//	}
//	os << std::endl;
//	return os;
//}

template <typename Type>
void print(Matrix<Type> matrix) {
	for (size_t r = 0; r < matrix.get_rows(); ++r) {
		for (int c = 0; c < matrix.get_cols(); ++c) {
			std::cout << matrix(r, c) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

template <typename Type>
void PrintShape(Matrix<Type> matrix) {
	std::cout << "Matrix Size([" << matrix.get_rows() << ", " << matrix.get_cols() << "])" << std::endl;
}


#endif

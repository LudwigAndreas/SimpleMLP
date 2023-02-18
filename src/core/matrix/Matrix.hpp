#ifndef SIMPLEMLP_MATRIX_HPP
#define SIMPLEMLP_MATRIX_HPP

#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>
#include <tuple>
#include <functional>
#include <random>
#include <exception>
#include <csignal>

namespace s21 {
	template<typename Type>
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
			data.resize(0);
			shape = (std::tuple<size_t, size_t>) {rows, cols};
		}

		Matrix(size_t rows, size_t cols) : cols(cols), rows(rows) {
			data.resize(cols * rows);
			shape = (std::tuple<size_t, size_t>) {rows, cols};
		}

		Matrix(std::vector<Type> vector) : cols(vector.size()), rows(1) {
		// Matrix(std::vector<Type> vector, int cols) : cols(1), rows(vector.size()) {
			data = vector;
			shape = (std::tuple<size_t, size_t>) {rows, cols};
		}

		Matrix &operator=(const Matrix<Type> matrix) {
			this->rows = matrix.get_rows();
			this->cols = matrix.get_cols();
			this->shape = (std::tuple<size_t, size_t>) {rows, cols};
			this->numel = cols * rows;
			data.clear();
			data.resize(cols * rows);
			for (int c = 0; c < cols; ++c) {
				for (int r = 0; r < rows; ++r) {
					(*this)(r, c) = matrix(r, c);
				}
			}
			return (*this);
		}

		~Matrix() {}

		/* getters */
		size_t get_cols() const { return cols; }

		size_t get_rows() const { return rows; }

		std::tuple<size_t, size_t> get_shape() const { return shape; }

		int get_number_of_elements() const { return numel; }

		void set_cols(size_t cols) {
			Matrix::cols = cols;
		}

		void set_rows(size_t rows) {
			Matrix::rows = rows;
		}

		void set_shape(const std::tuple<size_t, size_t> &shape) {
			Matrix::shape = shape;
		}

		void set_numel(int numel) {
			Matrix::numel = numel;
		}

		void set_data(const std::vector<Type> &data) {
			Matrix::data = data;
		}

		void update_shape() {
			std::get<0>(Matrix::shape) = get_rows();
			std::get<1>(Matrix::shape) = get_cols();
		}

		Type &operator()(size_t row, size_t col) {
			return data[row * cols + col];
		}

		const Type &operator()(size_t row, size_t col) const {
			return data[row * cols + col];
		}

		/*  linear algebra methods */

		/* Matrix multiplication */

		Matrix multiply_elementwise(Matrix &target) {
			assert(shape == target.get_shape());
			Matrix output((*this));
			for (size_t r = 0; r < output.get_rows(); ++r) {
				for (size_t c = 0; c < output.get_cols(); ++c) {
					output(r, c) = target(r, c) * (*this)(r, c);
				}
			}
			return output;
		}

		Matrix matmul(Matrix &target) {
			if (cols != target.get_rows())
				std::raise(SIGTRAP);
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

		Matrix operator&(const Matrix &target) const	{ return multiply_elementwise(target); }
		Matrix operator&(Matrix target)					{ return multiply_elementwise(target); }
		Matrix operator*(const Matrix &target) const	{ return matmul(target); }
		Matrix operator*(Matrix target)  				{ return matmul(target); }

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

		Matrix operator*(Type number) {
			return multiply_scalar(number);
		}

		/* Matrix addition */
		Matrix add(const Matrix &target) const {
			if (shape != target.get_shape())
				std::raise(SIGTRAP);
			Matrix output(rows, std::get<1>(target.get_shape()));

			for (size_t r = 0; r < output.get_rows(); ++r) {
				for (size_t c = 0; c < output.get_cols(); ++c) {
					output(r, c) = (*this)(r, c) + target(r, c);
				}
			}
			return output;
		}
		
		Matrix add(Matrix target) {
			if (shape != target.get_shape())
				std::raise(SIGTRAP);
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


		Matrix sub(const Matrix<Type> &target) const {
			Matrix neg_target = -target;
			return add(neg_target);
		}

		Matrix sub(Matrix<Type> target) {
			Matrix neg_target = -target;
			return add(neg_target);
		}

		Matrix operator-(const Matrix<Type> &target) const {  // for cleaner usage
			return sub(target);
		}

		Matrix operator-(Matrix<Type> target) {  // for cleaner usage
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

		Matrix T() { // Similar to numpy, etc.
			return transpose();
		}

		Matrix
		apply_function(const std::function<Type(const Type &)> &function) {
			Matrix output((*this));
			for (size_t r = 0; r < rows; ++r) {
				for (size_t c = 0; c < cols; ++c) {
					output(r, c) = function((*this)(r, c));
				}
			}
			return output;
		}

		std::vector<Type> ToVector() const {
			return data;
		}

		// static Matrix getY(std::vector<Type> values) {
		// 	Matrix y(values);
		// 	int tmp;
		// 	tmp = y.get_cols();
		// 	y.set_cols(y.get_rows());
		// 	y.update_shape();
		// 	return y;
		// }
	};

	class Vector : public Matrix<float> {

	};

	/* print methods [or move it to another class] */
	template<typename Type>
	std::ostream &operator<<(std::ostream &os, const Matrix<Type> &matrix) {
		os << matrix.get_rows() << ' ' << matrix.get_cols() << std::endl;
		for (size_t r = 0; r < matrix.get_rows(); ++r) {
			for (size_t c = 0; c < matrix.get_cols(); ++c) {
				os << matrix(r, c) << " ";
			}
			os << std::endl;
		}
		os << std::endl;
		return os;
	}

	template<typename Type>
	std::istream &operator>>(std::istream &is, Matrix<Type> &matrix) {
		int							rows, cols;
		std::vector<float>			data;
		// std::vector<std::string>	split_line;
		// std::string					line;
		float						tmp;

		is >> rows >> cols;
		data.reserve(rows * cols);
		for (size_t elem = 0; elem < rows * cols; ++elem) {
			is >> tmp;
			data.push_back(tmp);
		}
		matrix = Matrix<float>(data);
		matrix.set_rows(rows);
		matrix.set_cols(cols);
		matrix.update_shape();
		return is;
	}

	template<typename Type>
	void PrintShape(Matrix<Type> matrix) {
		std::cout << "Matrix Size([" << matrix.get_rows() << ", "
				  << matrix.get_cols() << "])" << std::endl;
	}

	template <typename T>
	static Matrix<T> GenerateNDMatrix(size_t rows, size_t cols) {
		Matrix<T> M(rows, cols);

		// std::random_device rd;
		// std::mt19937 gen(rd());
		std::mt19937 gen(time(nullptr));

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
}

#endif

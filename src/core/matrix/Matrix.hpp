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
#include <algorithm>

namespace s21 {
	template<typename Type>
	class Matrix {
	private:
		size_t cols;
		size_t rows;
		std::tuple<size_t, size_t> shape;
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

        Matrix(std::vector<Type> vector) : cols(vector.size()), rows(1), data(std::move(vector)) {
            shape = (std::tuple<size_t, size_t>) {rows, cols};
        }

        Matrix(std::vector<Type> vector, size_t rows, size_t cols) : cols(cols), rows(rows), data(std::move(vector)) {
            shape = (std::tuple<size_t, size_t>) {rows, cols};
        }

		Matrix &operator=(const Matrix<Type> matrix) {
			this->rows = matrix.get_rows();
			this->cols = matrix.get_cols();
			this->shape = (std::tuple<size_t, size_t>) {rows, cols};
            data = matrix.ToVector();
			return (*this);
		}

		~Matrix() {}

		/* getters */
		size_t get_cols() const { return cols; }

		size_t get_rows() const { return rows; }

		size_t size() const { return cols * rows; }

		std::tuple<size_t, size_t> get_shape() const { return shape; }

		void set_cols(size_t cols) {
			Matrix::cols = cols;
			std::get<1>(shape) = cols;
		}

		void set_rows(size_t rows) {
			Matrix::rows = rows;
			std::get<0>(shape) = rows;
		}

		void set_shape(const std::tuple<size_t, size_t> &shape) {
			Matrix::shape = shape;
			rows = std::get<0>(shape);
			cols = std::get<1>(shape);

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

        Type &operator[](size_t index) {
            return data[index];
        }

		const Type &operator()(size_t row, size_t col) const {
			return data[row * cols + col];
		}

        const Type &operator[](size_t index) const {
            return data[index];
        }

		/*  linear algebra methods */

		/* Matrix multiplication */

		Matrix multiply_elementwise(Matrix &target) {
			assert(shape == target.get_shape());
			Matrix output((*this));
            // #pragma omp parallel for
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
            std::vector<Type> transposed = target.T().ToVector();
            typename std::vector<Type>::iterator begin, end, tbegin;

            // #pragma omp parallel for
            begin = data.begin();
            end = data.begin() + cols;
            for (size_t r = 0; r < output.get_rows(); ++r) {
                tbegin = transposed.begin();
                for (size_t c = 0; c < output.get_cols(); ++c) {
                    output(r, c) = std::inner_product(begin, end,
                                                      tbegin, 0.f);
                    tbegin += cols;
                }
                begin = end;
                end += cols;
            }
            return output;
        }

        Matrix matmulTransposed(Matrix &target) {
            if (cols != target.get_cols())
                std::raise(SIGTRAP);

            Matrix output(rows, target.get_rows());
            std::vector<Type> transposed = target.ToVector();
            typename std::vector<Type>::iterator begin, end, tbegin;

            // #pragma omp parallel for
            begin = data.begin();
            end = data.begin() + cols;
            for (size_t r = 0; r < output.get_rows(); ++r) {
                tbegin = transposed.begin();
                for (size_t c = 0; c < output.get_cols(); ++c) {
                    output(r, c) = std::inner_product(begin, end,
                                                      tbegin, 0.f);
                    tbegin += cols;
                }
                begin = end;
                end += cols;
            }
            return output;
        }

		Matrix operator&(const Matrix &target) const	{ return multiply_elementwise(target); }
		Matrix operator&(Matrix target)					{ return multiply_elementwise(target); }
		Matrix operator*(const Matrix &target) const	{ return matmul(target); }
		Matrix operator*(Matrix target)  				{ return matmul(target); }
		Matrix operator*(Type number) 					{ return multiply_scalar(number); }

		Matrix square() {
			Matrix output((*this));
			output = multiply_elementwise(output);
			return output;
		}

		Matrix multiply_scalar(Type scalar) {
			Matrix output((*this));
            // #pragma omp parallel for
			for (size_t r = 0; r < output.get_rows(); ++r) {
				for (size_t c = 0; c < output.get_cols(); ++c) {
					output(r, c) = scalar * (*this)(r, c);
				}
			}
			return output;
		}

		/* Matrix addition */
		Matrix add(const Matrix &target) const {
			if (shape != target.get_shape())
				std::raise(SIGTRAP);
			Matrix output(rows, cols);
            // #pragma omp parallel for
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
			Matrix output(rows, cols);
            // #pragma omp parallel for
			for (size_t r = 0; r < output.get_rows(); ++r) {
				for (size_t c = 0; c < output.get_cols(); ++c) {
					output(r, c) = (*this)(r, c) + target(r, c);
				}
			}
			return output;
		}

		Matrix operator+(Matrix target) {
			return add(target);
		}

		Matrix operator+(const Matrix &target) const {
			return add(target);
		}

		/* Matrix subtraction */
		Matrix operator-() {
			Matrix output(rows, cols);
            // #pragma omp parallel for
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

//        void transpose(double *dst, const double *src, size_t n, size_t p) noexcept {
//            size_t block = 32;
//            for (size_t i = 0; i < n; i += block) {
//                for (size_t j = 0; j < p; ++j) {
//                    for (size_t b = 0; b < block && i + b < n; ++b) {
//                        dst[j*n + i + b] = src[(i + b)*p + j];
//                    }
//                }
//            }
//        }

		/* Matrix transposing */
        Matrix transpose() noexcept {
            // new rows = cols;
            // new cols = rows;
            Matrix transposed(cols, rows);//(cols, rows);
            const size_t block = 16;
            // #pragma omp parallel for
            for (size_t i = 0; i < rows; i += block) {
                for (size_t j = 0; j < cols; ++j) {
                    for (size_t b = 0; b < block && i + b < rows; ++b)
                        transposed[j * rows + i + b] = data[(i + b) * cols + j];  // swap row and col
//                    transposed(r, c) = (*this)(c, r);  // swap row and col
                }
            }
            return transposed;
        }

		Matrix T() { // Similar to numpy, etc.
			return transpose();
		}

		Matrix
		apply_function(const std::function<Type(const Type &)> &function) {
			Matrix output(rows, cols);
            // #pragma omp parallel for
			for (size_t r = 0; r < rows; ++r) {
				for (size_t c = 0; c < cols; ++c) {
					output(r, c) = function((*this)(r, c));
				}
			}
			return output;
		}

        const std::vector<Type>& ToVector() const {
            return data;
        }

        std::vector<Type> &ToVector() {
            return data;
        }
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
		float						tmp;

		is >> rows >> cols;
		data.reserve(rows * cols);
		for (int i = 0; i < rows * cols; ++i) {
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

		std::random_device rd;
		std::mt19937 gen(rd());
		// std::mt19937 gen(time(nullptr));

		// init Gaussian distr. w/ N(mean=0, stdev=1/sqrt(numel))
		T n(M.get_cols() * M.get_rows());
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

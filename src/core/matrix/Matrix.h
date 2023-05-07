#ifndef SIMPLEMLP_MATRIX_H
#define SIMPLEMLP_MATRIX_H

#include <algorithm>
#include <cassert>
#include <cmath>
#include <csignal>
#include <exception>
#include <functional>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <vector>

#include "../exceptions/MatrixException.h"

namespace s21 {
template <typename Type>
class Matrix {
 private:
  size_t rows;
  size_t cols;
  std::tuple<size_t, size_t> shape;
  std::vector<Type> data;

 public:
  /* constructors */
  Matrix() : rows(0), cols(0) {
    data.resize(0);
    shape = (std::tuple<size_t, size_t>){rows, cols};
  }

  Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
    data.resize(rows * cols);
    shape = (std::tuple<size_t, size_t>){rows, cols};
  }

  Matrix(std::vector<Type> vector)
      : rows(1), cols(vector.size()), data(std::move(vector)) {
    shape = (std::tuple<size_t, size_t>){rows, cols};
  }

  Matrix(std::vector<Type> vector, size_t rows, size_t cols)
      : rows(rows), cols(cols), data(std::move(vector)) {
    shape = (std::tuple<size_t, size_t>){rows, cols};
  }

  Matrix(const Matrix<Type> &matrix) = default;

  Matrix(Matrix<Type> &&matrix) = default;

  Matrix &operator=(const Matrix<Type> matrix) {
    Matrix::rows = matrix.get_rows();
    Matrix::cols = matrix.get_cols();
    Matrix::shape = (std::tuple<size_t, size_t>){rows, cols};
    data = matrix.ToVector();
    return (*this);
  }

  ~Matrix() {}

  /* getters */
  size_t get_cols() const { return cols; }

  size_t get_rows() const { return rows; }

  std::tuple<size_t, size_t> get_shape() const { return shape; }

  size_t size() const { return data.size(); }

  std::vector<Type> get_data() { return Matrix::data; }

  std::vector<Type> get_data() const { return Matrix::data; }

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

  void set_data(const std::vector<Type> &data) { Matrix::data = data; }

  Type &operator()(size_t row, size_t col) {
    if (row * cols + col >= data.size())
      throw std::out_of_range(
          "Matrix out of bounds::operator()(size_t, size_t)");
    return data[row * cols + col];
  }

  Type &operator[](size_t index) {
    if (index >= data.size())
      throw std::out_of_range("Matrix out of bounds::operator[](size_t)");
    return data[index];
  }

  const Type &operator()(size_t row, size_t col) const {
    return data[row * cols + col];
  }

  const Type &operator[](size_t index) const { return data[index]; }

  /* Equality operators */

  bool operator==(const Matrix &other) const {
    return this->data == other.get_data() && this->shape == other.get_shape();
  }

  bool operator!=(const Matrix &other) const {
    return this->data != other.get_data() || this->shape != other.get_shape();
  }

  /*  Linear algebra methods */

  /* Matrix multiplication */

  Matrix ElementwiseMultiplication(Matrix &target) {
    if (shape != target.get_shape())
      throw MatrixCalculationsException(
          "Matrix Multiplication Exception: ElementwiseMultiplication(Matrix "
          "&). "
          "Shape is not valid");
    Matrix output((*this));
    for (size_t r = 0; r < output.get_rows(); ++r) {
      for (size_t c = 0; c < output.get_cols(); ++c) {
        output(r, c) = target(r, c) * (*this)(r, c);
      }
    }
    return output;
  }

  Matrix MatrixMultiplication(Matrix &target) {
    if (cols != target.get_rows())
      throw MatrixCalculationsException(
          "Matrix Multiplication Exception: MatrixMultiplication(Matrix &). "
          "Matrix "
          "dimensions not match");

    Matrix output(rows, target.get_cols());
    std::vector<Type> transposed = target.T().ToVector();
    typename std::vector<Type>::iterator begin, end, tbegin;

    // #pragma omp parallel for
    begin = data.begin();
    end = data.begin() + cols;
    for (size_t r = 0; r < output.get_rows(); ++r) {
      tbegin = transposed.begin();
      for (size_t c = 0; c < output.get_cols(); ++c) {
        output(r, c) = std::inner_product(begin, end, tbegin, 0.f);
        tbegin += cols;
      }
      begin = end;
      end += cols;
    }
    return output;
  }

  Matrix MatrixMultiplicationTransposed(Matrix &target) {
    if (cols != target.get_cols()) raise(SIGTRAP);
    // throw MatrixCalculationsException("Matrix Multiplication Exception:
    // MatrixMultiplicationTransposed(Matrix). Matrix dimensions not match");

    Matrix output(rows, target.get_rows());
    std::vector<Type> transposed = target.ToVector();
    typename std::vector<Type>::iterator begin, end, tbegin;

    // #pragma omp parallel for
    begin = data.begin();
    end = data.begin() + cols;
    for (size_t r = 0; r < output.get_rows(); ++r) {
      tbegin = transposed.begin();
      for (size_t c = 0; c < output.get_cols(); ++c) {
        output(r, c) = std::inner_product(begin, end, tbegin, 0.f);
        tbegin += cols;
      }
      begin = end;
      end += cols;
    }
    return output;
  }

  Matrix operator&(const Matrix &target) const {
    return ElementwiseMultiplication(target);
  }
  Matrix operator&(Matrix target) { return ElementwiseMultiplication(target); }
  Matrix operator*(const Matrix &target) const {
    return MatrixMultiplication(target);
  }
  Matrix operator*(Matrix target) { return MatrixMultiplication(target); }
  Matrix operator*(Type number) { return ScalarMultiplication(number); }

  Matrix Square() {
    Matrix output((*this));
    output = ElementwiseMultiplication(output);
    return output;
  }

  Matrix ScalarMultiplication(Type scalar) {
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
  Matrix Add(const Matrix &target) const {
    if (shape != target.get_shape())
      throw MatrixCalculationsException(
          "Matrix Addition Exception: Add(Matrix &). Matrix dimensions not "
          "match");
    Matrix output(rows, cols);
    // #pragma omp parallel for
    for (size_t r = 0; r < output.get_rows(); ++r) {
      for (size_t c = 0; c < output.get_cols(); ++c) {
        output(r, c) = (*this)(r, c) + target(r, c);
      }
    }
    return output;
  }

  Matrix Add(Matrix target) {
    if (shape != target.get_shape())
      throw MatrixCalculationsException(
          "Matrix Addition Exception: Add(Matrix). Matrix dimensions not "
          "match");
    Matrix output(rows, cols);
    // #pragma omp parallel for
    for (size_t r = 0; r < output.get_rows(); ++r) {
      for (size_t c = 0; c < output.get_cols(); ++c) {
        output(r, c) = (*this)(r, c) + target(r, c);
      }
    }
    return output;
  }

  Matrix operator+(Matrix target) { return Add(target); }

  Matrix operator+(const Matrix &target) const { return Add(target); }

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

  Matrix Sub(const Matrix<Type> &target) const {
    Matrix neg_target = -target;
    return Add(neg_target);
  }

  Matrix Sub(Matrix<Type> target) {
    Matrix neg_target = -target;
    return Add(neg_target);
  }

  Matrix operator-(const Matrix<Type> &target) const {  // for cleaner usage
    return Sub(target);
  }

  Matrix operator-(Matrix<Type> target) {  // for cleaner usage
    return Sub(target);
  }

  /* Matrix transposing */
  Matrix Transpose() noexcept {
    Matrix transposed(cols, rows);
    const size_t block = 16;
    // #pragma omp parallel for
    for (size_t i = 0; i < rows; i += block) {
      for (size_t j = 0; j < cols; ++j) {
        for (size_t b = 0; b < block && i + b < rows; ++b)
          transposed[j * rows + i + b] =
              data[(i + b) * cols + j];  // swap row and col
      }
    }
    return transposed;
  }

  Matrix T() { return Transpose(); }

  Matrix ApplyFunction(const std::function<Type(const Type &)> &function) {
    Matrix output(rows, cols);
    // #pragma omp parallel for
    for (size_t r = 0; r < rows; ++r) {
      for (size_t c = 0; c < cols; ++c) {
        output(r, c) = function((*this)(r, c));
      }
    }
    return output;
  }

  const std::vector<Type> &ToVector() const { return data; }

  std::vector<Type> &ToVector() { return data; }
};

/* print methods [or move it to another class] */
template <typename Type>
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

template <typename Type>
std::istream &operator>>(std::istream &is, Matrix<Type> &matrix) {
  std::vector<float> data;
  std::stringstream ss;
  std::string line;
  size_t input_size;
  size_t size;
  size_t i;
  size_t j;
  float weight = 0;

  line = "";
  while (line.empty()) std::getline(is, line);
  ss = std::stringstream(line);
  ss >> input_size >> size;
  if (input_size <= 0 || input_size > 0xFFFF || size <= 0 || size > 0xFFFF)
    throw MatrixCalculationsException("Incorrect matrix size.");
  data.reserve(input_size * size);
  for (j = 0; j < input_size && std::getline(is, line); ++j) {
    ss = std::stringstream(line);
    i = 0;
    while (ss >> weight) {
      data.push_back(weight);
      ++i;
    }
    if (i != size)
      throw MatrixCalculationsException("Invalid matrix's line length.");
  }
  if (j != input_size) {
    throw MatrixCalculationsException("Input ended unexpectedly.");
  }
  matrix = Matrix<float>(data);
  matrix.set_rows(input_size);
  matrix.set_cols(size);
  return is;
}

template <typename Type>
void PrintShape(Matrix<Type> matrix) {
  std::cout << "Matrix Size([" << matrix.get_rows() << ", " << matrix.get_cols()
            << "])" << std::endl;
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
  std::normal_distribution<T> d(0, stdev);

  // fill each element w/ draw from distribution
  for (size_t r = 0; r < rows; ++r) {
    for (size_t c = 0; c < cols; ++c) {
      M(r, c) = d(gen);
    }
  }
  return M;
}
}  // namespace s21

#endif

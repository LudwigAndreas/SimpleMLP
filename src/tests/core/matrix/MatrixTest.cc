#include <gtest/gtest.h>

#include "core/exceptions/MatrixException.h"
#include "core/matrix/Matrix.h"

class MatrixTest : public ::testing::Test {
 protected:
  void SetUp() override {
    matrix1 = s21::Matrix<float>(3, 3);
    matrix2 = s21::Matrix<float>(3, 3);
    for (size_t i = 0; i < matrix1.get_rows(); ++i) {
      for (size_t j = 0; j < matrix1.get_cols(); ++j) {
        matrix1(i, j) = i * j;
        matrix2(i, j) = i + j;
      }
    }
  }

  void TearDown() override {}

  s21::Matrix<float> matrix1;
  s21::Matrix<float> matrix2;
};

TEST_F(MatrixTest, DefaultConstructor) {
  s21::Matrix<float> matrix;
  EXPECT_EQ(matrix.get_rows(), 0);
  EXPECT_EQ(matrix.get_cols(), 0);
  EXPECT_EQ(matrix.get_shape(), (std::tuple<size_t, size_t>(0, 0)));
  EXPECT_TRUE(matrix.get_data().empty());
}

TEST_F(MatrixTest, ConstructorWithDimensions) {
  size_t rows = 2;
  size_t cols = 3;
  s21::Matrix<float> matrix(rows, cols);
  EXPECT_EQ(matrix.get_rows(), rows);
  EXPECT_EQ(matrix.get_cols(), cols);
  EXPECT_EQ(matrix.get_shape(), (std::tuple<size_t, size_t>(rows, cols)));
  EXPECT_EQ(matrix.get_data().size(), rows * cols);
}

TEST_F(MatrixTest, ConstructorWithVector) {
  std::vector<float> vector = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f};
  s21::Matrix<float> matrix(vector);
  EXPECT_EQ(matrix.get_rows(), 1);
  EXPECT_EQ(matrix.get_cols(), vector.size());
  EXPECT_EQ(matrix.get_shape(), (std::tuple<size_t, size_t>(1, vector.size())));
  EXPECT_EQ(matrix.get_data().size(), vector.size());
  EXPECT_EQ(matrix(0, 0), vector[0]);
  EXPECT_EQ(matrix(0, 1), vector[1]);
  EXPECT_EQ(matrix(0, 2), vector[2]);
  EXPECT_EQ(matrix(0, 3), vector[3]);
  EXPECT_EQ(matrix(0, 4), vector[4]);
  EXPECT_EQ(matrix(0, 5), vector[5]);
}

TEST_F(MatrixTest, ConstructorWithVectorAndDimensions) {
  std::vector<float> vector = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f};
  size_t rows = 2;
  size_t cols = 3;
  s21::Matrix<float> matrix(vector, rows, cols);
  EXPECT_EQ(matrix.get_rows(), rows);
  EXPECT_EQ(matrix.get_cols(), cols);
  EXPECT_EQ(matrix.get_shape(), (std::tuple<size_t, size_t>(rows, cols)));
  EXPECT_EQ(matrix.get_data().size(), vector.size());
  EXPECT_EQ(matrix(0, 0), vector[0]);
  EXPECT_EQ(matrix(0, 1), vector[1]);
  EXPECT_EQ(matrix(0, 2), vector[2]);
  EXPECT_EQ(matrix(1, 0), vector[3]);
  EXPECT_EQ(matrix(1, 1), vector[4]);
  EXPECT_EQ(matrix(1, 2), vector[5]);
}

TEST_F(MatrixTest, AssignmentOperator) {
  s21::Matrix<float> matrix_copy;
  matrix_copy = matrix1;

  EXPECT_EQ(matrix1.get_rows(), matrix_copy.get_rows());
  EXPECT_EQ(matrix1.get_cols(), matrix_copy.get_cols());
  for (size_t i = 0; i < matrix1.get_rows(); ++i) {
    for (size_t j = 0; j < matrix1.get_cols(); ++j) {
      EXPECT_EQ(matrix1(i, j), matrix_copy(i, j));
    }
  }
}

// TODO: not sure what size setters should do with data. Should it resize it or
// not
TEST_F(MatrixTest, Setters) {
  s21::Matrix<float> matrix(matrix1);
  size_t rows = matrix.get_rows();
  size_t new_rows = 2;
  size_t new_cols = 3;
  matrix.set_cols(new_cols);
  EXPECT_EQ(matrix.get_rows(), rows);
  EXPECT_EQ(matrix.get_cols(), new_cols);
  EXPECT_EQ(matrix.get_shape(), (std::tuple<size_t, size_t>(rows, new_cols)));
  EXPECT_EQ(matrix.get_data(), matrix1.get_data());

  matrix.set_rows(new_rows);
  EXPECT_EQ(matrix.get_rows(), new_rows);
  EXPECT_EQ(matrix.get_cols(), new_cols);
  EXPECT_EQ(matrix.get_shape(),
            (std::tuple<size_t, size_t>(new_rows, new_cols)));
  EXPECT_EQ(matrix.get_data(), matrix1.get_data());

  matrix.set_shape(std::tuple<size_t, size_t>(1, new_rows * new_cols));
  EXPECT_EQ(matrix.get_rows(), 1);
  EXPECT_EQ(matrix.get_cols(), new_rows * new_cols);
  EXPECT_EQ(matrix.get_shape(),
            (std::tuple<size_t, size_t>(1, new_rows * new_cols)));
  EXPECT_EQ(matrix.get_data(), matrix1.get_data());

  matrix.set_data(matrix2.get_data());
  EXPECT_EQ(matrix.get_rows(), 1);
  EXPECT_EQ(matrix.get_cols(), new_rows * new_cols);
  EXPECT_EQ(matrix.get_shape(),
            (std::tuple<size_t, size_t>(1, new_rows * new_cols)));
  EXPECT_EQ(matrix.get_data(), matrix2.get_data());
}

TEST_F(MatrixTest, OperatorParentheses) {
  s21::Matrix<float> matrix =
      s21::Matrix<float>({1.f, 2.f, 3.f, 4.f, 5.f, 6.f}, 3, 2);
  EXPECT_EQ(matrix(0, 0), 1.f);
  EXPECT_EQ(matrix(0, 1), 2.f);
  EXPECT_EQ(matrix(1, 0), 3.f);
  EXPECT_EQ(matrix(1, 1), 4.f);
  EXPECT_EQ(matrix(2, 0), 5.f);
  EXPECT_EQ(matrix(2, 1), 6.f);
  EXPECT_THROW(matrix(matrix.get_rows(), matrix.get_cols() + 1) = 1.f,
               std::out_of_range);
  EXPECT_THROW(matrix(matrix.get_rows() + 1, matrix.get_cols()) = 1.f,
               std::out_of_range);
}

TEST_F(MatrixTest, OperatorBrackets) {
  s21::Matrix<float> matrix =
      s21::Matrix<float>({1.f, 2.f, 3.f, 4.f, 5.f, 6.f}, 3, 2);
  EXPECT_EQ(matrix[0], 1.f);
  EXPECT_EQ(matrix[1], 2.f);
  EXPECT_EQ(matrix[2], 3.f);
  EXPECT_EQ(matrix[3], 4.f);
  EXPECT_EQ(matrix[4], 5.f);
  EXPECT_EQ(matrix[5], 6.f);
  EXPECT_THROW(matrix[matrix.size()] = 21.f, std::out_of_range);
}

TEST_F(MatrixTest, ElementwiseMultiplicationMethod) {
  s21::Matrix<float> matrix({1.f, 0.f, 2.f, -1.f, -2.f, 0.f, -4.f, 2.f, 1.f,
                             0.f, 2.f, -1.f, 3.f, 0.f, 6.f, -3.f},
                            4, 4);
  EXPECT_THROW(matrix.ElementwiseMultiplication(matrix1),
               MatrixCalculationsException);
  EXPECT_THROW(matrix1.ElementwiseMultiplication(matrix),
               MatrixCalculationsException);
  s21::Matrix output(matrix1);
  for (size_t r = 0; r < output.get_rows(); ++r) {
    for (size_t c = 0; c < output.get_cols(); ++c) {
      output(r, c) = matrix1(r, c) * matrix2(r, c);
    }
  }
  EXPECT_EQ(matrix1.ElementwiseMultiplication(matrix2), output);
  EXPECT_EQ(matrix2.ElementwiseMultiplication(matrix1), output);
}

TEST_F(MatrixTest, MatmulMethod) {
  s21::Matrix<int> A({1, 2, 3, 4, 5, 6}, 2, 3);
  s21::Matrix<int> B({7, 8, 9, 10, 11, 12}, 3, 2);
  s21::Matrix<int> expected_result({58, 64, 139, 154}, 2, 2);
  EXPECT_EQ(A.MatrixMultiplication(B), expected_result);

  s21::Matrix<float> C({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f},
                       3, 3);
  s21::Matrix<float> D(
      {0.5f, 0.5f, 0.5f, 0.25f, 0.25f, 0.25f, 0.125f, 0.125f, 0.125f}, 3, 3);
  s21::Matrix<float> expected_result2(
      {1.375f, 1.375f, 1.375f, 4.f, 4.f, 4.f, 6.625f, 6.625f, 6.625f}, 3, 3);
  EXPECT_EQ(C.MatrixMultiplication(D), expected_result2);
  // TODO: throws error
}

TEST_F(MatrixTest, MatmulTransposedMethod) {
  s21::Matrix<int> A({1, 2, 3, 4, 5, 6}, 2, 3);
  s21::Matrix<int> B({7, 9, 11, 8, 10, 12}, 2, 3);
  s21::Matrix<int> expected_result({58, 64, 139, 154}, 2, 2);
  EXPECT_EQ(A.MatrixMultiplicationTransposed(B), expected_result);

  s21::Matrix<float> C({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f},
                       3, 3);
  s21::Matrix<float> D(
      {0.5f, 0.25f, 0.125f, 0.5f, 0.25f, 0.125f, 0.5f, 0.25f, 0.125f}, 3, 3);
  s21::Matrix<float> expected_result2(
      {1.375f, 1.375f, 1.375f, 4.f, 4.f, 4.f, 6.625f, 6.625f, 6.625f}, 3, 3);
  EXPECT_EQ(C.MatrixMultiplicationTransposed(D), expected_result2);
  // TODO: throws error
}
TEST_F(MatrixTest, SquareMethod) {
  s21::Matrix<int> A({1, 2, 3, 4, 5, 6}, 2, 3);
  s21::Matrix<int> expected_result({1, 4, 9, 16, 25, 36}, 2, 3);
  EXPECT_EQ(A.Square(), expected_result);

  s21::Matrix<float> C({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f},
                       3, 3);
  s21::Matrix<float> expected_result2(
      {1.0f, 4.0f, 9.0f, 16.f, 25.f, 36.f, 49.0f, 64.0f, 81.0f}, 3, 3);
  EXPECT_EQ(C.Square(), expected_result2);
}

TEST_F(MatrixTest, MultiplyScalarMethod) {
  s21::Matrix<int> A({1, 2, 3, 4, 5, 6}, 2, 3);
  s21::Matrix<int> expected_result({5, 10, 15, 20, 25, 30}, 2, 3);
  EXPECT_EQ(A.ScalarMultiplication(5), expected_result);

  s21::Matrix<float> C({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f},
                       3, 3);
  s21::Matrix<float> expected_result2(
      {5.0f, 10.0f, 15.0f, 20.f, 25.f, 30.f, 35.0f, 40.0f, 45.0f}, 3, 3);
  EXPECT_EQ(C.ScalarMultiplication(5), expected_result2);
  // TODO: throws error
}

TEST_F(MatrixTest, AdditionMethod) {
  s21::Matrix<int> A({1, 2, 3, 4, 5, 6}, 2, 3);
  s21::Matrix<int> B({7, 8, 9, 10, 11, 12}, 2, 3);
  s21::Matrix<int> expected_result({8, 10, 12, 14, 16, 18}, 2, 3);
  EXPECT_EQ(A.Add(B), expected_result);

  s21::Matrix<float> C({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f},
                       3, 3);
  s21::Matrix<float> D(
      {0.5f, 0.5f, 0.5f, 0.25f, 0.25f, 0.25f, 0.125f, 0.125f, 0.125f}, 3, 3);
  s21::Matrix<float> expected_result2(
      {1.5f, 2.5f, 3.5f, 4.25f, 5.25f, 6.25f, 7.125f, 8.125f, 9.125f}, 3, 3);
  EXPECT_EQ(C.Add(D), expected_result2);
  // TODO: throws error
}
// TODO: operator-() test
TEST_F(MatrixTest, InversionOperator) {
  s21::Matrix<int> A({1, 2, 3, 4, 5, 6}, 2, 3);
  s21::Matrix<int> expected_result({-1, -2, -3, -4, -5, -6}, 2, 3);
  EXPECT_EQ(-A, expected_result);

  s21::Matrix<float> C({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f},
                       3, 3);
  s21::Matrix<float> expected_result2(
      {-1.0f, -2.0f, -3.0f, -4.0f, -5.0f, -6.0f, -7.0f, -8.0f, -9.0f}, 3, 3);
  EXPECT_EQ(-C, expected_result2);
}
// TODO: operator+(Matrix) test
TEST_F(MatrixTest, AdditionOperator) {
  s21::Matrix<int> A({1, 2, 3, 4, 5, 6}, 2, 3);
  s21::Matrix<int> B({7, 8, 9, 10, 11, 12}, 2, 3);
  s21::Matrix<int> expected_result({8, 10, 12, 14, 16, 18}, 2, 3);
  EXPECT_EQ(A + B, expected_result);

  s21::Matrix<float> C({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f},
                       3, 3);
  s21::Matrix<float> D(
      {0.5f, 0.5f, 0.5f, 0.25f, 0.25f, 0.25f, 0.125f, 0.125f, 0.125f}, 3, 3);
  s21::Matrix<float> expected_result2(
      {1.5f, 2.5f, 3.5f, 4.25f, 5.25f, 6.25f, 7.125f, 8.125f, 9.125f}, 3, 3);
  EXPECT_EQ(C + D, expected_result2);
  // TODO: throws error
}
// TODO: operator-(Matrix) test
TEST_F(MatrixTest, SubstractionOperator) {
  s21::Matrix<int> A({1, 2, 3, 4, 5, 6}, 2, 3);
  s21::Matrix<int> B({7, 8, 9, 10, 11, 12}, 2, 3);
  s21::Matrix<int> expected_result({-6, -6, -6, -6, -6, -6}, 2, 3);
  EXPECT_EQ(A - B, expected_result);

  s21::Matrix<float> C({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f},
                       3, 3);
  s21::Matrix<float> D(
      {0.5f, 0.5f, 0.5f, 0.25f, 0.25f, 0.25f, 0.125f, 0.125f, 0.125f}, 3, 3);
  s21::Matrix<float> expected_result2(
      {0.5f, 1.5f, 2.5f, 3.75f, 4.75f, 5.75f, 6.875f, 7.875f, 8.875f}, 3, 3);
  EXPECT_EQ(C - D, expected_result2);
  // TODO: throws error
}
// TODO: transpose test
TEST_F(MatrixTest, TransposingOperator) {
  s21::Matrix<int> A({1, 2, 3, 4, 5, 6}, 2, 3);
  s21::Matrix<int> expected_result({1, 4, 2, 5, 3, 6}, 3, 2);
  EXPECT_EQ(A.Transpose(), expected_result);

  s21::Matrix<float> C({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f},
                       3, 3);
  s21::Matrix<float> expected_result2(
      {1.0f, 4.0f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f}, 3, 3);
  EXPECT_EQ(C.Transpose(), expected_result2);
  // TODO: throws error
}
// TODO: ApplyFunction test
TEST_F(MatrixTest, ApplyFunctionMethod) {
  s21::Matrix<int> A({1, 2, 3, 4, 5, 6}, 2, 3);
  s21::Matrix<int> expected_result({0, 1, 0, 1, 0, 1}, 2, 3);
  EXPECT_EQ(A.ApplyFunction([](const int &n) -> int { return n % 2 == 0; }),
            expected_result);

  s21::Matrix<float> C({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f},
                       3, 3);
  s21::Matrix<float> expected_result2(
      {0.0f, 1.0f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f}, 3, 3);
  EXPECT_EQ(
      C.ApplyFunction([](const float &n) -> float { return (int)n % 2 == 0; }),
      expected_result2);
}
// TODO: ToVector test
TEST_F(MatrixTest, ToVectorMethod) {
  s21::Matrix<int> A({1, 2, 3, 4, 5, 6}, 2, 3);
  std::vector<int> expected_result = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(A.ToVector(), expected_result);

  s21::Matrix<float> C({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f},
                       3, 3);
  std::vector<float> expected_result2 = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
                                         6.0f, 7.0f, 8.0f, 9.0f};
  EXPECT_EQ(C.ToVector(), expected_result2);
}
// TODO: operator<< test
TEST_F(MatrixTest, OuputOperator) {}
// TODO: operator>> test
TEST_F(MatrixTest, InputOperator) {}
// TODO: PrintShape test
TEST_F(MatrixTest, PrintShapeMethod) {}

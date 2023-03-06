#include <gtest/gtest.h>

#include "src/core/matrix/Matrix.hpp"
#include "src/core/exceptions/MatrixException.hpp"

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

	void TearDown() override {

	}

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
	int rows = 2;
	int cols = 3;
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
	int rows = 2;
	int cols = 3;
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
	for(size_t i = 0; i < matrix1.get_rows(); ++i) {
		for(size_t j = 0; j < matrix1.get_cols(); ++j) {
			EXPECT_EQ(matrix1(i, j), matrix_copy(i, j));
		}
	}
}

//TODO: not sure what size setters should do with data. Should it resize it or not
TEST_F(MatrixTest, Setters) {
	s21::Matrix<float> matrix(matrix1);
	int rows = matrix.get_rows();
	int new_rows = 2;
	int new_cols = 3;
	matrix.set_cols(new_cols);
	EXPECT_EQ(matrix.get_rows(), rows);
	EXPECT_EQ(matrix.get_cols(), new_cols);
	EXPECT_EQ(matrix.get_shape(), (std::tuple<size_t, size_t>(rows, new_cols)));
	EXPECT_EQ(matrix.get_data(), matrix1.get_data());

	matrix.set_rows(new_rows);
	EXPECT_EQ(matrix.get_rows(), new_rows);
	EXPECT_EQ(matrix.get_cols(), new_cols);
	EXPECT_EQ(matrix.get_shape(), (std::tuple<size_t, size_t>(new_rows, new_cols)));
	EXPECT_EQ(matrix.get_data(), matrix1.get_data());

	matrix.set_shape(std::tuple<size_t, size_t>(1, new_rows * new_cols));
	EXPECT_EQ(matrix.get_rows(), 1);
	EXPECT_EQ(matrix.get_cols(), new_rows * new_cols);
	EXPECT_EQ(matrix.get_shape(), (std::tuple<size_t, size_t>(1, new_rows * new_cols)));
	EXPECT_EQ(matrix.get_data(), matrix1.get_data());

	matrix.set_data(matrix2.get_data());
	EXPECT_EQ(matrix.get_rows(), 1);
	EXPECT_EQ(matrix.get_cols(), new_rows * new_cols);
	EXPECT_EQ(matrix.get_shape(), (std::tuple<size_t, size_t>(1, new_rows * new_cols)));
	EXPECT_EQ(matrix.get_data(), matrix2.get_data());
}

TEST_F(MatrixTest, OperatorParentheses) {
	s21::Matrix<float> matrix = s21::Matrix<float>({1.f, 2.f,
													3.f, 4.f,
													5.f, 6.f},
												   3, 2);
	EXPECT_EQ(matrix(0,0), 1.f);
	EXPECT_EQ(matrix(0,1), 2.f);
	EXPECT_EQ(matrix(1,0), 3.f);
	EXPECT_EQ(matrix(1,1), 4.f);
	EXPECT_EQ(matrix(2,0), 5.f);
	EXPECT_EQ(matrix(2,1), 6.f);
	EXPECT_THROW(matrix(matrix.get_rows(), matrix.get_cols() + 1)
							= 1.f, std::out_of_range);
	EXPECT_THROW(matrix(matrix.get_rows() + 1, matrix.get_cols())
						 = 1.f, std::out_of_range);

}

TEST_F(MatrixTest, OperatorBrackets) {
	s21::Matrix<float> matrix = s21::Matrix<float>({1.f, 2.f,
													3.f, 4.f,
													5.f, 6.f},
												   3, 2);
	EXPECT_EQ(matrix[0], 1.f);
	EXPECT_EQ(matrix[1], 2.f);
	EXPECT_EQ(matrix[2], 3.f);
	EXPECT_EQ(matrix[3], 4.f);
	EXPECT_EQ(matrix[4], 5.f);
	EXPECT_EQ(matrix[5], 6.f);
	EXPECT_THROW(matrix[matrix.size() + 1] = 21.f, std::out_of_range);
}

TEST_F(MatrixTest, MultiplyElementwiseMethod) {
	s21::Matrix<float> matrix({1.f, 0.f, 2.f, -1.f,
							   -2.f, 0.f, -4.f, 2.f,
							   1.f, 0.f, 2.f, -1.f,
							   3.f, 0.f, 6.f, -3.f},
							  4, 4);
	EXPECT_THROW(matrix.multiply_elementwise(matrix1), MatrixCalculationsException);
	EXPECT_THROW(matrix1.multiply_elementwise(matrix), MatrixCalculationsException);
	s21::Matrix output(matrix1);
	for (size_t r = 0; r < output.get_rows(); ++r) {
		for (size_t c = 0; c < output.get_cols(); ++c) {
			output(r, c) = matrix1(r, c) * matrix2(r, c);
		}
	}
	EXPECT_EQ(matrix1.multiply_elementwise(matrix2), output);
	EXPECT_EQ(matrix2.multiply_elementwise(matrix1), output);
}

//TODO: matmul test
//TODO: matmulTransposed test
//TODO: square test
//TODO: multiply_scalar test
//TODO: add test
//TODO: operator-() test
//TODO: operator+(Matrix) test
//TODO: operator-(Matrix) test
//TODO: transpose test
//TODO: apply_function test
//TODO: ToVector test
//TODO: operator<< test
//TODO: operator>> test
//TODO: PrintShape test
//TODO: GenerateNDMatrix test






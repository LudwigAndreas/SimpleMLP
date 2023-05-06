#include <gtest/gtest.h>

#include "core/graph/MLPGraphModel.h"
#include "core/matrix/MLPMatrixModel.h"
#include "core/utils/MLPSerializer.h"

class MLPMatrixGraphModelTest : public ::testing::Test {
protected:
	void SetUp() override {
  }
	void TearDown() override {

	}

};

TEST(MLPMatrixGraphModelTest, size) {
  s21::MLPMatrixModel *matrix_model = s21::MLPSerializer::DeserializeMLPModel();
}

TEST(MLPMatrixGraphModelTest, Forward) {
  
  auto layers = model.get_layers();
  auto input = Matrix<float>({1, 0});
  auto result = model.Forward(input);


  ASSERT_FLOAT_EQ(result[0], 0);
}


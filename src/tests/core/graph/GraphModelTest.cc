#include <gtest/gtest.h>

#include "core/graph/MLPGraphModel.h"

class MLPGraphModelTest : public ::testing::Test {
protected:
	void SetUp() override {
		model = s21::MLPGraphModel(
      {2, 3, 1},
			s21::ActivationFunction(s21::ActivationFunction::Flags::Linear));

  }

	void TearDown() override {

	}

	s21::MLPGraphModel model;
};

TEST(MLPGraphModelTest, size) {
  auto layers = model.get_layers();
  ASSERT_EQ(*layers[0].size(), 2);
  ASSERT_EQ(*layers[1].size(), 3);
  ASSERT_EQ(*layers[2].size(), 1);
}

TEST(MLPGraphModelTest, Forward) {
  auto layers = model.get_layers();
  auto input = Matrix<float>({1, 0});
  auto result = model.Forward(input);


  ASSERT_FLOAT_EQ(result[0], 0);
}


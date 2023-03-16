#include <gtest/gtest.h>

#include "src/core/utils/BMPReader.hpp"

#include <gtest/gtest.h>
#include <fstream>
#include <iostream>

class BMPReaderTest : public ::testing::Test {
protected:
	// Initialize the input file and expected output
	void SetUp() override {
		// Create a BMP file with a 2x2 pixel image
		std::ofstream bmp_file("test.bmp", std::ios::binary);
		unsigned char bmp_header[] = { 'B', 'M', 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00 };
		unsigned char bmp_data[] = { 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00 };
		bmp_file.write((char *) bmp_header, sizeof(bmp_header));
		bmp_file.write((char *) bmp_data, sizeof(bmp_data));
		bmp_file.close();

		// Set the expected output for the test case
		expected_output = new unsigned char[6];
		expected_output[0] = 0xFF;
		expected_output[1] = 0xFF;
		expected_output[2] = 0x00;
		expected_output[3] = 0xFF;
		expected_output[4] = 0xFF;
		expected_output[5] = 0x00;
	}

	// Clean up the input file and expected output
	void TearDown() override {
		std::remove("test.bmp");
		delete[] expected_output;
	}

	// Declare variables to hold the input file and expected output
	const char* input_file = "test.bmp";
	unsigned char* expected_output;
};


TEST_F(BMPReaderTest, readAndResizeBMPFunction) {
	const char* filename = "test1.bmp";
	int new_width = 100;
	int new_height = 100;

	// Call the function being tested
	unsigned char* result = ReadAndResizeBMP(filename, new_width, new_height);

	// Check the output against expected results
	ASSERT_NE(result, nullptr);
	// Check the dimensions of the resized BMP
	// You can use a library like EasyBMP to read the BMP header
	// and get the width and height of the BMP
	// Then, compare these values with the expected width and height
	// of the resized BMP
}

TEST_F(BMPReaderTest, BMPDataToGrayscaleFunction) {

}

TEST_F(BMPReaderTest, VectorToBMPFunction) {

}

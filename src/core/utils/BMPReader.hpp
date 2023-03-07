#ifndef SIMPLEMLP_BMPREADER_HPP
#define SIMPLEMLP_BMPREADER_HPP

#include <iostream>
#include <fstream>
#include <vector>

// Структура для хранения заголовка BMP файла
struct BMPHeader {
	uint16_t magicNumber;
	uint32_t size;
	uint32_t reserved;
	uint32_t offset;
};

unsigned char *readAndResizeBMP(const char* filename,
											int new_width, int new_height);

std::vector<float> bmp_to_grayscale(const unsigned char* bmp_data,
									int width, int height, int channels);

void vectorToBMP(const std::vector<float>& vec, const std::string& filename,
				 int width, int height);

#endif //SIMPLEMLP_BMPREADER_HPP

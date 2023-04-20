#ifndef SIMPLEMLP_BMPREADER_HPP
#define SIMPLEMLP_BMPREADER_HPP

#include <iostream>
#include <fstream>
#include <vector>

unsigned char *ReadAndResizeBMP(const char* filename,
								int new_width, int new_height);

std::vector<float> BMPDataToGrayscale(const unsigned char* bmp_data,
									  int width, int height, int channels);

#endif //SIMPLEMLP_BMPREADER_HPP

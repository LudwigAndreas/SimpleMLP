#include "BMPReader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../lib/stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../../lib/stb_image_resize.h"

std::vector<float> BMPDataToGrayscale(const unsigned char* bmp_data,
									  int width, int height, int channels) {

	std::vector<float> grayscale_data(width * height);
	float min = 255, max = 0;
	for (int i = 0; i < width * height; i++) {
		int r = bmp_data[i * channels];
		int g = bmp_data[i * channels + 1];
		int b = bmp_data[i * channels + 2];
		grayscale_data[i] = static_cast<float>(0.2126 * r + 0.7152 * g + 0.0722 * b);
		if (grayscale_data[i] > max)
			max = grayscale_data[i];
		if (grayscale_data[i] < min)
			min = grayscale_data[i];
	}
	max = max - (max - min) / 20;
	min = min + (max - min) / 20;
	for (auto &i : grayscale_data)
		i = (float) std::min(255., std::max(0., (i - min) * (1. / (max - min))));
	return grayscale_data;
}

unsigned char *ReadAndResizeBMP(const char* filename,
								int new_width, int new_height) {
	int channels_in_file;
	int width_in_file;
	int height_in_file;

	// Load the BMP file using stb_image library
	unsigned char* data = stbi_load(filename, &width_in_file, &height_in_file, &channels_in_file, 0);

	if (!data) {
//		TODO throw an error
		std::cerr << "Error loading file " << filename << std::endl;
		return {};
	}

	// Resize the image using stb_image_resize library
	int channels = 3;  // convert to RGB format
	auto* resized_data = new unsigned char[new_width * new_height * channels];
	stbir_resize_uint8(data, width_in_file, height_in_file, 0, resized_data, new_width, new_height, 0, channels);

	// Free the memory used by stb_image and stb_image_resize libraries
	stbi_image_free(data);

	return resized_data;
}

// Функция для конвертации вектора обратно в BMP изображение
void VectorToBMP(const std::vector<float>& vec, const std::string& filename,
				 int width, int height) {
//	stbi_write_bmp("result.bmp", 271, 271, 3, result.data());
}
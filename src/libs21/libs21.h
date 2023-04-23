#ifndef SIMPLEMLP_LIBFT_H
#define SIMPLEMLP_LIBFT_H

#include <string>
#include <vector>
#include <algorithm>

namespace s21 {
    std::string to_lower_case(std::string str);

    std::string to_upper_case(std::string str);

    std::vector <std::string> split(std::string s, std::string delimiter);

    unsigned char* load_bmp(const char* filename, int* width, int* height, int* channels);

    void resize_bmp_data(unsigned char *original_data, int width_px, int height_px, unsigned char *resized_data, int new_width, int new_height, int num_channels);

    std::vector<float> bmp_data_to_grayscale(const unsigned char* bmp_data,
                                             int width, int height, int channels);
}

#endif //SIMPLEMLP_LIBFT_H

#ifndef SIMPLEMLP_LIBFT_H
#define SIMPLEMLP_LIBFT_H

#include <string>
#include <vector>
namespace s21 {
    std::string to_lower_case(std::string str);

    std::string to_upper_case(std::string str);

    std::vector <std::string> split(std::string s, std::string delimiter);

    unsigned char* load_bmp(const char* filename, int* width, int* height, int* channels);
}

#endif //SIMPLEMLP_LIBFT_H

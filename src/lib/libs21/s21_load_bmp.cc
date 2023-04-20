#include <fstream>
#include <iostream>
#include <cstdint>
#include <cstring>

namespace s21 {

    unsigned char* load_bmp(const char* filename, int* width, int* height, int* channels) {
        std::ifstream infile(filename, std::ios::binary);
        if (!infile) {
            return nullptr;
        }

        char header[54];
        infile.read(header, 54);

        if (header[0] != 'B' || header[1] != 'M') {
            return nullptr;
        }

        int file_size = *(int32_t*)&header[2];
        int data_offset = *(int32_t*)&header[10];
        int width_px = *(int32_t*)&header[18];
        int height_px = *(int32_t*)&header[22];
        int num_channels = *(int16_t*)&header[28] / 8;

        if (num_channels != 3 && num_channels != 4) {
            return nullptr;
        }

        int row_size_bytes = (num_channels * width_px + 3) & (~3);
        int padding_bytes = row_size_bytes - num_channels * width_px;
        int image_size_bytes = row_size_bytes * height_px;

        unsigned char* data = new unsigned char[image_size_bytes];

        infile.seekg(data_offset);
        char arr[3];
        for (int y = 0; y < height_px; ++y) {
            for (int x = 0; x < width_px; ++x) {
                infile.read((char*)&data[(height_px - y - 1) * num_channels * width_px + num_channels * x], num_channels);
            }
            infile.read(arr, padding_bytes);
        }

        *width = width_px;
        *height = height_px;
        *channels = num_channels;

        return data;
    }
}
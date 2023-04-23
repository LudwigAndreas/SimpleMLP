#include <fstream>
#include <iostream>
#include <cstdint>
#include <cstring>
#include <vector>

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

    std::vector<float> bmp_data_to_grayscale(const unsigned char* bmp_data,
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
}


#include "DatasetReading.hpp"
#include "exceptions/UploadFileException.h"
#include "libs21/include/libs21.h"

std::vector<s21::Sample> ReadDataset(std::string filename)
{
	std::vector<s21::Sample>	samples;
	std::fstream				file;
	std::string					str;

	file.open(filename, std::ofstream::in);
    if (!file.is_open()) {
        throw UploadFileException("Error opening dataset file");
    }
	while (file >> str) {
		std::vector<std::string> letter = s21::split(str, ",");
		std::vector<float> pixels;
		std::vector<float> answer(26, 0);
		answer[std::atoi(letter[0].data()) - 1] = 1;

		for (auto it = letter.begin() + 1; it < letter.end(); ++it)
		 	pixels.push_back(((float)std::atoi((*it).data())) / 255);
		s21::Sample s(pixels, s21::Matrix<float>(answer));

		samples.push_back(s);
	}
	file.close();
	return samples;
}

std::map<int, char> readSymbolMapping(const std::string &filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        throw UploadFileException("Error opening symbol mapping file");
    }

    std::map<int, char> symbolTable;

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int index;
        iss >> index;

        int asciiCode;
        while (iss >> asciiCode) {
            char symbol = static_cast<char>(asciiCode);
            symbolTable[index] = symbol;
        }
    }

    inputFile.close();
    return symbolTable;
}
#include "DatasetReading.hpp"

std::vector<std::string> split (std::string s, std::string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;

	while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
		token = s.substr (pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back (token);
	}

	res.push_back (s.substr (pos_start));
	return res;
}

std::vector<s21::Sample> ReadDataset(std::string filename)
{
	std::vector<s21::Sample>	samples;
	std::fstream				file;
	std::string					str;

//	samples.reserve(88800);
	file.open(filename, std::ofstream::in);
	// file.open("datasets/emnist-letters-train.csv", std::ofstream::in);
	while (file >> str) {
		std::vector<std::string> letter = split(str, ",");
		std::vector<float> pixels;
		std::vector<float> answer(26, 0);
		answer[std::atoi(letter[0].data()) - 1] = 1;

		for (auto it = letter.begin() + 1; it < letter.end(); ++it)
//			pixels.push_back(std::atoi((*it).data()));
		 	pixels.push_back(((float)std::atoi((*it).data())) / 255);
		s21::Sample s(pixels, s21::Matrix<float>(answer));

		samples.push_back(s);
	}
	file.close();
	std::cerr << "Dataset loaded! " << samples.size() << " samples." << std::endl;
	return samples;
}

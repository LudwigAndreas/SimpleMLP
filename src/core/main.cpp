#include <functional>
#include <random>
#include <vector>
#include <cmath>
#include <chrono>
#include <cassert>
#include <iostream>
#include <tuple>
#include <fstream>
#include <sstream>
#include <string>

#include "LetterRecognitionMlpModelBuilder.hpp"
#include "matrix/MLPMatrixModel.hpp"
#include "graph/MLPGraphModel.hpp"
#include "utils/MLPSerializer.hpp"
// void log(std::fstream &file, const float &x, const s21::Matrix<float> &y, const std::vector<float> &y_hat){
// 	auto correct_guess = SearchMaxIndex(y.ToVector());
// 	auto mse = (y(correct_guess, 0) - y_hat[correct_guess]);
// 	mse = mse*mse;

// 	file << ((correct_guess == SearchMaxIndex(y_hat)) ? "✅" : "❌") << ' '
// 		 << char('A' + correct_guess) << " "
// 		 << char('A' + SearchMaxIndex(y_hat)) << ' ' 
// 		 << y_hat[SearchMaxIndex(y_hat)] * 100 << "%\t"
// 		 << mse << std::endl;
// }
#include "DatasetReading.hpp"

void	SaveModel(s21::IMLPModel<float> *model, int iteration) {
	std::stringstream	ss;

	ss << "testmodel" << iteration << ".mlpmodel";
	s21::MLPSerializer<float>::SerializeMLPMatrixModel((s21::MLPMatrixModel *)(model), ss.str());
}

float CrossValidation(s21::IMLPModel<float> *model, s21::Dataset dataset, bool silent_mode = false) {
	float training_accuracy;
	float testing_accuracy;
	int trained_on;
	for (int i = 0; i < (int) dataset.size(); ++i) {
		// SaveModel(model, i);
		training_accuracy = 0;
		trained_on = 0;
		for (int j = 0; j < (int) dataset.size(); ++j) {
			std::cerr << "\rEpoch #" << i << ", " << trained_on << '/' << dataset.size() - 1 << " groups trained on. ";
			if (j)
				std::cerr << "Current accuracy: " << (training_accuracy * 100) / ((float) trained_on) << '%';
			if (j != dataset.current_iteration && ++trained_on)
				training_accuracy += model->Train(dataset[j], true);
			
		}
		std::cerr << "\rEpoch #" << i + 1 << ", " << trained_on << '/' << dataset.size() << " groups trained on.\n";
		std::cerr << "Train: " << (training_accuracy * 100) / ((float) trained_on) << "% accuracy" << std::endl;
		testing_accuracy = model->Test(dataset[dataset.current_iteration], true);
		std::cerr << "Test:  " << testing_accuracy * 100 << "% accuracy" << std::endl;
		++dataset.current_iteration;
	}
	return testing_accuracy;
}

// #include "utils/BMPReader.hpp"
// int main(int argc, char **argv) {
// 	std::string filename = "image.bmp";

// 	if (argc > 1)
// 		filename = argv[1];
// 	std::vector<float> image;
// 	std::vector<float> letter {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,20,27,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,33,84,169,190,126,33,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,47,190,233,251,253,244,163,33,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,20,67,175,247,254,254,254,254,244,127,10,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,45,122,231,253,254,255,255,254,251,175,34,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,114,203,254,254,254,253,254,254,254,243,113,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,22,145,222,254,253,228,218,242,254,254,243,113,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,110,232,249,253,219,126,213,246,254,252,177,34,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,21,172,252,254,232,98,91,233,252,254,245,115,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,32,203,254,254,209,54,118,245,254,254,232,82,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,37,217,254,250,142,77,188,252,254,252,172,22,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,37,214,232,207,111,177,250,254,254,250,130,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,20,138,93,51,119,243,254,255,255,252,173,22,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,15,6,4,93,236,254,254,254,254,232,100,32,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,53,165,215,222,233,251,253,232,152,75,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,18,81,125,140,173,232,253,250,170,81,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,4,9,22,100,230,250,188,108,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,20,111,190,243,218,77,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,115,242,243,112,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,33,160,188,51,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,92,145,50,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,33,106,106,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,42,112,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,24,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
// 	// BMPReader(filename.c_str(), image);
// //	std::cout << image.size() << std::endl;
// //	std::for_each(image.begin(), image.end(), [](float &n) { n *= (int) 255; n = (int) n; });
// //	s21::Matrix<float> image_matrix(image, 28, 28);
// //	std::cout << image_matrix << std::endl;

// 	vectorToBMP(image, std::string("out.bmp"), 28, 28);
// }

int main() {
	// s21::LetterRecognitionMLPModelBuilder *builder = new s21::LetterRecognitionMLPModelBuilder();
	// s21::IMLPModel<float>		*model = builder
	// 		->HiddenLayers(2)
	// 		->ActivationFunc(s21::ActivationFunction::Sigmoid)
	// 		->LearningRate(0.1f, false)
	// 		->HiddenUnitsPerLayer(400)
	// 		->GetResult();
	std::vector<s21::Sample>	samples;
	// std::chrono::time_point<std::chrono::system_clock> start, end;
	auto model = new s21::MLPGraphModel({784, 100, 100, 26},
				s21::ActivationFunction::getFunctionByFlag(s21::ActivationFunction::Flags::Sigmoid),
				true, 0.1);
	// s21::MLPSerializer<float>::DeserializeMLPMatrixModel((s21::MLPMatrixModel *)model, "testmodel.mlpmodel");


	// s21::Dataset dataset(ReadDataset("datasets/emnist-letters-test.csv"), 16);
	s21::Dataset dataset(ReadDataset("../../datasets/emnist-letters-train.csv"), 4);
	// s21::Dataset dataset(samples, 32);
	// std::cerr << "Dataset split on " << dataset.size() << " with " << dataset[0].size() << " samples in each." << std::endl;
	CrossValidation(model, dataset);

	model->TestOutput(ReadDataset("../../datasets/emnist-letters-test.csv"), false, "test.output");
	// CrossValidation(model, dataset);
	// s21::MLPSerializer<float>::SerializeMLPMatrixModel((s21::MLPMatrixModel *)(model), "testmodel.mlpmodel");
	// std::cout << "\nAccuracy: " << ((float)corr / i) * 100 << '%' << std::endl;
}

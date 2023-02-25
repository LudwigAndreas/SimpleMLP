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
#include "matrix/MLPMatrixModelv2.hpp"
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
	s21::MLPSerializer<float>::SerializeMLPMatrixModel((s21::MLPMatrixModelv2 *)(model), ss.str());
}

float CrossValidation(s21::IMLPModel<float> *model, s21::Dataset dataset, bool silent_mode = false) {
	float training_accuracy;
	float testing_accuracy;
	int trained_on;
	for (int i = 0; i < dataset.size(); ++i) {
		SaveModel(model, i);
		training_accuracy = 0;
		trained_on = 0;
		for (int j = 0; j < dataset.size(); ++j) {
			std::cerr << "\rEpoch #" << i << ", " << trained_on << '/' << dataset.size() - 1 << " groups trained on. ";
			if (j)
				std::cerr << "Current accuracy: " << (training_accuracy * 100) / (trained_on) << '%'; 
			if (j != dataset.current_iteration && ++trained_on)
				training_accuracy += model->Train(dataset[j], true);
			
		}
		std::cerr << "\rEpoch #" << i + 1 << ", " << trained_on << '/' << dataset.size() << " groups trained on.\n";
		std::cerr << "Train: " << (training_accuracy * 100) / (trained_on) << "% accuracy" << std::endl;
		testing_accuracy = model->Test(dataset[dataset.current_iteration], true);
		std::cerr << "Test:  " << testing_accuracy * 100 << "% accuracy" << std::endl;
		++dataset.current_iteration;
	}
	return testing_accuracy;
}

//int main()
//{
////    s21::Matrix<float> first = s21::GenerateNDMatrix<float>(100, 150),
////                        second = s21::GenerateNDMatrix<float>(150, 200),
//    s21::Matrix<float> first = s21::GenerateNDMatrix<float>(2, 4),
//                        second = s21::GenerateNDMatrix<float>(4, 3),
//                        correct = first.matmul(second),
//                       test = first.matmul727(second);
//
//    std::cout << correct << test;
////
////    std::vector<float> f{1, 2, 3}, s{1, 5, 9};
////    std::cout << std::inner_product(f.begin(), f.end(),
////                                    s.begin(), 0);
//}

int main() {
	s21::LetterRecognitionMLPModelBuilder *builder = new s21::LetterRecognitionMLPModelBuilder();
	s21::IMLPModel<float>		*model = builder
			->HiddenLayers(2)
			->ActivationFunc(s21::ActivationFunction::Sigmoid)
			->LearningRate(0.1f, false)
			->HiddenUnitsPerLayer(100)
			->GetResult();
	std::vector<s21::Sample>	samples;
	// std::chrono::time_point<std::chrono::system_clock> start, end;
	// auto model = s21::MLPMatrixModelv2::MakeModel(0, 0, 0, 0, 0);
	// s21::MLPSerializer<float>::DeserializeMLPMatrixModel((s21::MLPMatrixModelv2 *)model, "testmodel.mlpmodel");


	// s21::Dataset dataset(ReadDataset("datasets/emnist-letters-test.csv"), 16);
	s21::Dataset dataset(ReadDataset("/home/landreas/42Course/SimpleMLP/datasets/emnist-letters-train.csv"), 4);
	// s21::Dataset dataset(samples, 32);
	// std::cerr << "Dataset split on " << dataset.size() << " with " << dataset[0].size() << " samples in each." << std::endl;
	CrossValidation(model, dataset);

	model->TestOutput(ReadDataset("/home/landreas/42Course/SimpleMLP/datasets/emnist-letters-test.csv"), false, "test.output");
	// CrossValidation(model, dataset);
	s21::MLPSerializer<float>::SerializeMLPMatrixModel((s21::MLPMatrixModelv2 *)(model), "testmodel.mlpmodel");
	// std::cout << "\nAccuracy: " << ((float)corr / i) * 100 << '%' << std::endl;
}

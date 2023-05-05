#include "core/utils/MLPSerializer.h"
#include "core/utils/IMLPModel.h"
#include "core/DatasetReading.h"
#include <chrono>

// argv[1] = model
// argv[2] = testing_dataset
int main(int argc, char **argv){
	if (argc < 2)
		return 1;
	s21::IMLPModel *model = s21::MLPSerializer<float>::DeserializeMLPModel(argv[1]);
	s21::Dataset dataset(ReadDataset(argv[2]), 1);
	int size = (int) dataset[0].size();
	std::chrono::time_point<std::chrono::system_clock> start, end;
	for (int i = 10; i <= 1000; i *= 10){
		start = std::chrono::system_clock::now();
		for (int j = 0; j < i; ++j) {
			
			for (int k = 0; k < size; ++k) {
				int expected = model->getMostProbablePrediction(dataset[0][k].y.ToVector());
				int got = model->Predict(dataset[0][k].x);
			}

		}
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		std::cout << "For " << i << " iterations | elapsed time: " << elapsed_seconds.count() << "s\t | average time: " << elapsed_seconds.count() / i << "s\n";
	}
	return 0;
}
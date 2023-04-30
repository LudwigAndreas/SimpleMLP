#include "ModelTrainWorker.hpp"

#include "src/core/DatasetReading.hpp"
#include "src/core/exceptions/ModelProcessingException.hpp"

#include <list>

ModelTrainWorker::ModelTrainWorker() {}

void ModelTrainWorker::process() {
	// try {
		s21::Dataset dataset(ReadDataset(dataset_file_name), num_of_epochs);
		for (size_t i = 0; i < dataset.size(); ++i) {
			int correct_guesses = 0;

			for (size_t j = 0; j < dataset.size(); ++j) {
				if (this->stop)
					return;
				if (j != (size_t) dataset.current_iteration || dataset.size() == 1) {
					correct_guesses = 0;
					for (int k = 0; k < (int) dataset[j].size(); ++k) {
						if (this->stop)
							return;

						if (model->Predict(dataset[j][k].x) == model->getMostProbablePrediction(dataset[j][k].y.ToVector()))
							++correct_guesses;
						else
							model->Backward(dataset[j][k].y);
					}
				}
				emit statusChanged(i + 1,
								   ((float) i * dataset.size() + j + 1)
								   / (dataset.size() * dataset.size()) * 100,
								   ((float)correct_guesses * 100) / dataset[j].size());

			}
			emit MeanErrorCalculated(i + 1, this->CalculateMSE(dataset[dataset.current_iteration % dataset.size()]));
			SaveModel(model, i);
			++dataset.current_iteration;
		}
		return;
	// } catch (std::exception &e) {
		// throw ModelProcessingException("Data processing error");
	// }
}

float ModelTrainWorker::CalculateMSE(s21::DatasetGroup &batch) {
	float mse = 0;
	float tmp;
	for (size_t i = 0; i < batch.size(); ++i) {
		tmp = 0;
		auto prediction = model->Forward(batch[i].x);
		for (size_t j = 0; j < prediction.size(); ++j) {
			tmp += std::pow(prediction[j] - batch[i].x[j], 2);
		}
		tmp /= prediction.size();
		mse += tmp;
	}
	mse /= batch.size();
	return mse;
}


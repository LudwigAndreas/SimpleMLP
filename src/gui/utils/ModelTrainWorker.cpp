#include "ModelTrainWorker.hpp"

#include "src/core/DatasetReading.hpp"
#include "src/core/exceptions/ModelProcessingException.hpp"

void ModelTrainWorker::process() {
	try {
		s21::Dataset dataset(ReadDataset(dataset_file_name), num_of_epochs);
		//TODO confusion matrix
		for (size_t i = 0; i < dataset.size(); ++i) {
			float training_accuracy = 0;
			int trained_on = 0;

			for (size_t j = 0; j < dataset.size(); ++j) {
				if (this->stop)
					return;
				if (j != (size_t) dataset.current_iteration && ++trained_on) {
					training_accuracy += model->Train(dataset[j], true);
				}
				emit statusChanged(i + 1,
								   ((float) i * dataset.size() + j + 1)
								   / (dataset.size() * dataset.size()) * 100,
								   (training_accuracy * 100) / (trained_on));

			}
			SaveModel(model, i);
			++dataset.current_iteration;
		}
	} catch (std::exception &e) {
		throw ModelProcessingException("Data processing error");
	}
}

//void MTWorker::stop() {
//	return;
//}


#include <QDebug>
#include "sstream"

#include "src/core/DatasetReading.hpp"
#include "src/core/utils/MLPSerializer.hpp"
#include "MTWorker.hpp"



MTWorker::MTWorker() {
	this->num_of_epochs = 5;
	this->stop = false;
}

MTWorker::~MTWorker() {

}

void MTWorker::setModel(s21::IMLPModel<float> *model) {
	this->model = model;
}

void MTWorker::setDatasetFileName(std::string file_name) {
	this->dataset_file_name = file_name;
}

void	SaveModel(s21::IMLPModel<float> *model, int iteration) {
	std::stringstream	ss;

	ss << "testmodel" << iteration << ".mlpmodel";
	s21::MLPSerializer<float>::SerializeMLPMatrixModel((s21::MLPMatrixModel *)(model), ss.str());
}

void MTWorker::setNumOfEpochs(int num) {
	this->num_of_epochs = num;
}

void MTWorker::stopTraining() {
	stop = true;
}


void MTWorker::process() {
	try {
		s21::Dataset dataset(ReadDataset(dataset_file_name), num_of_epochs);
		//TODO confusion matrix
		for (size_t i = 0; i < dataset.size(); ++i) {
			float training_accuracy = 0;
			float testing_accuracy = 0;
			int trained_on = 0;

			for (size_t j = 0; j < dataset.size(); ++j) {
				if (this->stop)
					return;
				std::cerr << "\rEpoch #" << i << ", " << trained_on << '/' << dataset.size() - 1 << " groups trained on. ";
				if (j)
					std::cerr << "Current accuracy: " << (training_accuracy * 100) / trained_on << '%';
				if (j != (size_t) dataset.current_iteration && ++trained_on) {
					training_accuracy += model->Train(dataset[j], true);
				}
				emit statusChanged(i + 1,
								   ((float) i * dataset.size() + j + 1)
								   / (dataset.size() * dataset.size()) *
								   100,
								   (training_accuracy * 100) /
								   (trained_on));

			}
			SaveModel(model, i);
			std::cerr << "\rEpoch #" << i + 1 << ", " << trained_on << '/' << dataset.size() << " groups trained on.\n";
			std::cerr << "Train: " << (training_accuracy * 100) / (trained_on) << "% accuracy" << std::endl;
			testing_accuracy = model->Test(dataset[dataset.current_iteration], true);
			std::cerr << "Test:  " << testing_accuracy * 100 << "% accuracy" << std::endl;
			++dataset.current_iteration;
		}
	} catch (std::exception e) {
//		TODO create exception
		qDebug() << "cant upload model or dataset";
	}
}

//void MTWorker::stop() {
//	return;
//}


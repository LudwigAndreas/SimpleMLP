#include <QDebug>

#include "../core/DatasetReading.hpp"

#include "MTWorker.hpp"



MTWorker::MTWorker() {

}

MTWorker::~MTWorker() {

}

void MTWorker::setModel(s21::IMLPModel<float> *model) {
	this->model = model;
}

void MTWorker::setDatasetFileName(std::string file_name) {
	this->dataset_file_name = file_name;
}

void MTWorker::process() {
	try {
		s21::Dataset dataset(ReadDataset(dataset_file_name), 5);
//TODO kdancy promised to fix it
		for (int i = 0; i < dataset.size(); ++i) {
			float training_accuracy = 0;
			float testing_accuracy = 0;
			int trained_on = 0;

			for (int j = 0; j < dataset.size(); ++j) {
				std::cerr << "\rEpoch #" << i << ", " << trained_on << '/' << dataset.size() - 1 << " groups trained on. ";
				if (j)
					std::cerr << "Current accuracy: " << (training_accuracy * 100) / (trained_on) << '%';
				if (j != dataset.current_iteration && ++trained_on)
					training_accuracy += model->Train(dataset[j], true);

				emit statusChanged(i + 1,
								   ((float) i * dataset.size() + j + 1)
								   / (dataset.size() * dataset.size()) * 100,
								   testing_accuracy);
			}
			std::cerr << "\rEpoch #" << i + 1 << ", " << trained_on << '/' << dataset.size() << " groups trained on.\n";
			std::cerr << "Train: " << (training_accuracy * 100) / (trained_on) << "% accuracy" << std::endl;
			testing_accuracy = model->Test(dataset[dataset.current_iteration], true);
			std::cerr << "Test:  " << testing_accuracy * 100 << "% accuracy" << std::endl;
			++dataset.current_iteration;
		}
	} catch (std::exception e) {
		qDebug() << "cant upload model or dataset";
	}
}


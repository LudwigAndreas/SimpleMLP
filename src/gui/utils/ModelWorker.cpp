#include "ModelWorker.hpp"

#include <QDebug>

#include "sstream"

#include "src/core/utils/MLPSerializer.hpp"
#include "src/core/exceptions/ModelProcessingException.hpp"


ModelWorker::ModelWorker() {
	this->num_of_epochs = 5;
	this->stop = false;
}

ModelWorker::~ModelWorker() {
	delete model;
}

void ModelWorker::setModel(s21::IMLPModel<float> *model) {
	this->model = model;
}

void ModelWorker::setDatasetFileName(std::string file_name) {
	this->dataset_file_name = file_name;
}

void ModelWorker::SaveModel(s21::IMLPModel<float> *model, int iteration) {
	std::stringstream	ss;

	if (model != nullptr) {
		ss << "testmodel" << iteration << ".mlpmodel";
		s21::MLPSerializer<float>::SerializeMLPMatrixModel(
				(s21::MLPMatrixModel *) (model), ss.str());
	}
}

void ModelWorker::setNumOfEpochs(int num) {
	this->num_of_epochs = num;
}

void ModelWorker::stopTraining() {
	stop = true;
}

#include "ModelWorker.h"

#include <QDebug>

#include "sstream"

#include "core/utils/MLPSerializer.h"
#include "core/exceptions/ModelProcessingException.h"
#include "gui/utils/const.h"


ModelWorker::ModelWorker() {
	this->num_of_epochs = 5;
	this->stop = false;
}

ModelWorker::~ModelWorker() {
	delete model;
}

void ModelWorker::setModel(s21::IMLPModel *model) {
	this->model = model;
}

void ModelWorker::setDatasetFileName(std::string file_name) {
	this->dataset_file_name = file_name;
}

void ModelWorker::SaveModel(s21::IMLPModel *model, int iteration) {
	std::stringstream	ss;

	if (model != nullptr) {
		ss << s21::constant::model_autosave_filename << iteration << ".mlpmodel";
		s21::MLPSerializer<float>::SerializeMLPModel(model, ss.str());
	}
}

void ModelWorker::setNumOfEpochs(int num) {
	this->num_of_epochs = num;
}

void ModelWorker::stopTraining() {
	stop = true;
}

#include "ModelTestWorker.hpp"

#include "src/core/DatasetReading.hpp"
#include "src/core/exceptions/ModelProcessingException.hpp"
#include "src/core/utils/ConfusionMatrix.hpp"

ModelTestWorker::ModelTestWorker() {
	fraction = 100;
}

void ModelTestWorker::setDatasetFraction(int value) {
	if (value >= 0 && value <= 100)
		this->fraction = value;
}

void ModelTestWorker::process() {
	try {
		s21::Dataset dataset(ReadDataset(dataset_file_name), 1);
		auto result = new std::vector<s21::ConfusionMatrix>(26);
		int size = (int) dataset[0].size() * fraction / 100;
		for (int k = 0; k < size; ++k) {
			if (this->stop)
				return;
			int expected = model->getMostProbablePrediction(dataset[0][k].y.ToVector());
			int got = model->Predict(dataset[0][k].x);
			for (size_t l = 0; l < result->size(); ++l) {
				if (expected != l && got != l)
					(*result)[l].tn++;
				else if (expected == l && got == l)
					(*result)[l].tp++;
				else if (expected == l && got != l)
					(*result)[l].fn++;
				else if (expected != l && got == l)
					(*result)[l].fp++;
			}
			emit statusChanged(((k + 1) * 100) / size);
		}
//		for (auto & item : *result ) {
//			std::cerr << item.tp << " " << item.fn << std::endl;
//			std::cerr << item.fp << " " << item.tn << std::endl;
//			std::cerr << std::endl;
//		}
		emit finishedResult(result);
	} catch (std::exception &e) {
		throw ModelProcessingException("Data processing error");
	}
}
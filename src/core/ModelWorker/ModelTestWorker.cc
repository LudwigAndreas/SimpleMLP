#include "ModelTestWorker.h"

#include <chrono>

#include "core/DatasetReading.h"
#include "core/exceptions/ModelProcessingException.h"
#include "core/utils/ConfusionMatrix.h"

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
        int size = (int)dataset[0].size() * fraction / 100;
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
        for (int k = 0; k < size; ++k) {
            if (this->stop)
                return;
            int expected =
                model->getMostProbablePrediction(dataset[0][k].y.ToVector());
            int got = model->Predict(dataset[0][k].x);
            for (int l = 0; l < (int)result->size(); ++l) {
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
        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        emit finishedResult(result, static_cast<float>(elapsed_seconds.count()));
    } catch (std::exception &e) {
        throw ModelProcessingException("Data processing error");
    }
}
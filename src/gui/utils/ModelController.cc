#include "ModelController.h"

#include <libs21/include/libs21.h>

#include "core/utils/MLPSerializer.hpp"
#include "core/utils/ModelMetrics.h"
#include "gui/view/mainwindow.h"
#include "gui/view/testdatainfodialog.h"

ModelController::ModelController() {
    this->current_model = nullptr;
    this->training_thread = nullptr;
    this->training_worker = nullptr;
    this->testing_thread = nullptr;
    this->testing_worker = nullptr;
    this->builder = new s21::LetterRecognitionMLPModelBuilder();
    this->window = nullptr;
}

ModelController::~ModelController() {
    delete current_model;
    delete training_thread;
    delete training_worker;
    delete testing_thread;
    delete testing_worker;
    delete builder;
}

void ModelController::SetWindow(MainWindow *window) {
    this->window = window;
}

void ModelController::HandleModelConfigured() {
    int numOfHiddenLayers = window->getNumOfHiddenLayers();
    std::string activationFunc = window->getActivationFunc();
    int hiddenUnitsPerLayer = window->getHiddenUnitsPerLayer();
    std::string perceptionBase = window->getPerceptionBase();
    float learningRate = window->getLearningRate();
    if (current_model != nullptr)
        delete current_model;
    current_model = builder->HiddenLayers(numOfHiddenLayers)
                    ->ActivationFunc(activationFunc)
                    ->HiddenUnitsPerLayer(hiddenUnitsPerLayer)
                    ->PerceptionBase(perceptionBase)
                    ->LearningRate(learningRate, true)
                    ->GetResult();
}

void ModelController::HandleModelImported(QFile *file) {
    if (current_model != nullptr)
        delete current_model;
    current_model = s21::MLPSerializer<float>::DeserializeMLPModel(
                        file->fileName().toStdString());
}

bool ModelController::IsTrainingRunning() {
    return training_thread != nullptr && training_thread->isRunning();
}

void ModelController::HandleStartTraining(QFile *file) {
    if (training_thread != nullptr) {
        this->training_thread = new QThread();
        if (training_worker == nullptr)
            delete training_worker;
        this->training_worker = new ModelTrainWorker();
        training_worker->setModel(current_model);
        training_worker->setNumOfEpochs(window->getNumOfEpochs());
        training_worker->setDatasetFileName(file->fileName().toStdString());
        training_worker->moveToThread(this->training_thread);

        connect(this->training_thread, SIGNAL(started()), training_worker,
                SLOT(process()));
        connect(training_worker, SIGNAL(finished()), this->training_thread,
                SLOT(quit()));
        connect(training_worker, SIGNAL(statusChanged(int, int, float)), this,
                SLOT(TrainingStatusChanged(int, int, float)));
        connect(training_worker, SIGNAL(finished()), training_worker,
                SLOT(deleteLater()));
        //  connect(training_worker, SIGNAL(),
        //          this, SLOT()); //TODO add finished signal and slot that handle process finish
        connect(this->training_thread, SIGNAL(finished()), this->training_thread,
                SLOT(deleteLater()));

        this->training_thread->start();
    }
}

void ModelController::TrainingStatusChanged(int epoch, int completion,
        float accuracy) {
    window->update_training_status(epoch, completion, accuracy);
}

void ModelController::QuitTraining() {
    if (training_thread) {
        this->training_thread->quit();
        this->training_thread->wait();
        delete training_thread;
        training_thread = nullptr;
    }
}

void ModelController::HandleStartTesting(QFile *file) {
    if (testing_thread != nullptr) {
        this->testing_thread = new QThread();
        if (testing_worker == nullptr)
            delete testing_worker;
        this->testing_worker = new ModelTestWorker();
        testing_worker->setModel(current_model);
        testing_worker->setDatasetFileName(file->fileName().toStdString());
        testing_worker->setDatasetFraction(window->getTestingDatasetFraction());
        testing_worker->moveToThread(this->testing_thread);

        connect(this->testing_thread, SIGNAL(started()), testing_worker,
                SLOT(process()));
        connect(testing_worker, SIGNAL(finished()), this->testing_thread,
                SLOT(quit()));
        connect(testing_worker, SIGNAL(statusChanged(int)), this,
                SLOT(TestingStatusChanged(int)));
        connect(testing_worker,
                SIGNAL(finishedResult(std::vector<s21::ConfusionMatrix> *)), this,
                SLOT(TestingFinished(std::vector<s21::ConfusionMatrix> *)));
        connect(testing_worker, SIGNAL(finished()), testing_worker,
                SLOT(deleteLater()));
        connect(this->testing_thread, SIGNAL(finished()), this->testing_thread,
                SLOT(deleteLater()));
        testing_thread->start();
    }
}

void ModelController::TestingStatusChanged(int completion) {}

void ModelController::TestingFinished(
    std::vector<s21::ConfusionMatrix> *result) {
    auto *predict_window = new TestDataInfoDialog();
    int size = s21::calculate_size(result);
    predict_window->SetModelMetrics(size, s21::calculate_recall(result, size),
                                    s21::calculate_precision(result, size),
                                    s21::calculate_accuracy(result, size));
    window->show_predict_window();
    predict_window->show();
}

void ModelController::QuitTesting() {
    this->testing_thread->quit();
    this->testing_thread->wait();
    delete testing_thread;
    testing_thread = nullptr;
}

void ModelController::FileWasDrawn() {
    static const int new_width = 28;
    static const int new_height = 28;
    int channels_in_file;
    int width_in_file;
    int height_in_file;
    auto image = s21::load_bmp("my_letter.bmp", &width_in_file, &height_in_file,
                               &channels_in_file);
    auto grayscale = s21::bmp_data_to_grayscale(image, new_width, new_height, 3);
    if (current_model) {
        auto matrix_image =
            s21::Matrix<float>(grayscale, new_width, new_height).T();
        matrix_image.set_cols(new_height * new_width);
        matrix_image.set_rows(1);
        std::stringstream ss;
        delete[] image;
        window->onModelGuessed(
            static_cast<char>('A' + current_model->Predict(matrix_image)));
    }
}

bool ModelController::IsModelInitialized() {
    return current_model != nullptr;
}

void ModelController::HandleSaveModel(std::string filename) {
    s21::MLPSerializer<float>::SerializeMLPModel(current_model, filename);
}

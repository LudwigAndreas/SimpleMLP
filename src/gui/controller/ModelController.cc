#include "ModelController.h"

#include <QMessageBox>

#include "core/utils/MLPSerializer.h"
#include "core/utils/ModelMetrics.h"
#include "gui/utils/const.h"
#include "gui/view/mainwindow.h"
#include "gui/view/testdatainfodialog.h"
#include "libs21/include/libs21.h"

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
    QuitTesting();
    QuitTraining();
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
    if (current_model) delete current_model;
    current_model = builder->HiddenLayers(numOfHiddenLayers)
                    ->ActivationFunc(activationFunc)
                    ->HiddenUnitsPerLayer(hiddenUnitsPerLayer)
                    ->PerceptionBase(perceptionBase)
                    ->LearningRate(learningRate, true)
                    ->GetResult();
}

void ModelController::HandleModelImported(QFile *file) {
    if (current_model) delete current_model;
    this->current_model = s21::MLPSerializer<float>::DeserializeMLPModel(
                              file->fileName().toStdString());
}

void ModelController::QuitIntention() {
    if (this->IsTrainingRunning()) {
        QuitTraining();
    }
    if (this->IsTestingRunning()) {
        QuitTesting();
    }
}

bool ModelController::IsTrainingRunning() {
    return training_thread != nullptr && training_thread->isRunning();
}

bool ModelController::IsTestingRunning() {
    return testing_thread != nullptr && testing_thread->isRunning();
}

void ModelController::HandleStartTraining(QFile *file) {
    if (training_thread) {
        if (training_thread->isRunning()) training_thread->quit();
    }
    this->training_thread = new QThread();
    if (training_worker) {
        training_worker->stopTraining();
        delete training_worker;
    }
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
    connect(training_worker, SIGNAL(MeanErrorCalculated(int, float)), this,
            SLOT(HandleMSEUpdate(int, float)));
    connect(training_worker, SIGNAL(finished()), this, SLOT(TrainingFinished()));
    connect(training_thread, SIGNAL(finished()), this->training_thread,
            SLOT(deleteLater()));

    this->training_thread->start();
}

void ModelController::TrainingStatusChanged(int epoch, int completion,
        float accuracy) {
    if (completion == 100) {
        window->TrainingFinished();
    }
    window->update_training_status(epoch, completion, accuracy);
}

void ModelController::QuitTraining() {
    if (training_worker) {
        this->training_worker->stopTraining();
        if (training_thread) {
            this->training_thread->quit();
            this->training_thread->wait();
            delete training_thread;
            training_thread = nullptr;
        }
        delete this->training_worker;
        this->training_worker = nullptr;
    }
}

void ModelController::TrainingFinished() {
    this->training_thread->quit();
}

void ModelController::HandleStartTesting(QFile *file) {
    if (testing_thread) {
        if (testing_thread->isRunning()) testing_thread->quit();
    }
    this->testing_thread = new QThread();
    if (testing_worker) {
        testing_worker->stopTraining();
        delete testing_worker;
    }
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
            SIGNAL(finishedResult(std::vector<s21::ConfusionMatrix> *, float)),
            this,
            SLOT(TestingFinished(std::vector<s21::ConfusionMatrix> *, float)));
    connect(testing_worker, SIGNAL(finished()), testing_worker,
            SLOT(deleteLater()));
    connect(this->testing_thread, SIGNAL(finished()), this->testing_thread,
            SLOT(deleteLater()));
    testing_thread->start();
}

void ModelController::TestingStatusChanged(int completion) {
    this->window->update_testing_status(completion);
}

void ModelController::DeletePredictWindow() {
    delete predict_window;
}

void ModelController::TestingFinished(std::vector<s21::ConfusionMatrix> *result,
                                      float time) {
    this->predict_window = new TestDataInfoDialog();
    int size = s21::CalculateSize(result);
    predict_window->SetModelMetrics(size, s21::CalculateRecall(result, size),
                                    s21::CalculatePrecision(result, size),
                                    s21::CalculateAccuracy(result, size), time);
    window->show_predict_window();
    this->predict_window->show();
    connect(this->predict_window, SIGNAL(destroyed()), this,
            SLOT(DeletePredictWindow()));
    delete result;
}

void ModelController::QuitTesting() {
    if (testing_worker) {
        this->testing_worker->stopTraining();
        if (testing_thread) {
            this->testing_thread->quit();
            this->testing_thread->wait();
            delete testing_thread;
            testing_thread = nullptr;
        }
        delete testing_worker;
        testing_worker = nullptr;
    }
}

void ModelController::FileWasDrawn() {
    static const int new_width = 28;
    static const int new_height = 28;
    int channels_in_file;
    int width_in_file;
    int height_in_file;
    auto image = s21::load_bmp(s21::constant::letter_file.c_str(), &width_in_file,
                               &height_in_file, &channels_in_file);
    if (!image) {
        QMessageBox::warning(this->window, tr("Image error"),
                             "Letter imported wrong. Please restart application.");
    }
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

void ModelController::HandleMSEUpdate(int epoch, float mse) {
    this->window->MSEUpdated(epoch, mse);
    if (epoch == this->window->getNumOfEpochs()) QuitTraining();
}

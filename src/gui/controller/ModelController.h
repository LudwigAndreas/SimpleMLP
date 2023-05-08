#ifndef SIMPLEMLP_MODELCONTROLLER_H
#define SIMPLEMLP_MODELCONTROLLER_H

#include <QFile>
#include <QObject>

#include "core/LetterRecognitionMlpModelBuilder.h"
#include "core/ModelWorker/ModelTestWorker.h"
#include "core/ModelWorker/ModelTrainWorker.h"
#include "core/utils/IMLPModel.h"
#include "gui/view/testdatainfodialog.h"

class MainWindow;

class ModelController : public QObject {
    Q_OBJECT

public:
    ModelController();
    ~ModelController();

    bool IsTrainingRunning();
    bool IsTestingRunning();
    bool IsModelInitialized();
    void SetWindow(MainWindow *window);
    void QuitIntention();

protected slots:
    void HandleModelConfigured();
    void HandleModelImported(QFile *file);
    void HandleStartTraining(QFile *file);
    void TrainingStatusChanged(int epoch, int completion, float accuracy);
    void QuitTraining();
    void TrainingFinished();
    void HandleStartTesting(QFile *file);
    void QuitTesting();
    void TestingStatusChanged(int completion);
    void TestingFinished(std::vector<s21::ConfusionMatrix> *result,
                         float time = 0);
    void FileWasDrawn();
    void HandleSaveModel(std::string filename);
    void HandleMSEUpdate(int epoch, float mse);
    void DeletePredictWindow();

private:
    MainWindow *window;
    TestDataInfoDialog *predict_window;
    s21::IMLPModel *current_model;
    QThread *training_thread;
    ModelTrainWorker *training_worker;
    ModelTestWorker *testing_worker;
    QThread *testing_thread;
    s21::LetterRecognitionMLPModelBuilder *builder;
};

#endif  // SIMPLEMLP_MODELCONTROLLER_H

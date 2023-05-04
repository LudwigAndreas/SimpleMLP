#ifndef SIMPLEMLP_MODELCONTROLLER_H
#define SIMPLEMLP_MODELCONTROLLER_H

#include <QObject>
#include <QFile>

#include "core/LetterRecognitionMlpModelBuilder.h"
#include "core/utils/IMLPModel.h"

#include "ModelTestWorker.h"
#include "ModelTrainWorker.h"

class MainWindow;

class ModelController : public QObject {
  Q_OBJECT

public:
  ModelController();
  ~ModelController();

  bool IsTrainingRunning();
  bool IsModelInitialized();
  void SetWindow(MainWindow *window);

protected slots:
  void HandleModelConfigured();
  void HandleModelImported(QFile *file);
  void HandleStartTraining(QFile *file);
  void TrainingStatusChanged(int epoch, int completion, float accuracy);
  void QuitTraining();
  void HandleStartTesting(QFile *file);
  void QuitTesting();
  void TestingStatusChanged(int completion);
  void TestingFinished(std::vector<s21::ConfusionMatrix> *result);
  void FileWasDrawn();
  void HandleSaveModel(std::string filename);

private:
  MainWindow *window;
  s21::IMLPModel *current_model;
  QThread *training_thread;
  ModelTrainWorker *training_worker;
  ModelTestWorker *testing_worker;
  QThread *testing_thread;
  s21::LetterRecognitionMLPModelBuilder *builder;
};

#endif // SIMPLEMLP_MODELCONTROLLER_H

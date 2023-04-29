#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QLineSeries>
#include <QMainWindow>
#include <QMessageBox>
#include <QThread>

#include <sstream>

#include "src/core/LetterRecognitionMlpModelBuilder.hpp"
#include "src/core/utils/IMLPModel.hpp"

#include "src/gui/utils/ModelController.h"

#include "src/gui/utils/ModelTestWorker.hpp"
#include "src/gui/utils/ModelTrainWorker.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  int getNumOfHiddenLayers() const;

  std::string getActivationFunc() const;

  int getHiddenUnitsPerLayer() const;

  std::string getPerceptionBase() const;

  float getLearningRate() const;

  int getNumOfEpochs() const;

  int getTestingDatasetFraction() const;

  void update_testing_status(int completion);

  void update_training_status(int epoch, int group, float accuracy);

  void show_predict_window();

  void onModelGuessed(char letter);

  void ConnectController();

private slots:

  void on_train_model_push_button_pressed();

  void on_test_model_push_button_pressed();

  void on_tabWidget_currentChanged(int index);

  void on_to_train_push_button_pressed();

  void on_predict_push_button_pressed();

  void on_start_training_push_button_pressed();

  //  void update_training_status(int epoch, int group, float accuracy);

  void on_toolButton_pressed();

  void OnModelConfigWasUploaded();

  void onTrainingDatasetWasUploaded();

  void onTestingDatasetWasUploaded();

  void on_toolButton_3_pressed();

  void on_test_model_push_button_2_pressed();

  void on_pushButton_pressed();

  void on_toolButton_4_pressed();

  void on_to_configure_push_button_pressed();

  void on_to_configure_push_button_2_pressed();

  void on_testing_size_horizontal_slider_valueChanged(int value);

  void on_export_model_push_button_pressed();

signals:
  void ModelConfigured();

  void ModelImported(QFile *file);

  void TrainModel(QFile *file);

  void StopTraining();

  void TestModel(QFile *file);

  void LetterSaved();

  void SaveModel(std::string file_path);

private:
  Ui::MainWindow *ui;
  QFile *model_config_file;
  QFile *training_dataset_file;
  QFile *testing_dataset_file;
  QLineSeries *chart_series;
  ModelController *m_controller;

  void ConnectDragNDrop();
  void InitChart();

  bool exitFromTrainPage();
  bool exitFromConfigPage();
  void modelConfigFileWasUploaded(QFile *file);
  void trainDatasetFileWasUploaded(QFile *file);
  void testDatasetFileWasUploaded(QFile *file);
};
#endif // MAINWINDOW_H

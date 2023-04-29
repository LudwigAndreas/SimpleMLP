#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QMessageBox>
#include <QThread>
#include <QLineSeries>

#include <sstream>

#include "src/core/LetterRecognitionMlpModelBuilder.hpp"

#include "src/core/utils/IMLPModel.hpp"
#include "src/gui/utils/ModelTrainWorker.hpp"
#include "src/gui/utils/ModelTestWorker.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_train_model_push_button_pressed();

<<<<<<< Updated upstream
=======
    void on_to_configure_push_button_pressed();

    void on_to_configure_push_button_2_pressed();
  //
>>>>>>> Stashed changes
    void on_test_model_push_button_pressed();

    void on_tabWidget_currentChanged(int index);

	void on_to_train_push_button_pressed();

    void on_predict_push_button_pressed();

    void on_start_training_push_button_pressed();

	void update_training_status(int epoch, int group, float accuracy);

	void on_toolButton_pressed();

    void OnModelConfigWasUploaded();

    void onTrainingDatasetWasUploaded();

    void onTestingDatasetWasUploaded();

    void on_toolButton_3_pressed();

    void on_test_model_push_button_2_pressed();

    void on_pushButton_pressed();

    void on_toolButton_4_pressed();
<<<<<<< Updated upstream

    void on_to_configure_push_button_pressed();
=======
  //
  //    void OnModelConfigWasUploaded();
  //
  //    void onTrainingDatasetWasUploaded();
  //
  //    void onTestingDatasetWasUploaded();
  //
      void on_test_model_push_button_2_pressed();
  //
      void on_pushButton_pressed();
  //
  //
  //
  //    void on_testing_size_horizontal_slider_valueChanged(int value);
  //
        void onFileWasDrawn();
  //
  //	void on_export_model_push_button_pressed();
  //
//      void show_predict_window(std::vector<s21::ConfusionMatrix> *result);
  //	void update_testing_status(int completion);
  //
      void GoToConfigModelPage();
>>>>>>> Stashed changes

    void on_to_configure_push_button_2_pressed();

    void on_testing_size_horizontal_slider_valueChanged(int value);

	void onFileWasDrawn();

<<<<<<< Updated upstream
	void on_export_model_push_button_pressed();
=======
  void CreateConnectionWithController();
  void CreateConnectionWithView();
>>>>>>> Stashed changes

	void show_predict_window(std::vector<s21::ConfusionMatrix> *result);

	void update_testing_status(int completion);

private:
    Ui::MainWindow *ui;
    QFile *model_config_file;
    QFile *training_dataset_file;
    QFile *testing_dataset_file;
    s21::IMLPModel *current_model;
	QThread *training_thread;
	ModelTrainWorker *training_worker;
	ModelTestWorker *testing_worker;
	QThread *testing_thread;
	s21::LetterRecognitionMLPModelBuilder *builder;
	QLineSeries *chart_series;

	bool exitFromTrainPage();
	bool exitFromConfigPage();
	void modelConfigFileWasUploaded(QFile *file);
    void trainDatasetFileWasUploaded(QFile *file);
    void testDatasetFileWasUploaded(QFile *file);
};
#endif // MAINWINDOW_H

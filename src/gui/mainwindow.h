#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QGraphicsScene>

#include "../core/utils/IMLPModel.hpp"

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

    void on_start_model_button_clicked();

    void on_train_model_push_button_pressed();

    void on_test_model_push_button_pressed();

    void on_tabWidget_currentChanged(int index);

    void on_predict_push_button_pressed();

    void on_start_training_push_button_pressed();

	void update_training_status(int epoch, int group, float accuracy);

	void on_toolButton_pressed();

    void on_model_config_was_uploaded();

    void on_training_dataset_was_uploaded();

    void on_testing_dataset_was_uploaded();

    void on_toolButton_3_pressed();

    void on_test_model_push_button_2_pressed();

    void on_pushButton_pressed();

    void on_toolButton_4_pressed();

    void on_back_to_configure_push_button_pressed();

    void on_back_to_configure_push_button_2_pressed();

    void on_testing_size_horizontalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QFile *model_config_file;
    QFile *training_dataset_file;
    QFile *testing_dataset_file;
    s21::IMLPModel<float> *current_model;


    void modelConfigFileWasUploaded(QFile *file);
    void trainDatasetFileWasUploaded(QFile *file);
    void testDatasetFileWasUploaded(QFile *file);
};
#endif // MAINWINDOW_H

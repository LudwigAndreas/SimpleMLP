#include <QFileDialog>
#include <QMessageBox>
#include <QThread>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "importfileitem.h"
#include "testdatainfodialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->training_progress_bar->setValue(0);
    ui->training_progress_bar->hide();

    connect(ui->import_model_config_label, &ImportFileItem::fileWasUploaded,
			this, &MainWindow::on_model_config_was_uploaded);
    connect(ui->import_train_dataset_label, &ImportFileItem::fileWasUploaded,
			this, &MainWindow::on_training_dataset_was_uploaded);
    connect(ui->import_test_dataset_label, &ImportFileItem::fileWasUploaded,
			this, &MainWindow::on_testing_dataset_was_uploaded);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_start_model_button_clicked()
{
//    this->hide();
}


void MainWindow::on_train_model_push_button_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_test_model_push_button_pressed()
{
    ui->training_progress_bar->hide();
    ui->start_training_push_button->show();
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_test_model_push_button_2_pressed()
{
    ui->training_progress_bar->hide();
    ui->start_training_push_button->show();
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_back_to_configure_push_button_pressed()
{
    ui->training_progress_bar->hide();
    ui->start_training_push_button->show();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_back_to_configure_push_button_2_pressed()
{
//    ui->training_progress_bar->hide();
//    ui->start_training_push_button->show();
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (this->model_config_file && index == 1)
        ui->test_model_push_button->setEnabled(true);
    else
        ui->test_model_push_button->setEnabled(false);
}


void MainWindow::on_predict_push_button_pressed()
{
    QWidget *predict_window = new TestDataInfoDialog();
    predict_window->show();
}

void MainWindow::modelConfigFileWasUploaded(QFile *file)
{
    ui->file_path_label->setText(file->fileName());
    ui->test_model_push_button->setEnabled(true);
    ui->import_model_config_label->setPixmap(QPixmap(":/img/empty_file.png").scaled(150, 150));
}

void MainWindow::trainDatasetFileWasUploaded(QFile *file)
{
    ui->file_path_label_2->setText(file->fileName());
    ui->import_train_dataset_label->setPixmap(QPixmap(":/img/empty_file.png").scaled(150, 150));
}

void MainWindow::testDatasetFileWasUploaded(QFile *file)
{
    ui->file_path_label_3->setText(file->fileName());
    ui->import_test_dataset_label->setPixmap(QPixmap(":/img/empty_file.png").scaled(150, 150));
}

void MainWindow::on_model_config_was_uploaded()
{
    this->model_config_file = ui->import_model_config_label->getUploadedFile();
    modelConfigFileWasUploaded(ui->import_model_config_label->getUploadedFile());
}

void MainWindow::on_training_dataset_was_uploaded()
{
    this->training_dataset_file = ui->import_train_dataset_label->getUploadedFile();
    trainDatasetFileWasUploaded(ui->import_train_dataset_label->getUploadedFile());
    ui->start_training_push_button->setEnabled(true);
}

void MainWindow::on_testing_dataset_was_uploaded()
{
    this->testing_dataset_file = ui->import_test_dataset_label->getUploadedFile();
    testDatasetFileWasUploaded(ui->import_test_dataset_label->getUploadedFile());
    ui->predict_push_button->setEnabled(true);
}

void MainWindow::on_toolButton_pressed()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Get Any File");
    QDir d = QFileInfo(file_path).absoluteFilePath();
    QFile file(d.absolutePath());
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    } else {
        this->model_config_file = &file;
        modelConfigFileWasUploaded(&file);
    }
}


void MainWindow::on_start_training_push_button_pressed()
{
//    TODO: in new QThead start training with updating progress_bar value;
    ui->training_progress_bar->setValue(ui->training_progress_bar->value() + 25);
    ui->training_progress_bar->show();
    ui->start_training_push_button->hide();
    if (ui->training_progress_bar->value() == 100)
        ui->test_model_push_button_2->setEnabled(true);
}


void MainWindow::on_toolButton_3_pressed()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Get Any File");
    QDir d = QFileInfo(file_path).absoluteFilePath();
    QFile file(d.absolutePath());
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    } else {
        this->model_config_file = &file;
        trainDatasetFileWasUploaded(&file);
    }
}

void MainWindow::on_toolButton_4_pressed()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Get Any File");
    QDir d = QFileInfo(file_path).absoluteFilePath();
    QFile file(d.absolutePath());
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    } else {
        this->model_config_file = &file;
        testDatasetFileWasUploaded(&file);
    }
}


void MainWindow::on_pushButton_pressed()
{
    ui->paint_view->clear();
}



void MainWindow::on_testing_size_horizontalSlider_valueChanged(int value)
{
    if (value > 0)
        ui->testing_size_label->setText(QString::number((float) (value + 1) / 100));
    else
        ui->testing_size_label->setText(QString::number(0));
}


#include "src/gui/view/mainwindow.h"

#include <sstream>

#include "src/core/LetterRecognitionMlpModelBuilder.hpp"
#include "src/gui/utils/importfileitem.h"
#include "ui_mainwindow.h"
#include "src/gui/view/testdatainfodialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
	this->current_model = nullptr;
	this->training_thread = nullptr;
	this->model_config_file = nullptr;
	this->training_dataset_file = nullptr;
	this->testing_dataset_file = nullptr;
	this->builder = new s21::LetterRecognitionMLPModelBuilder();
	ui->setupUi(this);
    ui->training_progress_bar->setValue(0);
    ui->training_progress_bar->hide();
	ui->paint_view->setBackgroundBrush(QColor("midnightblue"));
    connect(ui->import_model_config_label, &ImportFileItem::fileWasUploaded,
			this, &MainWindow::OnModelConfigWasUploaded);
    connect(ui->import_train_dataset_label, &ImportFileItem::fileWasUploaded,
			this, &MainWindow::onTrainingDatasetWasUploaded);
    connect(ui->import_test_dataset_label, &ImportFileItem::fileWasUploaded,
			this, &MainWindow::onTestingDatasetWasUploaded);
    connect(ui->paint_view, &PaintView::file_saved,
			this, &MainWindow::onFileWasDrawn);
}

MainWindow::~MainWindow()
{
    delete ui;
}



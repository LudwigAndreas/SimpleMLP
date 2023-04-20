#include "src/gui/view/mainwindow.h"

#include <sstream>

#include <QLogValueAxis>
#include <QValueAxis>

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
	this->testing_worker = nullptr;
	this->training_worker = nullptr;
	this->builder = new s21::LetterRecognitionMLPModelBuilder();
	ui->setupUi(this);
	ui->stackedWidget->setCurrentIndex(0);
	ui->chart_widget->hide();

	this->chart_series = new QLineSeries();
	auto *chart = new QChart();
	chart->legend()->hide();
	chart->addSeries(this->chart_series);
	auto *y = new QValueAxis();
	y->setMax(100);
	y->setMin(0.1);
	chart->addAxis(y, Qt::AlignLeft);
	chart_series->attachAxis(y);
	ui->chart_widget->setChart(chart);
	ui->chart_widget->setRenderHint(QPainter::Antialiasing);
//		ui->chart_widget->setCurrentWidget(chart);

	ui->testing_progress_bar->setValue(0);
	ui->testing_progress_bar->hide();
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



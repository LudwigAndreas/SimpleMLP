#include "src/gui/view/mainwindow.h"

#include <sstream>

#include <QLogValueAxis>
#include <QValueAxis>

#include "src/core/LetterRecognitionMlpModelBuilder.hpp"
#include "src/gui/utils/importfileitem.h"
#include "src/gui/view/testdatainfodialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  this->model_config_file = nullptr;
  this->training_dataset_file = nullptr;
  this->testing_dataset_file = nullptr;
  //  this->testing_worker = nullptr;
  //  this->training_worker = nullptr;
  //  this->builder = new s21::LetterRecognitionMLPModelBuilder();
  //  ui->chart_widget->setCurrentWidget(chart);

  ui->stackedWidget->setCurrentIndex(0);
  ui->testing_progress_bar->setValue(0);
  ui->testing_progress_bar->hide();
  ui->paint_view->setBackgroundBrush(QColor("midnightblue"));

  this->m_controller = new ModelController();
  m_controller->SetWindow(this);

  InitChart();
  ConnectDragNDrop();
  ConnectController();
}

int MainWindow::getNumOfEpochs() const {
  return ui->num_of_epochs_spin_box->value();
}

int MainWindow::getNumOfHiddenLayers() const {
  return ui->num_of_hidden_layers_comboBox->currentText().toInt();
}

std::string MainWindow::getActivationFunc() const {
  return ui->activation_func_comboBox->currentText().toStdString();
}

int MainWindow::getHiddenUnitsPerLayer() const {
  return ui->hidden_utf_spin_box->value();
}

std::string MainWindow::getPerceptionBase() const {
  return ui->perceptron_imp_comboBox->currentText().toStdString();
}

float MainWindow::getLearningRate() const {
  return static_cast<float>(ui->lr_double_spin_box->value());
}

void MainWindow::ConnectDragNDrop() {
  connect(ui->import_model_config_label, &ImportFileItem::fileWasUploaded, this,
          &MainWindow::OnModelConfigWasUploaded);
  connect(ui->import_train_dataset_label, &ImportFileItem::fileWasUploaded,
          this, &MainWindow::onTrainingDatasetWasUploaded);
  connect(ui->import_test_dataset_label, &ImportFileItem::fileWasUploaded, this,
          &MainWindow::onTestingDatasetWasUploaded);
  connect(ui->paint_view, SIGNAL(file_saved()), m_controller,
          SLOT(FileWasDrawn()));
}

void MainWindow::InitChart() {
  ui->chart_widget->hide();
  this->chart_series = new QLineSeries();
  auto *chart = new QChart();
  chart->legend()->hide();
  chart->addSeries(this->chart_series);
  auto *y = new QValueAxis();
  y->setMax(100);
  y->setMin(0);
  chart->addAxis(y, Qt::AlignLeft);
  chart_series->attachAxis(y);
  ui->chart_widget->setChart(chart);
  ui->chart_widget->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::ConnectController() {
  connect(this, SIGNAL(ModelConfigured()), m_controller,
          SLOT(HandleModelConfigured()));
  connect(this, SIGNAL(ModelImported(QFile *)), m_controller,
          SLOT(HandleModelImported(QFile *)));
  connect(this, SIGNAL(TrainModel(QFile *)), m_controller,
          SLOT(HandleStartTraining(QFile *)));
  connect(this, SIGNAL(StopTraining()), m_controller, SLOT(QuitTraining()));
  connect(this, SIGNAL(TestModel(QFile *)), m_controller,
          SLOT(HandleStartTesting(QFile *)));
  connect(this, SIGNAL(LetterSaved()), m_controller, SLOT(FileWasDrawn()));
  //  connect(this, SIGNAL(SaveModel(std::string)), m_controller, SLOT(Save));
}

MainWindow::~MainWindow() { delete ui; }

int MainWindow::getTestingDatasetFraction() const {
  return ui->testing_size_horizontal_slider->value();
}

void MainWindow::on_stackedWidget_currentChanged(int index)
{
  if (index == 0)
    onStartConfigurePage();
  else if (index == 1)
    onStartTrainingPage();
  else if (index == 2)
    onStartTestingPage();
}

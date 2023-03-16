#include <QFileDialog>
#include <QMessageBox>
#include <QThread>

#include <sstream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "src/lib/stb_image_write.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "importfileitem.h"
#include "testdatainfodialog.h"
#include "../core/LetterRecognitionMlpModelBuilder.hpp"
#include "../core/utils/MLPSerializer.hpp"
#include "MTWorker.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
	this->current_model = nullptr;
	this->training_thread = new QThread();
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


void MainWindow::on_start_model_button_clicked()
{
//    this->hide();
}

//TODO add advanced settings: lr, units_per_layer
void MainWindow::on_train_model_push_button_pressed()
{
    if (ui->tabWidget->currentIndex() == 0){

		auto *builder =
				new s21::LetterRecognitionMLPModelBuilder();
		current_model = builder
                ->HiddenLayers(ui->num_of_hidden_layers_comboBox->currentText().toInt())
                ->ActivationFunc(ui->activation_func_comboBox->currentText().toStdString())
				->HiddenUnitsPerLayer(ui->hidden_utf_spin_box->value())
                ->PerceptionBase(ui->perceptron_imp_comboBox->currentText().toStdString())
				->LearningRate((float) ui->lr_double_spin_box->value(), true)
				->GetResult();
    } else if (ui->tabWidget->currentIndex() == 1 && !ui->file_path_label->text().isEmpty()){
		current_model = s21::MLPSerializer<float>::DeserializeMLPMatrixModel(ui->file_path_label->text().toStdString());
    } else {
		QMessageBox::information(this, tr("Unable to create model"), "There is an error in creating model");
	}
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_test_model_push_button_pressed()
{
    ui->training_progress_bar->hide();
    ui->start_training_push_button->show();
    ui->stackedWidget->setCurrentIndex(2);
	ui->train_info_text_label->setDisabled(true);
}

void MainWindow::on_test_model_push_button_2_pressed()
{
    ui->training_progress_bar->hide();
    ui->start_training_push_button->show();
    ui->stackedWidget->setCurrentIndex(2);
}
//TODO add message boxes for every button that can break app
void MainWindow::on_back_to_configure_push_button_pressed()
{
	if (this->training_thread->isRunning()) {
		QMessageBox training_is_running_message;
		training_is_running_message.setText("The training is already running"); //TODO finish message box
		training_is_running_message.setWindowTitle(tr("The training is already running"));
//		training_is_running_message.set
		training_is_running_message.setStandardButtons(QMessageBox::Ok | QMessageBox::Discard | QMessageBox::Cancel);
		training_is_running_message.setDefaultButton(QMessageBox::Cancel);
		int ret = training_is_running_message.exec();
//				msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
//		msgBox.setDefaultButton(QMessageBox::Save);
	}
    ui->training_progress_bar->hide();
	ui->training_progress_bar->setValue(0);
    ui->start_training_push_button->show();
    ui->stackedWidget->setCurrentIndex(0);
	ui->train_info_text_label->setDisabled(true);
}

void MainWindow::on_back_to_configure_push_button_2_pressed()
{
    ui->training_progress_bar->hide();
	ui->training_progress_bar->setValue(0);
    ui->start_training_push_button->show();
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
	this->current_model = s21::MLPSerializer<float>::DeserializeMLPMatrixModel(file->fileName().toStdString());
}

void MainWindow::trainDatasetFileWasUploaded(QFile *file)
{
	ui->start_training_push_button->setEnabled(true);
    ui->file_path_label_2->setText(file->fileName());
    ui->import_train_dataset_label->setPixmap(QPixmap(":/img/empty_file.png").scaled(150, 150));
}

void MainWindow::testDatasetFileWasUploaded(QFile *file)
{
    ui->file_path_label_3->setText(file->fileName());
    ui->import_test_dataset_label->setPixmap(QPixmap(":/img/empty_file.png").scaled(150, 150));
}

void MainWindow::OnModelConfigWasUploaded()
{
    this->model_config_file = ui->import_model_config_label->getUploadedFile();
    modelConfigFileWasUploaded(ui->import_model_config_label->getUploadedFile());
}

void MainWindow::onTrainingDatasetWasUploaded()
{
    this->training_dataset_file = ui->import_train_dataset_label->getUploadedFile();
    trainDatasetFileWasUploaded(ui->import_train_dataset_label->getUploadedFile());
    ui->start_training_push_button->setEnabled(true);
}

void MainWindow::onTestingDatasetWasUploaded()
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

	if (this->training_thread->isRunning()) {
		QMessageBox::information(this, tr("The training is already running"),
								 "Can't start training twice");
		return;
	}
	ui->training_progress_bar->show();
	ui->start_training_push_button->hide();
	ui->test_model_push_button->hide();
	auto *worker = new MTWorker();
	worker->setModel(current_model);
	worker->setNumOfEpochs(ui->num_of_epochs_spin_box->value());
	worker->setDatasetFileName((ui->file_path_label_2->text().toStdString()));
	worker->moveToThread(this->training_thread);
	connect(this->training_thread, SIGNAL(started()), worker, SLOT(process()));
	connect(worker, SIGNAL(finished()), this->training_thread, SLOT(quit()));
	connect(worker, SIGNAL(statusChanged(int, int, float)), this, SLOT(update_training_status(int, int, float)));
	connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
	connect(this->training_thread, SIGNAL(finished()), this->training_thread, SLOT(deleteLater()));
	this->training_thread->start();
}

void MainWindow::update_training_status(int epoch, int completion, float accuracy) {
	ui->train_info_text_label->setEnabled(true);
	std::stringstream ss;
	ss << "<html><head/><body><p><span style=\" font-size:18pt; font-weight:700;\">Epoch: </span><span style=\" font-size:18pt;\">"
	<< epoch
	<< "</span></p><p><span style=\" font-size:18pt; font-weight:700;\">Current accuracy: </span><span style=\" font-size:18pt;\">"
	<< std::setprecision(3) << (std::isnan(accuracy) ? 0 : accuracy) << "%"
	<< "</span></p><p><span style=\" font-size:18pt; font-weight:700;\">Completion: </span><span style=\" font-size:18pt;\">"
	<< completion << "%"
	<< "</span></p></body></html>";
	ui->train_info_text_label->setText(ss.str().data());
	ui->training_progress_bar->setValue(completion);

	if (ui->training_progress_bar->value() == 100) {
		ui->test_model_push_button_2->setEnabled(true);
	}
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

void MainWindow::onFileWasDrawn() {
	static const int new_width = 28;
	static const int new_height = 28;

	auto image = ReadAndResizeBMP("my_letter.bmp", new_width, new_height);
	auto grayscale = BMPDataToGrayscale(image, new_width, new_height, 3);
	if (current_model) {
		auto matrix_image = s21::Matrix<float>(grayscale, new_width, new_height).T();
		matrix_image.set_cols(new_height * new_width);
		matrix_image.set_rows(1);
		std::cout << matrix_image << std::endl;
		std::stringstream ss;
		ss << "<html><head/><body><p><span style=\" font-size:288pt;\">" <<
		(char) ('A' + current_model->Predict(matrix_image))
		<< "</span></p></body></html>";
		ui->prediction_result_label->setText(QString(ss.str().data()));
	} else {
		QMessageBox::information(this, tr("There is no loaded model"), "Can't create prediction without model");
	}
	delete[] image;

}


void MainWindow::on_export_model_push_button_pressed()
{
	QString file_path = QFileDialog::getSaveFileName(this, "Save config file");
//	QDir d = QFileInfo(file_path).absoluteFilePath();
	// TODO rewrite for not matrix model (made in universal)
	s21::MLPSerializer<float>::SerializeMLPMatrixModel((s21::MLPMatrixModel *)current_model, file_path.toStdString());
}


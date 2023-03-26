#include "src/gui/view/mainwindow.h"

#include "ui_mainwindow.h"
#include "src/core/utils/MLPSerializer.hpp"

bool MainWindow::exitFromConfigPage() {
	ui->file_path_label->clear();
	ui->import_model_config_label->clear();
	ui->import_model_config_label->setText(
			"<html><head/><body><p><span style=\" font-size:18pt;\">"
			"Drag and drop model config file"
			"</span></p><p><span style=\" font-size:18pt;\">"
			" (should be *.mlpmodel)</span></p></body></html>");
	return true;
}

void MainWindow::on_train_model_push_button_pressed()
{
	if (ui->tabWidget->currentIndex() == 0){
		current_model = builder
				->HiddenLayers(
						ui->num_of_hidden_layers_comboBox->currentText().toInt())
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
	exitFromConfigPage();
	ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_test_model_push_button_pressed()
{
	exitFromConfigPage();
	ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
	if (this->model_config_file && index == 1) {
		ui->test_model_push_button->setEnabled(true);
	} else {
		ui->test_model_push_button->setEnabled(false);
	}
}

void MainWindow::modelConfigFileWasUploaded(QFile *file)
{
	if (!file->fileName().endsWith(".mlpmodel"))
		QMessageBox::information(this, tr("Wrong file format"),
								 "Incorrect file format. The file must have the .mlpmodel extension ");
	else {
		if (this->model_config_file != nullptr) {
			delete this->model_config_file;
			this->model_config_file = nullptr;
		}
		this->model_config_file = file;
		ui->file_path_label->setText(file->fileName());
		ui->test_model_push_button->setEnabled(true);
		ui->import_model_config_label->setPixmap(
				QPixmap(":/img/empty_file.png").scaled(150, 150));
		this->current_model = s21::MLPSerializer<float>::DeserializeMLPMatrixModel(
				file->fileName().toStdString());
	}
}

void MainWindow::OnModelConfigWasUploaded()
{
	modelConfigFileWasUploaded(ui->import_model_config_label->getUploadedFile());
}

void MainWindow::on_toolButton_pressed()
{
	QString file_path = QFileDialog::getOpenFileName(this, "Get Any File");
	QDir d = QFileInfo(file_path).absoluteFilePath();
	QFile *file = new QFile(d.absolutePath());
	if (!file->open(QIODevice::ReadOnly)) {
		QMessageBox::information(this, tr("Unable to open file"), file->errorString());
		return;
	} else {
		modelConfigFileWasUploaded(file);
	}
}

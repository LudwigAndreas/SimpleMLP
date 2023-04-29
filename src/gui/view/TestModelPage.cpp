#include "src/gui/view/mainwindow.h"

#include "ui_mainwindow.h"
#include "testdatainfodialog.h"
#include "src/core/utils/MLPSerializer.hpp"
#include "libs21/include/libs21.h"

void MainWindow::on_to_configure_push_button_2_pressed()
{
	ui->stackedWidget->setCurrentIndex(0);
	ui->predict_push_button->setDisabled(true);
	ui->prediction_result_label->clear();
}

void MainWindow::on_to_train_push_button_pressed()
{
	ui->stackedWidget->setCurrentIndex(1);
	ui->predict_push_button->setDisabled(true);
	ui->prediction_result_label->clear();
}

void MainWindow::on_predict_push_button_pressed()
{
	ui->predict_push_button->hide();
	ui->testing_progress_bar->show();
	this->testing_thread = new QThread();
	this->testing_worker = new ModelTestWorker();
	testing_worker->setModel(current_model);
	testing_worker->setDatasetFileName(
			this->testing_dataset_file->fileName().toStdString());
	testing_worker->setDatasetFraction(ui->testing_size_horizontal_slider->value());
	testing_worker->moveToThread(this->testing_thread);

	connect(this->testing_thread, SIGNAL(started()),
			testing_worker, SLOT(process()));
	connect(testing_worker, SIGNAL(finished()),
			this->testing_thread, SLOT(quit()));
	connect(testing_worker, SIGNAL(statusChanged(int)),
			this, SLOT(update_testing_status(int)));
	connect(testing_worker, SIGNAL(finishedResult(std::vector<s21::ConfusionMatrix> *)),
			this, SLOT(show_predict_window(std::vector<s21::ConfusionMatrix> *)));
	connect(testing_worker, SIGNAL(finished()),
			testing_worker, SLOT(deleteLater()));
	connect(this->testing_thread, SIGNAL(finished()),
			this->testing_thread, SLOT(deleteLater()));
	testing_thread->start();
}

void MainWindow::update_testing_status(int completion) {
	ui->testing_progress_bar->setValue(completion);
}


void MainWindow::show_predict_window(std::vector<s21::ConfusionMatrix> *result) {
	auto *predict_window = new TestDataInfoDialog();
	predict_window->setConfusionMatrix(result);
	predict_window->show();
	ui->testing_progress_bar->setValue(0);
	ui->testing_progress_bar->hide();
	ui->predict_push_button->show();
	ui->predict_push_button->setEnabled(true);
}


void MainWindow::testDatasetFileWasUploaded(QFile *file)
{
	if (!file->fileName().endsWith(".csv")) {
		QMessageBox::information(this, tr("Wrong file format"),
								 "Incorrect file format. The file must have the .csv extension ");
	} else {
		if (this->testing_dataset_file != nullptr) {
			delete this->testing_dataset_file;
			this->testing_dataset_file = nullptr;
		}
		this->testing_dataset_file = file;
		ui->file_path_label_3->setText(file->fileName());
		ui->import_test_dataset_label->setPixmap(QPixmap(":/img/empty_file.png").scaled(150, 150));
		ui->predict_push_button->setEnabled(true);
	}
}

void MainWindow::onTestingDatasetWasUploaded()
{
	testDatasetFileWasUploaded(
			ui->import_test_dataset_label->getUploadedFile());
}

void MainWindow::on_toolButton_4_pressed()
{
	QString file_path = QFileDialog::getOpenFileName(this, "Get Any File");
	QDir d = QFileInfo(file_path).absoluteFilePath();
	QFile *file = new QFile(d.absolutePath());
	if (!file->open(QIODevice::ReadOnly)) {
		QMessageBox::information(this, tr("Unable to open file"), file->errorString());
		return;
	} else {
		testDatasetFileWasUploaded(file);
	}
}

void MainWindow::onFileWasDrawn() {
    //TODO extract logic from this file
	static const int new_width = 28;
	static const int new_height = 28;
    int channels_in_file;
    int width_in_file;
    int height_in_file;

	auto image = s21::load_bmp("my_letter.bmp", &width_in_file, &height_in_file, &channels_in_file);
	auto grayscale = s21::bmp_data_to_grayscale(image, new_width, new_height, 3);
	if (current_model) {
		auto matrix_image = s21::Matrix<float>(grayscale, new_width, new_height).T();
		matrix_image.set_cols(new_height * new_width);
		matrix_image.set_rows(1);
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

void MainWindow::on_pushButton_pressed()
{
	ui->paint_view->clear();
	ui->prediction_result_label->clear();
}

void MainWindow::on_testing_size_horizontal_slider_valueChanged(int value)
{
	ui->testing_size_label->setText(QString::number((float) value / 100));
}

void MainWindow::on_export_model_push_button_pressed()
{
	QString file_path = QFileDialog::getSaveFileName(this, "Save config file", "", "Model config files (*.mlpmodel)");
    if (file_path.isNull()) {
        QMessageBox::information(this, tr("File path is empty"),
                                 "Incorrect file path. Unable to save file");
        return;
    }
	//	QDir d = QFileInfo(file_path).absoluteFilePath();
	// TODO rewrite for not matrix model (made in universal)
	s21::MLPSerializer<float>::SerializeMLPModel((s21::MLPMatrixModel *)current_model, file_path.toStdString());
}
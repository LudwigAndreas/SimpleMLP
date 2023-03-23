#include "src/gui/view/mainwindow.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "src/lib/stb_image_write.h"

#include "ui_mainwindow.h"
#include "testdatainfodialog.h"
#include "src/core/utils/BMPReader.hpp"
#include "src/core/utils/MLPSerializer.hpp"

void MainWindow::on_to_configure_push_button_2_pressed()
{
	ui->stackedWidget->setCurrentIndex(0);
	ui->prediction_result_label->clear();
}

void MainWindow::on_to_train_push_button_pressed()
{
	ui->stackedWidget->setCurrentIndex(1);
	ui->prediction_result_label->clear();
}

void MainWindow::on_predict_push_button_pressed()
{
	QWidget *predict_window = new TestDataInfoDialog();
	predict_window->show();
}

void MainWindow::testDatasetFileWasUploaded(QFile *file)
{
	ui->file_path_label_3->setText(file->fileName());
	ui->import_test_dataset_label->setPixmap(QPixmap(":/img/empty_file.png").scaled(150, 150));
	ui->predict_push_button->setEnabled(true);
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
	QFile file(d.absolutePath());
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(this, tr("Unable to open file"), file.errorString());
		return;
	} else {
		this->model_config_file = &file;
		testDatasetFileWasUploaded(&file);
	}
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

void MainWindow::on_testing_size_horizontalSlider_valueChanged(int value)
{
	if (value > 0)
		ui->testing_size_label->setText(QString::number((float) (value + 1) / 100));
	else
		ui->testing_size_label->setText(QString::number(0));
}

void MainWindow::on_export_model_push_button_pressed()
{
	QString file_path = QFileDialog::getSaveFileName(this, "Save config file");
	//	QDir d = QFileInfo(file_path).absoluteFilePath();
	// TODO rewrite for not matrix model (made in universal)
	file_path.append(".mlpmodel");
	s21::MLPSerializer<float>::SerializeMLPMatrixModel((s21::MLPMatrixModel *)current_model, file_path.toStdString());
}
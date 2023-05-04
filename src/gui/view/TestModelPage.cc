#include "gui/view/mainwindow.h"

#include "libs21/include/libs21.h"
#include "core/utils/MLPSerializer.h"
#include "gui/utils/const.h"
#include "testdatainfodialog.h"
#include "ui_mainwindow.h"

//  TODO remove exitFromTestingPage and add onCreate analog

void MainWindow::onStartTestingPage() {
  ui->paint_view->clear();
  ui->prediction_result_label->clear();
  ui->testing_progress_bar->hide();
  ui->testing_progress_bar->setValue(0);
  ui->file_path_label_3->clear();
  ui->import_test_dataset_label->clear();
  ui->import_test_dataset_label->setText(
      "<html><head/><body><p><span style=\" font-size:18pt;\">Drag and drop "
      "test dataset file</span></p><p><span style=\" font-size:18pt;\"> "
      "(should be *.csv)</span></p></body></html>");
  ui->tabWidget_2->setCurrentIndex(0);
}

void MainWindow::on_to_configure_push_button_2_pressed() {
  ui->stackedWidget->setCurrentIndex(0);
  ui->predict_push_button->setDisabled(true);
  ui->prediction_result_label->clear();
}

void MainWindow::on_to_train_push_button_pressed() {
  ui->stackedWidget->setCurrentIndex(1);
  ui->predict_push_button->setDisabled(true);
  ui->prediction_result_label->clear();
}

void MainWindow::on_predict_push_button_pressed() {
  ui->predict_push_button->hide();
  ui->testing_progress_bar->show();
}

void MainWindow::update_testing_status(int completion) {
  ui->testing_progress_bar->setValue(completion);
}

void MainWindow::show_predict_window() {
  ui->testing_progress_bar->setValue(0);
  ui->testing_progress_bar->hide();
  ui->predict_push_button->show();
  ui->predict_push_button->setEnabled(true);
}

void MainWindow::testDatasetFileWasUploaded(QFile *file) {
  if (!file->fileName().endsWith(".csv")) {
    QMessageBox::information(
        this, tr("Wrong file format"),
        "Incorrect file format. The file must have the .csv extension ");
  } else {
    if (this->testing_dataset_file != nullptr) {
      delete this->testing_dataset_file;
      this->testing_dataset_file = nullptr;
    }
    this->testing_dataset_file = file;
    QFileInfo fileInfo(file->fileName());
    ui->file_path_label_3->setText(fileInfo.fileName());
    ui->import_test_dataset_label->setPixmap(
        QPixmap(s21::constant::empty_file_icon_path.c_str()).scaled(150, 150));
    ui->predict_push_button->setEnabled(true);
  }
}

void MainWindow::onTestingDatasetWasUploaded() {
  testDatasetFileWasUploaded(ui->import_test_dataset_label->getUploadedFile());
}

void MainWindow::on_toolButton_4_pressed() {
  QString file_path = QFileDialog::getOpenFileName(this, "Get Any File");
  QDir d = QFileInfo(file_path).absoluteFilePath();
  QFile *file = new QFile(d.absolutePath());
  if (!file->open(QIODevice::ReadOnly)) {
    QMessageBox::information(this, tr("Unable to open file"),
                             file->errorString());
    return;
  } else {
    testDatasetFileWasUploaded(file);
  }
}

void MainWindow::onModelGuessed(char letter) {
  if (m_controller->IsModelInitialized()) {
    std::stringstream ss;
    ss << "<html><head/><body><p><span style=\" font-size:288pt;\">" << letter
       << "</span></p></body></html>";
    ui->prediction_result_label->setText(QString(ss.str().data()));
  } else {
    QMessageBox::information(this, tr("There is no loaded model"),
                             "Can't create prediction without model");
  }
}

void MainWindow::on_pushButton_pressed() {
  ui->paint_view->clear();
  ui->prediction_result_label->clear();
}

void MainWindow::on_testing_size_horizontal_slider_valueChanged(int value) {
  ui->testing_size_label->setText(QString::number((float)value / 100));
}

void MainWindow::on_export_model_push_button_pressed() {
  QString file_path = QFileDialog::getSaveFileName(
      this, "Save config file", "", "Model config files (*.mlpmodel)");
  if (file_path.isNull()) {
    QMessageBox::information(this, tr("File path is empty"),
                             "Incorrect file path. Unable to save file");
    return;
  }
  emit SaveModel(file_path.toStdString());
}
#include "gui/view/mainwindow.h"

#include <QValueAxis>
#include <iomanip>

#include "gui/utils/const.h"
#include "ui_mainwindow.h"

void MainWindow::onStartTrainingPage() {
  ui->test_model_push_button_2->setDisabled(true);
  ui->training_progress_bar->hide();
  ui->training_progress_bar->setValue(0);
  ui->num_of_epochs_spin_box->show();
  ui->chart_widget->hide();
  ui->train_info_text_label->setDisabled(true);
  ui->start_training_push_button->show();
  ui->start_training_push_button->setDisabled(true);
  ui->import_train_dataset_label->clear();
  ui->import_train_dataset_label->setText(
      "<html><head/><body><p><span style=\" "
      "font-size:14pt;\">Drag and drop train dataset file"
      "</span></p><p><span style=\" font-size:14pt;\">"
      " (should be *.csv)</span></p></body></html>");
  ui->file_path_label_2->clear();
}

bool MainWindow::checkTrainingStatus() {
  if (m_controller->IsTrainingRunning()) {
    QMessageBox training_is_running_message;
    training_is_running_message.setText("If you stop the learning process, "
                                        "the progress will not be saved. "
                                        "Are you sure you want to stop?");
    training_is_running_message.setWindowTitle(
        tr("The training is already running"));
    training_is_running_message.setStandardButtons(QMessageBox::Yes |
                                                   QMessageBox::Cancel);
    training_is_running_message.setDefaultButton(QMessageBox::Cancel);
    int ret = training_is_running_message.exec();
    if (ret == QMessageBox::Yes) {
      emit StopTraining();
    } else
      return false;
  }
  return true;
}

void MainWindow::on_test_model_push_button_2_pressed() {
  if (checkTrainingStatus())
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_to_configure_push_button_pressed() {
  if (checkTrainingStatus())
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::trainDatasetFileWasUploaded(QFile *file) {
  if (!file->fileName().endsWith(".csv")) {
    QMessageBox::information(
        this, tr("Wrong file format"),
        "Incorrect file format. The file must have the .csv extension ");
  } else {
    if (this->training_dataset_file != nullptr) {
      delete this->training_dataset_file;
      this->training_dataset_file = nullptr;
    }
    this->training_dataset_file = file;
    ui->start_training_push_button->setEnabled(true);
    QFileInfo fileInfo(file->fileName());
    ui->file_path_label_2->setText(fileInfo.fileName());
    ui->import_train_dataset_label->setPixmap(
        QPixmap(s21::constant::empty_file_icon_path.c_str()).scaled(150, 150));
    ui->start_training_push_button->setEnabled(true);
  }
}

void MainWindow::onTrainingDatasetWasUploaded() {
  trainDatasetFileWasUploaded(
      ui->import_train_dataset_label->getUploadedFile());
}

void MainWindow::on_toolButton_3_pressed() {
  QString file_path = QFileDialog::getOpenFileName(this, "Get Any File");
  QDir d = QFileInfo(file_path).absoluteFilePath();
  QFile *file = new QFile(d.absolutePath());
  if (!file->open(QIODevice::ReadOnly)) {
    QMessageBox::information(this, tr("Unable to open file"),
                             file->errorString());
    return;
  } else {
    trainDatasetFileWasUploaded(file);
  }
}

void MainWindow::on_start_training_push_button_pressed() {
  if (m_controller->IsTrainingRunning()) {
    QMessageBox::information(this, tr("The training is already running"),
                             "Can't start training twice");
    return;
  }
  ui->training_progress_bar->show();
  ui->start_training_push_button->hide();
  ui->num_of_epochs_spin_box->hide();
  emit TrainModel(this->training_dataset_file);

  if (!ui->chart_widget->chart()->axes(Qt::Horizontal).isEmpty())
    ui->chart_widget->chart()->removeAxis(
        ui->chart_widget->chart()->axes(Qt::Horizontal).first());
  auto *x = new QValueAxis();
  x->setMax(ui->num_of_epochs_spin_box->value());
  x->setTickCount(ui->num_of_epochs_spin_box->value() + 1);
  x->setMin(0);
  ui->chart_widget->chart()->addAxis(x, Qt::AlignBottom);
  chart_series->attachAxis(x);
  mse_series->attachAxis(x);
  this->chart_series->clear();
  this->mse_series->clear();
  // mse_series->append(0,0);
  ui->chart_widget->show();
}

void MainWindow::update_training_status(int epoch, int completion,
                                        float accuracy) {
  ui->train_info_text_label->setEnabled(true);
  std::stringstream ss;
  ss << "<html><head/><body><p><span style=\" font-size:14pt;"
        " font-weight:700;\">Epoch: </span><span style=\" font-size:14pt;\">"
     << epoch
     << "</span></p><p><span style=\" font-size:14pt;"
        " font-weight:700;\">Current accuracy: </span><span style=\""
        " font-size:14pt;\">"
     << std::setprecision(3) << (std::isnan(accuracy) ? 0 : accuracy) << "%"
     << "</span></p><p><span style=\" font-size:14pt;"
        " font-weight:700;\">Completion: </span><span style=\""
        " font-size:14pt;\">"
     << completion << "%"
     << "</span></p></body></html>";
  ui->train_info_text_label->setText(ss.str().data());
  ui->training_progress_bar->setValue(completion);
  this->chart_series->append(((float)completion) /
                                 (getNumOfEpochs() * (getNumOfEpochs() - 1)),
                             accuracy);
  setUpdatesEnabled(this->chart_series);
}

void MainWindow::MSEUpdated(int epoch, float mse) {
  this->mse_values.push_back(mse);
  if (epoch == 1)
    this->mse_series->append(0, mse * 1.2);
  this->mse_series->append(epoch, mse);
  this->mse_y->setMax(*std::max_element(mse_values.begin(), mse_values.end()) * 1.25);
}

void MainWindow::TrainingFinished() {
  ui->test_model_push_button_2->setEnabled(true);
}
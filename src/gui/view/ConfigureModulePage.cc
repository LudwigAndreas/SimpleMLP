#include <QChart>
#include <QChartView>
#include <QLineSeries>

#include "gui/utils/const.h"
#include "gui/view/mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::onStartConfigurePage() {
    ui->file_path_label->clear();
    ui->import_model_config_label->clear();
    ui->import_model_config_label->setText(
        "<html><head/><body><p><span style=\" font-size:18pt;\">"
        "Drag and drop model config file"
        "</span></p><p><span style=\" font-size:18pt;\">"
        " (should be *.mlpmodel)</span></p></body></html>");
    ui->train_model_push_button->setEnabled(true);
    ui->test_model_push_button->setDisabled(true);
    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::on_train_model_push_button_pressed() {
    if (ui->tabWidget->currentIndex() == 0) {
        if (ui->lr_double_spin_box->value() > 0.1) {
            auto ms = QMessageBox::warning(
                          this, tr("Critical Message"),
                          "The value of the learning rate is too "
                          "high, it is not guaranteed that "
                          "the learning will go as planned. Do you want to continue?",
                          QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No);
            if (ms != QMessageBox::Yes) return;
        }
        emit ModelConfigured();
    } else if (ui->tabWidget->currentIndex() == 1 &&
               !ui->file_path_label->text().isEmpty()) {
        emit ModelImported(model_config_file);
    } else {
        QMessageBox::information(this, tr("Unable to create model"),
                                 "There is no configured model");
        return;
    }
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_test_model_push_button_pressed() {
    if (this->model_config_file != nullptr) {
        if (ui->tabWidget->currentIndex() == 1 &&
                !ui->file_path_label->text().isEmpty()) {
            emit ModelImported(model_config_file);
            ui->stackedWidget->setCurrentIndex(2);
        }
    }
}

void MainWindow::on_tabWidget_currentChanged(int index) {
    if (this->model_config_file && index == 1) {
        ui->test_model_push_button->setEnabled(true);
    } else {
        ui->test_model_push_button->setEnabled(false);
    }
}

void MainWindow::modelConfigFileWasUploaded(QFile *file) {
    if (!file->fileName().endsWith(".mlpmodel"))
        QMessageBox::information(
            this, tr("Wrong file format"),
            "Incorrect file format. The file must have the .mlpmodel extension ");
    else {
        if (this->model_config_file != nullptr) {
            delete this->model_config_file;
            this->model_config_file = nullptr;
        }
        this->model_config_file = file;
        QFileInfo fileInfo(file->fileName());
        ui->file_path_label->setText(fileInfo.fileName());
        ui->test_model_push_button->setEnabled(true);
        ui->import_model_config_label->setPixmap(
            QPixmap(s21::constant::empty_file_icon_path.c_str()).scaled(150, 150));
    }
}

void MainWindow::OnModelConfigWasUploaded() {
    modelConfigFileWasUploaded(ui->import_model_config_label->getUploadedFile());
}

void MainWindow::on_toolButton_pressed() {
    QString file_path = QFileDialog::getOpenFileName(this, "Get Any File");
    QDir d = QFileInfo(file_path).absoluteFilePath();
    auto *file = new QFile(d.absolutePath());
    if (!file->open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
                                 file->errorString());
        delete file;
        return;
    } else {
        modelConfigFileWasUploaded(file);
    }
}
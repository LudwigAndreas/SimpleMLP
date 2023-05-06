#include "testdatainfodialog.h"

#include <sstream>

#include "ui_testdatainfodialog.h"

TestDataInfoDialog::TestDataInfoDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::TestDataInfoDialog) {
  ui->setupUi(this);
  setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

TestDataInfoDialog::~TestDataInfoDialog() { delete ui; }

void TestDataInfoDialog::SetModelMetrics(int size, float recall,
                                         float precision, float accuracy,
                                         float time) {
  this->recall = recall;
  this->precision = precision;
  this->accuracy = accuracy;
  this->size = size;
  this->time = time;
}

void TestDataInfoDialog::on_pushButton_pressed() { this->close(); }

void TestDataInfoDialog::showEvent(QShowEvent *event) {
  QDialog::showEvent(event);

  std::stringstream ss;
  ss << "Size: " << this->size << " images";
  ui->size_label->setText(ss.str().data());
  ss.str(std::string());
  ss << "Average accuracy: " << this->accuracy << "%";
  ui->avg_accuracy_label->setText(ss.str().data());
  ss.str(std::string());
  ss << "Precision: " << this->precision << "%";
  ui->precision_label->setText(ss.str().data());
  ss.str(std::string());
  ss << "Recall: " << this->recall << "%";
  ui->recall_label->setText(ss.str().data());
  ss.str(std::string());
  float f_measure =
      (2 * this->recall * this->precision) / (this->precision + this->recall);
  ss << "f-measure: " << f_measure << "%";
  ui->f_measure_label->setText(ss.str().data());
  ss.str(std::string());
  ss << "Time: " << time << "s";
  ui->time_label->setText(ss.str().data());
}

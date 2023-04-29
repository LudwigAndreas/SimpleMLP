#include "testdatainfodialog.h"
#include "ui_testdatainfodialog.h"

#include "sstream"

TestDataInfoDialog::TestDataInfoDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::TestDataInfoDialog) {
  ui->setupUi(this);
  setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

TestDataInfoDialog::~TestDataInfoDialog() { delete ui; }

void TestDataInfoDialog::SetModelMetrics(int size, float recall, float precision, float accuracy) {
  this->recall = recall;
  this->precision = precision;
  this->accuracy = accuracy;
  this->size = size;
}

void TestDataInfoDialog::on_pushButton_pressed() { this->close(); }

void TestDataInfoDialog::showEvent(QShowEvent *event) {
  QDialog::showEvent(event);

  std::stringstream ss;

//  if (result != nullptr) {
//    int size = calculate_size(result);
//    ss << "Size: " << size << " images";
//    ui->size_label->setText(ss.str().data());
//    ss.str(std::string());
//    float average_accuracy = calculate_accuracy(result, size);
//    ss << "Average accuracy: " << average_accuracy << "%";
//    ui->avg_accuracy_label->setText(ss.str().data());
//    ss.str(std::string());
//    float precision = calculate_precision(result, size);
//    ss << "Precision: " << precision << "%";
//    ui->precision_label->setText(ss.str().data());
//    ss.str(std::string());
//    float recall = calculate_recall(result, size);
//    ss << "Recall: " << recall << "%";
//    ui->recall_label->setText(ss.str().data());
//    ss.str(std::string());
//    float f_measure = (2 * recall * precision) / (precision + recall);
//    ss << "f-measure: " << f_measure << "%";
//    ui->f_measure_label->setText(ss.str().data());
//    ss.str(std::string());
//  }
}

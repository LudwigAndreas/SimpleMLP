#include "testdatainfodialog.h"
#include "ui_testdatainfodialog.h"

#include "sstream"

TestDataInfoDialog::TestDataInfoDialog(QWidget *parent) : QDialog(parent),
                                                          ui(new Ui::TestDataInfoDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	this->result = nullptr;
}

TestDataInfoDialog::~TestDataInfoDialog()
{
    delete ui;
}

void TestDataInfoDialog::setConfusionMatrix(std::vector<s21::ConfusionMatrix> *result) {
	this->result = result;
}

void TestDataInfoDialog::on_pushButton_pressed()
{
    this->close();
}

float calculate_recall(std::vector<s21::ConfusionMatrix> *result, int size) {
	float recall = 0;
	for (auto & i : *result) {
		if (i.tp + i.fn != 0)
			recall += (float) (i.tp * (i.tp + i.fn)) / (i.tp + i.fn);
	}
	return ((float) recall / size) * 100;
}

float calculate_precision(std::vector<s21::ConfusionMatrix> *result, int size) {
	float precision = 0;
	for (auto & i : *result) {
		if (i.tp + i.fp != 0)
			precision += (float) (i.tp * (i.tp + i.fn)) / (i.tp + i.fp);
	}
	return ((float) precision / size) * 100;
}

float calculate_accuracy(std::vector<s21::ConfusionMatrix> *result, int size) {
	int tp = 0;
	int tn = 0;
	for (auto conf_matrix : *result) {
		tp += conf_matrix.tp;
		tn += conf_matrix.tn;
	}
	return ((float) (tp + tn) / (size * result->size())) * 100;
}

int calculate_size(std::vector<s21::ConfusionMatrix> *result) {
	if (result != nullptr && result->size() > 1) {
		int size = 0;
		size += result[0].data()->tp;
		size += result[0].data()->fp;
		size += result[0].data()->tn;
		size += result[0].data()->fn;
		return size;
	}
	return -1; //TODO exception
}

void TestDataInfoDialog::showEvent(QShowEvent *event) {
	QDialog::showEvent(event);

	std::stringstream ss;

	if (result != nullptr) {
		int size = calculate_size(result);
		ss << "Size: " << size << " images";
		ui->size_label->setText(ss.str().data());
		ss.str(std::string());
		float average_accuracy = calculate_accuracy(result, size);
		ss << "Average accuracy: " << average_accuracy << "%";
		ui->avg_accuracy_label->setText(ss.str().data());
		ss.str(std::string());
		float precision = calculate_precision(result, size);
		ss << "Precision: " << precision << "%";
		ui->precision_label->setText(ss.str().data());
		ss.str(std::string());
		float recall = calculate_recall(result, size);
		ss << "Recall: " << recall << "%";
		ui->recall_label->setText(ss.str().data());
		ss.str(std::string());
		float f_measure = (2 * recall * precision) / (precision + recall);
		ss << "f-measure: " << f_measure << "%";
		ui->f_measure_label->setText(ss.str().data());
		ss.str(std::string());
	}
}

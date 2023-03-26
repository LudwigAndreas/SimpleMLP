#ifndef TESTDATAINFODIALOG_H
#define TESTDATAINFODIALOG_H

#include <QDialog>

#include "src/core/utils/ConfusionMatrix.hpp"

namespace Ui {
class TestDataInfoDialog;
}

class TestDataInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestDataInfoDialog(QWidget *parent = nullptr);
    ~TestDataInfoDialog();

	void setConfusionMatrix(std::vector<s21::ConfusionMatrix> *result);

protected:
	void showEvent(QShowEvent *event) override;

private slots:
    void on_pushButton_pressed();

private:
    Ui::TestDataInfoDialog *ui;
	std::vector<s21::ConfusionMatrix> *result;
};

#endif // TESTDATAINFODIALOG_H

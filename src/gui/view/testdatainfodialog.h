#ifndef TESTDATAINFODIALOG_H
#define TESTDATAINFODIALOG_H

#include <QDialog>

#include "core/utils/ConfusionMatrix.h"

namespace Ui {
class TestDataInfoDialog;
}

class TestDataInfoDialog : public QDialog {
    Q_OBJECT

public:
    explicit TestDataInfoDialog(QWidget *parent = nullptr);
    ~TestDataInfoDialog();

    void SetModelMetrics(int size, float recall, float precision, float accuracy, float time);

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_pushButton_pressed();
//  void DataWasObtained();

private:
    Ui::TestDataInfoDialog *ui;
    float recall;
    float precision;
    float accuracy;
    float time;
    int size;
};

#endif // TESTDATAINFODIALOG_H

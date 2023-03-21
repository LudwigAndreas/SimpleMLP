#ifndef TESTDATAINFODIALOG_H
#define TESTDATAINFODIALOG_H

#include <QDialog>

namespace Ui {
class TestDataInfoDialog;
}

class TestDataInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestDataInfoDialog(QWidget *parent = nullptr);
    ~TestDataInfoDialog();

private slots:
    void on_pushButton_pressed();

private:
    Ui::TestDataInfoDialog *ui;
};

#endif // TESTDATAINFODIALOG_H

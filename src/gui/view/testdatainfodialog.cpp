#include "testdatainfodialog.h"
#include "ui_testdatainfodialog.h"

TestDataInfoDialog::TestDataInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestDataInfoDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

TestDataInfoDialog::~TestDataInfoDialog()
{
    delete ui;
}

void TestDataInfoDialog::on_pushButton_pressed()
{
    this->close();
}


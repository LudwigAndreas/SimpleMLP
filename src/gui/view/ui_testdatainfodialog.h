/********************************************************************************
** Form generated from reading UI file 'testdatainfodialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTDATAINFODIALOG_H
#define UI_TESTDATAINFODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestDataInfoDialog {
public:
  QPushButton *pushButton;
  QWidget *gridLayoutWidget;
  QGridLayout *gridLayout;
  QLabel *avg_accuracy_label;
  QLabel *time_label;
  QLabel *f_measure_label;
  QLabel *recall_label;
  QLabel *size_label;
  QLabel *precision_label;
  QLabel *label_5;

  void setupUi(QDialog *TestDataInfoDialog) {
    if (TestDataInfoDialog->objectName().isEmpty())
      TestDataInfoDialog->setObjectName("TestDataInfoDialog");
    TestDataInfoDialog->resize(650, 300);
    TestDataInfoDialog->setMinimumSize(QSize(650, 300));
    TestDataInfoDialog->setMaximumSize(QSize(650, 300));
    TestDataInfoDialog->setModal(true);
    pushButton = new QPushButton(TestDataInfoDialog);
    pushButton->setObjectName("pushButton");
    pushButton->setGeometry(QRect(280, 270, 100, 32));
    gridLayoutWidget = new QWidget(TestDataInfoDialog);
    gridLayoutWidget->setObjectName("gridLayoutWidget");
    gridLayoutWidget->setGeometry(QRect(20, 10, 311, 241));
    gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setObjectName("gridLayout");
    gridLayout->setContentsMargins(0, 0, 0, 0);
    avg_accuracy_label = new QLabel(gridLayoutWidget);
    avg_accuracy_label->setObjectName("avg_accuracy_label");
    avg_accuracy_label->setAlignment(Qt::AlignCenter);

    gridLayout->addWidget(avg_accuracy_label, 1, 0, 1, 1);

    time_label = new QLabel(gridLayoutWidget);
    time_label->setObjectName("time_label");
    time_label->setAlignment(Qt::AlignCenter);

    gridLayout->addWidget(time_label, 5, 0, 1, 1);

    f_measure_label = new QLabel(gridLayoutWidget);
    f_measure_label->setObjectName("f_measure_label");
    f_measure_label->setAlignment(Qt::AlignCenter);

    gridLayout->addWidget(f_measure_label, 4, 0, 1, 1);

    recall_label = new QLabel(gridLayoutWidget);
    recall_label->setObjectName("recall_label");
    recall_label->setAlignment(Qt::AlignCenter);

    gridLayout->addWidget(recall_label, 3, 0, 1, 1);

    size_label = new QLabel(gridLayoutWidget);
    size_label->setObjectName("size_label");
    size_label->setAlignment(Qt::AlignCenter);

    gridLayout->addWidget(size_label, 0, 0, 1, 1);

    precision_label = new QLabel(gridLayoutWidget);
    precision_label->setObjectName("precision_label");
    precision_label->setAlignment(Qt::AlignCenter);

    gridLayout->addWidget(precision_label, 2, 0, 1, 1);

    label_5 = new QLabel(TestDataInfoDialog);
    label_5->setObjectName("label_5");
    label_5->setGeometry(QRect(370, 10, 240, 240));
    label_5->setPixmap(QPixmap(QString::fromUtf8(
        "../Desktop/\320\241\320\275\320\270\320\274\320\276\320\272 "
        "\321\215\320\272\321\200\320\260\320\275\320\260 2023-02-04 \320\262 "
        "01.45.54.png")));
    label_5->setScaledContents(true);
    label_5->setAlignment(Qt::AlignCenter);

    retranslateUi(TestDataInfoDialog);

    QMetaObject::connectSlotsByName(TestDataInfoDialog);
  } // setupUi

  void retranslateUi(QDialog *TestDataInfoDialog) {
    TestDataInfoDialog->setWindowTitle(
        QCoreApplication::translate("TestDataInfoDialog", "Dialog", nullptr));
    pushButton->setText(
        QCoreApplication::translate("TestDataInfoDialog", "Ok", nullptr));
    avg_accuracy_label->setText(QCoreApplication::translate(
        "TestDataInfoDialog", "Average accuracy: 0%", nullptr));
    time_label->setText(QCoreApplication::translate("TestDataInfoDialog",
                                                    "Time: 0ms", nullptr));
    f_measure_label->setText(QCoreApplication::translate(
        "TestDataInfoDialog", "f-measure: 0%", nullptr));
    recall_label->setText(QCoreApplication::translate("TestDataInfoDialog",
                                                      "Recall: 0%", nullptr));
    size_label->setText(QCoreApplication::translate("TestDataInfoDialog",
                                                    "Size: 0 images", nullptr));
    precision_label->setText(QCoreApplication::translate(
        "TestDataInfoDialog", "Precision: 0%", nullptr));
    label_5->setText(QString());
  } // retranslateUi
};

namespace Ui {
class TestDataInfoDialog : public Ui_TestDataInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTDATAINFODIALOG_H

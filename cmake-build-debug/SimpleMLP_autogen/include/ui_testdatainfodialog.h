/********************************************************************************
** Form generated from reading UI file 'testdatainfodialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
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

class Ui_TestDataInfoDialog
{
public:
    QPushButton *pushButton;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label_8;
    QLabel *label_5;

    void setupUi(QDialog *TestDataInfoDialog)
    {
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
        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName("label_7");
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_7, 5, 0, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName("label_6");
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName("label_4");
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName("label_8");
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_8, 6, 0, 1, 1);

        label_5 = new QLabel(TestDataInfoDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(370, 10, 240, 240));
        label_5->setPixmap(QPixmap(QString::fromUtf8("../Desktop/\320\241\320\275\320\270\320\274\320\276\320\272 \321\215\320\272\321\200\320\260\320\275\320\260 2023-02-04 \320\262 01.45.54.png")));
        label_5->setScaledContents(true);
        label_5->setAlignment(Qt::AlignCenter);

        retranslateUi(TestDataInfoDialog);

        QMetaObject::connectSlotsByName(TestDataInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *TestDataInfoDialog)
    {
        TestDataInfoDialog->setWindowTitle(QCoreApplication::translate("TestDataInfoDialog", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("TestDataInfoDialog", "Ok", nullptr));
        label_3->setText(QCoreApplication::translate("TestDataInfoDialog", "Loss: 0%", nullptr));
        label->setText(QCoreApplication::translate("TestDataInfoDialog", "Accuracy: 0%", nullptr));
        label_7->setText(QCoreApplication::translate("TestDataInfoDialog", "ROC-AUC: 0%", nullptr));
        label_6->setText(QCoreApplication::translate("TestDataInfoDialog", "Recall: 0%", nullptr));
        label_4->setText(QCoreApplication::translate("TestDataInfoDialog", "Precision: 0%", nullptr));
        label_2->setText(QCoreApplication::translate("TestDataInfoDialog", "Size: 0 images", nullptr));
        label_8->setText(QCoreApplication::translate("TestDataInfoDialog", "Logistic loss: 0%", nullptr));
        label_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TestDataInfoDialog: public Ui_TestDataInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTDATAINFODIALOG_H

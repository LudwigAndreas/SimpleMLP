/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "src/gui/importfileitem.h"
#include "src/gui/paintview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionImport;
    QAction *actionExport;
    QAction *actionAbout;
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *set_model_page;
    QLabel *label_2;
    QLabel *label;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label_4;
    QComboBox *comboBox_2;
    QComboBox *comboBox;
    QComboBox *comboBox_3;
    QLabel *label_5;
    QLabel *label_6;
    QWidget *tab_2;
    QGroupBox *groupBox;
    ImportFileItem *import_model_config_label;
    QToolButton *toolButton;
    QLabel *file_path_label;
    QPushButton *test_model_push_button;
    QPushButton *train_model_push_button;
    QWidget *train_model_page;
    QLabel *label_8;
    QLabel *label_9;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_3;
    ImportFileItem *import_train_dataset_label;
    QPushButton *start_training_push_button;
    QLabel *file_path_label_2;
    QToolButton *toolButton_3;
    QProgressBar *training_progress_bar;
    QLabel *label_11;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *label_10;
    QLabel *label_14;
    QSpinBox *spinBox_3;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QLabel *label_15;
    QPushButton *test_model_push_button_2;
    QPushButton *back_to_configure_push_button;
    QWidget *use_model_page;
    QLabel *label_13;
    QLabel *label_23;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    PaintView *paint_view;
    QGroupBox *groupBox_8;
    QPushButton *pushButton;
    QWidget *tab_4;
    ImportFileItem *import_test_dataset_label;
    QGroupBox *groupBox_9;
    QPushButton *predict_push_button;
    QToolButton *toolButton_4;
    QLabel *file_path_label_3;
    QLabel *label_7;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QSlider *testing_size_horizontalSlider;
    QLabel *testing_size_label;
    QLabel *label_12;
    QPushButton *back_to_configure_push_button_2;
    QPushButton *back_to_configure_push_button_3;
    QPushButton *back_to_configure_push_button_4;
    QMenuBar *menubar;
    QMenu *menuSimpleMLP;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 520);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(800, 520));
        MainWindow->setMaximumSize(QSize(800, 520));
        MainWindow->setToolButtonStyle(Qt::ToolButtonIconOnly);
        MainWindow->setAnimated(true);
        MainWindow->setDocumentMode(false);
        actionImport = new QAction(MainWindow);
        actionImport->setObjectName("actionImport");
        actionExport = new QAction(MainWindow);
        actionExport->setObjectName("actionExport");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(-1, 0, 801, 501));
        stackedWidget->setAutoFillBackground(false);
        set_model_page = new QWidget();
        set_model_page->setObjectName("set_model_page");
        label_2 = new QLabel(set_model_page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 10, 58, 61));
        label_2->setTextFormat(Qt::AutoText);
        label_2->setScaledContents(false);
        label = new QLabel(set_model_page);
        label->setObjectName("label");
        label->setGeometry(QRect(100, 20, 671, 41));
        label->setWordWrap(true);
        verticalLayoutWidget = new QWidget(set_model_page);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(30, 80, 751, 351));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(verticalLayoutWidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setAcceptDrops(true);
        tab = new QWidget();
        tab->setObjectName("tab");
        gridLayoutWidget = new QWidget(tab);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(10, 60, 361, 181));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 0, 1, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 1, 1, 1, 1);

        comboBox_2 = new QComboBox(gridLayoutWidget);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");

        gridLayout->addWidget(comboBox_2, 1, 0, 1, 1);

        comboBox = new QComboBox(gridLayoutWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(comboBox, 0, 0, 1, 1);

        comboBox_3 = new QComboBox(gridLayoutWidget);
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName("comboBox_3");
        comboBox_3->setEnabled(false);

        gridLayout->addWidget(comboBox_3, 2, 0, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 2, 1, 1, 1);

        label_6 = new QLabel(tab);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(390, 60, 341, 181));
        label_6->setWordWrap(true);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 10, 721, 231));
        import_model_config_label = new ImportFileItem(groupBox);
        import_model_config_label->setObjectName("import_model_config_label");
        import_model_config_label->setEnabled(true);
        import_model_config_label->setGeometry(QRect(0, 0, 721, 231));
        import_model_config_label->setMinimumSize(QSize(10, 10));
        import_model_config_label->setCursor(QCursor(Qt::ArrowCursor));
        import_model_config_label->setAcceptDrops(true);
        import_model_config_label->setFrameShape(QFrame::NoFrame);
        import_model_config_label->setFrameShadow(QFrame::Raised);
        import_model_config_label->setScaledContents(false);
        import_model_config_label->setAlignment(Qt::AlignCenter);
        import_model_config_label->setIndent(-1);
        toolButton = new QToolButton(tab_2);
        toolButton->setObjectName("toolButton");
        toolButton->setGeometry(QRect(630, 250, 101, 22));
        file_path_label = new QLabel(tab_2);
        file_path_label->setObjectName("file_path_label");
        file_path_label->setEnabled(true);
        file_path_label->setGeometry(QRect(10, 250, 611, 20));
        tabWidget->addTab(tab_2, QString());

        verticalLayout_2->addWidget(tabWidget);

        test_model_push_button = new QPushButton(set_model_page);
        test_model_push_button->setObjectName("test_model_push_button");
        test_model_push_button->setEnabled(false);
        test_model_push_button->setGeometry(QRect(650, 440, 131, 32));
        train_model_push_button = new QPushButton(set_model_page);
        train_model_push_button->setObjectName("train_model_push_button");
        train_model_push_button->setGeometry(QRect(510, 440, 131, 32));
        stackedWidget->addWidget(set_model_page);
        train_model_page = new QWidget();
        train_model_page->setObjectName("train_model_page");
        label_8 = new QLabel(train_model_page);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(30, 10, 58, 61));
        label_8->setTextFormat(Qt::AutoText);
        label_8->setScaledContents(false);
        label_9 = new QLabel(train_model_page);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(100, 20, 671, 41));
        label_9->setWordWrap(true);
        verticalLayoutWidget_2 = new QWidget(train_model_page);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(30, 80, 751, 351));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(verticalLayoutWidget_2);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(10, 20, 351, 191));
        groupBox_3->setAcceptDrops(false);
        groupBox_3->setAutoFillBackground(true);
        groupBox_3->setFlat(false);
        import_train_dataset_label = new ImportFileItem(groupBox_3);
        import_train_dataset_label->setObjectName("import_train_dataset_label");
        import_train_dataset_label->setEnabled(true);
        import_train_dataset_label->setGeometry(QRect(0, 0, 351, 191));
        import_train_dataset_label->setMinimumSize(QSize(10, 10));
        import_train_dataset_label->setCursor(QCursor(Qt::ArrowCursor));
        import_train_dataset_label->setAcceptDrops(true);
        import_train_dataset_label->setAutoFillBackground(false);
        import_train_dataset_label->setFrameShape(QFrame::NoFrame);
        import_train_dataset_label->setFrameShadow(QFrame::Raised);
        import_train_dataset_label->setScaledContents(false);
        import_train_dataset_label->setAlignment(Qt::AlignCenter);
        import_train_dataset_label->setIndent(-1);
        start_training_push_button = new QPushButton(groupBox_2);
        start_training_push_button->setObjectName("start_training_push_button");
        start_training_push_button->setEnabled(false);
        start_training_push_button->setGeometry(QRect(300, 310, 131, 32));
        file_path_label_2 = new QLabel(groupBox_2);
        file_path_label_2->setObjectName("file_path_label_2");
        file_path_label_2->setEnabled(true);
        file_path_label_2->setGeometry(QRect(20, 280, 241, 20));
        toolButton_3 = new QToolButton(groupBox_2);
        toolButton_3->setObjectName("toolButton_3");
        toolButton_3->setGeometry(QRect(260, 220, 101, 22));
        training_progress_bar = new QProgressBar(groupBox_2);
        training_progress_bar->setObjectName("training_progress_bar");
        training_progress_bar->setGeometry(QRect(60, 310, 621, 31));
        training_progress_bar->setValue(24);
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(390, 20, 351, 20));
        label_11->setAlignment(Qt::AlignCenter);
        gridLayoutWidget_2 = new QWidget(groupBox_2);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(410, 50, 311, 161));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(gridLayoutWidget_2);
        label_10->setObjectName("label_10");

        gridLayout_2->addWidget(label_10, 0, 1, 1, 1);

        label_14 = new QLabel(gridLayoutWidget_2);
        label_14->setObjectName("label_14");
        label_14->setWordWrap(true);

        gridLayout_2->addWidget(label_14, 1, 1, 1, 1);

        spinBox_3 = new QSpinBox(gridLayoutWidget_2);
        spinBox_3->setObjectName("spinBox_3");

        gridLayout_2->addWidget(spinBox_3, 2, 0, 1, 1);

        spinBox = new QSpinBox(gridLayoutWidget_2);
        spinBox->setObjectName("spinBox");

        gridLayout_2->addWidget(spinBox, 0, 0, 1, 1);

        spinBox_2 = new QSpinBox(gridLayoutWidget_2);
        spinBox_2->setObjectName("spinBox_2");

        gridLayout_2->addWidget(spinBox_2, 1, 0, 1, 1);

        label_15 = new QLabel(gridLayoutWidget_2);
        label_15->setObjectName("label_15");
        label_15->setScaledContents(false);
        label_15->setWordWrap(true);

        gridLayout_2->addWidget(label_15, 2, 1, 1, 1);


        verticalLayout_3->addWidget(groupBox_2);

        test_model_push_button_2 = new QPushButton(train_model_page);
        test_model_push_button_2->setObjectName("test_model_push_button_2");
        test_model_push_button_2->setEnabled(false);
        test_model_push_button_2->setGeometry(QRect(650, 440, 131, 32));
        back_to_configure_push_button = new QPushButton(train_model_page);
        back_to_configure_push_button->setObjectName("back_to_configure_push_button");
        back_to_configure_push_button->setEnabled(true);
        back_to_configure_push_button->setGeometry(QRect(510, 440, 131, 32));
        stackedWidget->addWidget(train_model_page);
        use_model_page = new QWidget();
        use_model_page->setObjectName("use_model_page");
        label_13 = new QLabel(use_model_page);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(30, 10, 58, 61));
        label_13->setTextFormat(Qt::AutoText);
        label_13->setScaledContents(false);
        label_23 = new QLabel(use_model_page);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(100, 20, 671, 51));
        label_23->setWordWrap(true);
        horizontalLayoutWidget_4 = new QWidget(use_model_page);
        horizontalLayoutWidget_4->setObjectName("horizontalLayoutWidget_4");
        horizontalLayoutWidget_4->setGeometry(QRect(30, 80, 751, 351));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        tabWidget_2 = new QTabWidget(horizontalLayoutWidget_4);
        tabWidget_2->setObjectName("tabWidget_2");
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        paint_view = new PaintView(tab_3);
        paint_view->setObjectName("paint_view");
        paint_view->setGeometry(QRect(70, 10, 271, 271));
        paint_view->setAcceptDrops(true);
        paint_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        paint_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        QBrush brush(QColor(255, 17, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        paint_view->setForegroundBrush(brush);
        groupBox_8 = new QGroupBox(tab_3);
        groupBox_8->setObjectName("groupBox_8");
        groupBox_8->setGeometry(QRect(399, 10, 271, 271));
        pushButton = new QPushButton(tab_3);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(250, 290, 100, 32));
        tabWidget_2->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        import_test_dataset_label = new ImportFileItem(tab_4);
        import_test_dataset_label->setObjectName("import_test_dataset_label");
        import_test_dataset_label->setEnabled(true);
        import_test_dataset_label->setGeometry(QRect(10, 10, 351, 191));
        import_test_dataset_label->setMinimumSize(QSize(10, 10));
        import_test_dataset_label->setCursor(QCursor(Qt::ArrowCursor));
        import_test_dataset_label->setAcceptDrops(true);
        import_test_dataset_label->setFrameShape(QFrame::NoFrame);
        import_test_dataset_label->setFrameShadow(QFrame::Raised);
        import_test_dataset_label->setScaledContents(false);
        import_test_dataset_label->setAlignment(Qt::AlignCenter);
        import_test_dataset_label->setIndent(-1);
        groupBox_9 = new QGroupBox(tab_4);
        groupBox_9->setObjectName("groupBox_9");
        groupBox_9->setGeometry(QRect(10, 10, 351, 191));
        predict_push_button = new QPushButton(tab_4);
        predict_push_button->setObjectName("predict_push_button");
        predict_push_button->setEnabled(false);
        predict_push_button->setGeometry(QRect(310, 290, 131, 32));
        toolButton_4 = new QToolButton(tab_4);
        toolButton_4->setObjectName("toolButton_4");
        toolButton_4->setGeometry(QRect(260, 210, 101, 22));
        file_path_label_3 = new QLabel(tab_4);
        file_path_label_3->setObjectName("file_path_label_3");
        file_path_label_3->setEnabled(true);
        file_path_label_3->setGeometry(QRect(10, 250, 611, 20));
        label_7 = new QLabel(tab_4);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(387, 10, 351, 20));
        label_7->setAlignment(Qt::AlignCenter);
        horizontalLayoutWidget_2 = new QWidget(tab_4);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(410, 40, 311, 51));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        testing_size_horizontalSlider = new QSlider(horizontalLayoutWidget_2);
        testing_size_horizontalSlider->setObjectName("testing_size_horizontalSlider");
        testing_size_horizontalSlider->setValue(50);
        testing_size_horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(testing_size_horizontalSlider);

        testing_size_label = new QLabel(horizontalLayoutWidget_2);
        testing_size_label->setObjectName("testing_size_label");
        testing_size_label->setMinimumSize(QSize(30, 0));
        testing_size_label->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_2->addWidget(testing_size_label);

        label_12 = new QLabel(horizontalLayoutWidget_2);
        label_12->setObjectName("label_12");

        horizontalLayout_2->addWidget(label_12);

        tabWidget_2->addTab(tab_4, QString());
        groupBox_9->raise();
        import_test_dataset_label->raise();
        predict_push_button->raise();
        toolButton_4->raise();
        file_path_label_3->raise();
        label_7->raise();
        horizontalLayoutWidget_2->raise();

        horizontalLayout_4->addWidget(tabWidget_2);

        back_to_configure_push_button_2 = new QPushButton(use_model_page);
        back_to_configure_push_button_2->setObjectName("back_to_configure_push_button_2");
        back_to_configure_push_button_2->setEnabled(true);
        back_to_configure_push_button_2->setGeometry(QRect(510, 440, 131, 32));
        back_to_configure_push_button_3 = new QPushButton(use_model_page);
        back_to_configure_push_button_3->setObjectName("back_to_configure_push_button_3");
        back_to_configure_push_button_3->setEnabled(true);
        back_to_configure_push_button_3->setGeometry(QRect(650, 440, 131, 32));
        back_to_configure_push_button_4 = new QPushButton(use_model_page);
        back_to_configure_push_button_4->setObjectName("back_to_configure_push_button_4");
        back_to_configure_push_button_4->setEnabled(true);
        back_to_configure_push_button_4->setGeometry(QRect(30, 440, 131, 32));
        stackedWidget->addWidget(use_model_page);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        menuSimpleMLP = new QMenu(menubar);
        menuSimpleMLP->setObjectName("menuSimpleMLP");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuSimpleMLP->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);
        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "SimpleMLP", nullptr));
        actionImport->setText(QCoreApplication::translate("MainWindow", "Import", nullptr));
        actionExport->setText(QCoreApplication::translate("MainWindow", "Export", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-family:'Segoe UI Emoji'; font-size:49px; color:#333333;\">\360\237\244\226</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "In this panel you can configure model properties or load pretrained one. ", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Number of hidden layers", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Perceptron implementation", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "Matrix", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "Graph", nullptr));

        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "2", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "3", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "4", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "5", nullptr));

        comboBox_3->setItemText(0, QCoreApplication::translate("MainWindow", "Sigmoid", nullptr));

        label_5->setText(QCoreApplication::translate("MainWindow", "Activation function", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "The Perceptron algorithm is a two-class (binary) classification machine learning algorithm.\n"
"\n"
"It is a type of neural network model, perhaps the simplest type of neural network model.\n"
"\n"
"It consists of a single node or neuron that takes a row of data as input and predicts a class label. This is achieved by calculating the weighted sum of the inputs and a bias (set to 1). The weighted sum of the input of the model is called the activation.", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Configure", nullptr));
        groupBox->setTitle(QString());
        import_model_config_label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">Drag and drop model config file</span></p><p><span style=\" font-size:18pt;\"> (should be *.mlpmodel)</span></p></body></html>", nullptr));
        toolButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        file_path_label->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Load", nullptr));
        test_model_push_button->setText(QCoreApplication::translate("MainWindow", "Test model", nullptr));
        train_model_push_button->setText(QCoreApplication::translate("MainWindow", "Train model", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-family:'Segoe UI Emoji'; font-size:49px; color:#333333;\">\360\237\247\221\342\200\215\360\237\217\253</span></p></body></html>", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "In this panel you can train your model on your dataset. You can track your dataset file to d&d field or choose existing dataset file from datasets folder. Train dataset file should be with .csv extention.", nullptr));
        groupBox_2->setTitle(QString());
        groupBox_3->setTitle(QString());
        import_train_dataset_label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">Drag and drop train dataset file</span></p><p><span style=\" font-size:18pt;\"> (should be *.csv)</span></p></body></html>", nullptr));
        start_training_push_button->setText(QCoreApplication::translate("MainWindow", "Start training", nullptr));
        file_path_label_2->setText(QString());
        toolButton_3->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Train settings</span></p></body></html>", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Number of epochs", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Number of cross-validation groups", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Autosave progress every number of epochs", nullptr));
        test_model_push_button_2->setText(QCoreApplication::translate("MainWindow", "Test model", nullptr));
        back_to_configure_push_button->setText(QCoreApplication::translate("MainWindow", "Config model", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-family:'Segoe UI Emoji'; font-size:49px; color:#333333;\">\360\237\224\256</span></p></body></html>", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "In this panel you can draw symbol and neural network will try to guess it or you can upload test dataset to model and it will create report with some accuracy statistics. Test dataset file should be with .csv extention. You can drag and drop .bmp file into paint field.", nullptr));
        groupBox_8->setTitle(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Paint", nullptr));
        import_test_dataset_label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">Drag and drop test dataset file</span></p><p><span style=\" font-size:18pt;\"> (should be *.csv)</span></p></body></html>", nullptr));
        groupBox_9->setTitle(QString());
        predict_push_button->setText(QCoreApplication::translate("MainWindow", "Predict", nullptr));
        toolButton_4->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        file_path_label_3->setText(QString());
        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Test settings</span></p></body></html>", nullptr));
        testing_size_label->setText(QCoreApplication::translate("MainWindow", "0.5", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Part of test sample", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Upload", nullptr));
        back_to_configure_push_button_2->setText(QCoreApplication::translate("MainWindow", "Config model", nullptr));
        back_to_configure_push_button_3->setText(QCoreApplication::translate("MainWindow", "Train model", nullptr));
        back_to_configure_push_button_4->setText(QCoreApplication::translate("MainWindow", "Export model", nullptr));
        menuSimpleMLP->setTitle(QCoreApplication::translate("MainWindow", "SimpleMLP", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

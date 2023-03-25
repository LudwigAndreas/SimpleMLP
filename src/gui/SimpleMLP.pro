QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += "../../"

SOURCES += \
    main.cpp \
    utils/MTWorker.cpp \
    utils/importfileitem.cpp \
    utils/paintview.cpp \
    view/ConfigureModulePage.cpp \
    view/TestModelPage.cpp \
    view/TrainModelPage.cpp \
    view/mainwindow.cpp \
    view/testdatainfodialog.cpp \
    ../core/DatasetReading.cpp \
    ../core/LetterRecognitionMlpModelBuilder.cpp \
    ../core/graph/MLPGraphLayer.cpp \
    ../core/graph/MLPGraphModel.cpp \
    ../core/utils/ActivationFunction.cpp \
    ../core/utils/BMPReader.cpp

HEADERS += \
    utils/importfileitem.h \
    view/mainwindow.h \
    utils/paintview.h \
    view/testdatainfodialog.h

FORMS += \
    view/mainwindow.ui \
    view/testdatainfodialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourses.qrc

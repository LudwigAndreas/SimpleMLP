QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/gui/utils/importfileitem.cpp \
    src/gui/main.cpp \
    src/gui/view/mainwindow.cpp \
    src/gui/utils/paintview.cpp \
    src/gui/view/testdatainfodialog.cpp

HEADERS += \
    src/gui/utils/importfileitem.h \
    src/gui/view/mainwindow.h \
    src/gui/utils/paintview.h \
    src/gui/view/testdatainfodialog.h

FORMS += \
    src/gui/view/mainwindow.ui \
    src/gui/view/testdatainfodialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourses.qrc

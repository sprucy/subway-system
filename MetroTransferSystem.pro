#-------------------------------------------------
#
# Project created by QtCreator 2017-08-03T12:33:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MetroTransferSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    about.cpp \
    main.cpp \
    mainwindow.cpp \
    graphics_view_zoom.cpp \
    addstation.cpp \
    metrograph.cpp \
    myview.cpp \
    querytransfer.cpp \
    station.cpp

HEADERS += \
    about.h \
    global.h \
    mainwindow.h \
    graphics_view_zoom.h \
    line.h \
    addstation.h \
    myview.h \
    querytransfer.h \
    station.h \
    metrograph.h

FORMS += \
    about.ui \
       mainwindow.ui \
    addstation.ui \
    querytransfer.ui

RESOURCES += \
    resource.qrc

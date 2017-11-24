#-------------------------------------------------
#
# Project created by QtCreator 2017-11-08T09:45:51
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetVideoClient
TEMPLATE = app
RC_ICONS += icon.ico


SOURCES += main.cpp\
        mainwindow.cpp \
    onevideo.cpp \
    iconbutton.cpp \
    mythread.cpp \
    configdialog.cpp \
    fullscreenvideo.cpp

HEADERS  += mainwindow.h \
    onevideo.h \
    iconbutton.h \
    mythread.h \
    configdialog.h \
    fullscreenvideo.h

FORMS    += \
    configdialog.ui

RESOURCES += \
    res.qrc

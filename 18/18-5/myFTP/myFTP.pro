#-------------------------------------------------
#
# Project created by QtCreator 2022-05-06T13:43:27
#
#-------------------------------------------------

QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myFTP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qftp.cpp \
    qurlinfo.cpp

HEADERS  += mainwindow.h \
    qftp.h \
    qurlinfo.h

FORMS    += mainwindow.ui

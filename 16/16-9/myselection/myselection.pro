#-------------------------------------------------
#
# Project created by QtCreator 2022-04-25T14:46:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myselection
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    spinboxdelegate.cpp

HEADERS  += mainwindow.h \
    spinboxdelegate.h

FORMS    += mainwindow.ui

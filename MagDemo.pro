#-------------------------------------------------
#
# Project created by QtCreator 2015-08-22T19:33:59
#
#-------------------------------------------------
cache()
QMAKE_CXXFLAGS += -Wno-deprecated
QMAKE_CXXFLAGS += -Wunknown-pragmas


QT       += core gui
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MagDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

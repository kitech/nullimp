#-------------------------------------------------
#
# Project created by QtCreator 2012-08-15T17:50:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nullimp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    vlinkocv.cpp

HEADERS  += mainwindow.h \
    vlinkocv.h

FORMS    += mainwindow.ui

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv

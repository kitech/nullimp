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
    vlinkocv.cpp \
    ./src/util.cpp \
    ../../../../../../home/gzleo/workspace1/nullimp/src/imageprocessor.cpp

HEADERS  += mainwindow.h \
    vlinkocv.h \
    ./src/util.h \
    ../../../../../../home/gzleo/workspace1/nullimp/src/imageprocessor.h

FORMS    += mainwindow.ui

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv

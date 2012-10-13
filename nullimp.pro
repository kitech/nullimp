#-------------------------------------------------
#
# Project created by QtCreator 2012-08-15T17:50:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nullimp
TEMPLATE = app
OBJECTS_DIR = ./build/.
MOC_DIR = ./build/.
UI_DIR = ./build/.

SOURCES += ./src/main.cpp\
        ./src/mainwindow.cpp \
    ./src/vlinkocv.cpp \
    ./src/util.cpp \
    ./src/simplelog.cpp \
    ./src/imageprocessor.cpp

HEADERS  += ./src/mainwindow.h \
    ./src/vlinkocv.h \
    ./src/util.h \
    ./src/simplelog.h \
    ./src/imageprocessor.h

FORMS    += uis/mainwindow.ui

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv GraphicsMagick GraphicsMagick++ GraphicsMagickWand

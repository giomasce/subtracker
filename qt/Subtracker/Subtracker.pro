#-------------------------------------------------
#
# Project created by QtCreator 2016-11-02T23:49:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Subtracker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    videowidget.cpp \
    framereader.cpp \
    logging.cpp

HEADERS  += mainwindow.h \
    videowidget.h \
    framereader.h \
    logging.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++14 -march=native -O3 -DBOOST_ALL_DYN_LINK
QMAKE_LFLAGS += -lturbojpeg -lboost_log_setup -lboost_log -lboost_system -lboost_thread

CONFIG += link_pkgconfig
PKGCONFIG += opencv
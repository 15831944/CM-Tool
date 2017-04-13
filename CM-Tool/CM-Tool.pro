#-------------------------------------------------
#
# Project created by QtCreator 2017-04-01T17:01:04
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CM-Tool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    udp/heartbeat.cpp \
    udp/datasouce.cpp \
    udp/datasent.cpp \
    udp/myudpthread.cpp

HEADERS  += mainwindow.h \
    udp/heartbeat.h \
    udp/datadefine.h \
    udp/datasouce.h \
    udp/datasent.h \
    udp/myudpthread.h

FORMS    += mainwindow.ui

#-------------------------------------------------
#
# Project created by QtCreator 2017-02-20T16:07:10
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mapping
TEMPLATE = app

CONFIG += console


SOURCES += main.cpp\
        mainwindow.cpp \
    qtspcomm.cpp \
    rplidardriver.cpp \
    configwidget.cpp

HEADERS  += mainwindow.h \
    datadef.h \
    qtspcomm.h \
    rplidardriver.h \
    configwidget.h

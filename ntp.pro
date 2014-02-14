#-------------------------------------------------
#
# Project created by QtCreator 2014-02-14T13:04:56
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ntp
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include (qntp/qntp.pri)


SOURCES += main.cpp \
    ntptest.cpp

HEADERS += \
    ntptest.h

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
    ntptest.cpp \
    param.cpp

HEADERS += \
    ntptest.h \
    param.h

DEFINES += GIT_CURRENT_SHA1="\\\"$(shell C:/Progra~2/Git/bin/git -C "$$_PRO_FILE_PWD_" describe --abbrev=4 --dirty --always --tags)\\\""

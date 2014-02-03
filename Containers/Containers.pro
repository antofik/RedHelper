#-------------------------------------------------
#
# Project created by QtCreator 2014-01-31T12:17:12
#
#-------------------------------------------------

QT       -= gui

TARGET = Containers
TEMPLATE = lib
CONFIG += staticlib

SOURCES += containers.cpp

HEADERS += containers.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

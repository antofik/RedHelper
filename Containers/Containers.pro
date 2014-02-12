#-------------------------------------------------
#
# Project created by QtCreator 2014-01-31T12:17:12
#
#-------------------------------------------------

QT       -= gui

TARGET = Containers
TEMPLATE = lib
CONFIG += staticlib c++11

SOURCES += \
    visitor.cpp \
    basenotification.cpp \
    textnotification.cpp \
    typingnotification.cpp \
    mousenotification.cpp \
    cobrowsenotification.cpp

HEADERS += containers.h \
    visitor.h \
    basenotification.h \
    textnotification.h \
    typingnotification.h \
    mousenotification.h \
    cobrowsenotification.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

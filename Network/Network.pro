#-------------------------------------------------
#
# Project created by QtCreator 2014-01-31T12:16:25
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = Network
TEMPLATE = lib
CONFIG += staticlib

SOURCES += network.cpp

HEADERS += network.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Containers/release/ -lContainers
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Containers/debug/ -lContainers
else:unix: LIBS += -L$$OUT_PWD/../Containers/ -lContainers

INCLUDEPATH += $$PWD/../Containers
DEPENDPATH += $$PWD/../Containers

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Containers/release/libContainers.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Containers/debug/libContainers.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Containers/release/Containers.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Containers/debug/Containers.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Containers/libContainers.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../qxmpp/src/release/ -lqxmpp_d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../qxmpp/src/debug/ -lqxmpp_d
else:unix: LIBS += -L$$OUT_PWD/../qxmpp/src/ -lqxmpp_d

INCLUDEPATH += $$PWD/../qxmpp/src
DEPENDPATH += $$PWD/../qxmpp/src
INCLUDEPATH += $$PWD/../qxmpp/src/base
DEPENDPATH += $$PWD/../qxmpp/src/base
INCLUDEPATH += $$PWD/../qxmpp/src/client
DEPENDPATH += $$PWD/../qxmpp/src/client
INCLUDEPATH += $$PWD/../qxmpp/src/server
DEPENDPATH += $$PWD/../qxmpp/src/server

unix|win32: LIBS += -L$$OUT_PWD/../qxmpp/src/ -lqxmpp_d

INCLUDEPATH += $$PWD/../qxmpp/src
DEPENDPATH += $$PWD/../qxmpp/src

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../qxmpp/src/qxmpp_d.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../qxmpp/src/libqxmpp_d.a

#-------------------------------------------------
#
# Project created by QtCreator 2014-01-31T12:14:32
#
#-------------------------------------------------

QT       += core gui network webkit webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Desktop
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mainmenu.cpp \
    maintab.cpp \
    visitorlistview.cpp \
    visitorchatview.cpp \
    logincontrol.cpp \
    loginwindow.cpp \
    messageeditor.cpp \
    visitordetailsview.cpp \
    cobrowseview.cpp \
    cobrowseobject.cpp

HEADERS  += mainwindow.h \
    mainmenu.h \
    maintab.h \
    visitorlistview.h \
    visitorchatview.h \
    logincontrol.h \
    loginwindow.h \
    messageeditor.h \
    visitordetailsview.h \
    cobrowseview.h \
    cobrowseobject.h

FORMS    += mainwindow.ui \
    mainmenu.ui \
    maintab.ui \
    visitorlistview.ui \
    visitorchatview.ui \
    logincontrol.ui \
    loginwindow.ui \
    visitordetailsview.ui \
    cobrowseview.ui

CONFIG += mobility
MOBILITY = 


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Business/release/ -lBusiness
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Business/debug/ -lBusiness
else:unix: LIBS += -L$$OUT_PWD/../Business/ -lBusiness

INCLUDEPATH += $$PWD/../Business
DEPENDPATH += $$PWD/../Business

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Business/release/libBusiness.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Business/debug/libBusiness.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Business/release/Business.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Business/debug/Business.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Business/libBusiness.a

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

#RESOURCES += \
#    Images.qrc

OTHER_FILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Network/release/ -lNetwork
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Network/debug/ -lNetwork
else:unix: LIBS += -L$$OUT_PWD/../Network/ -lNetwork

INCLUDEPATH += $$PWD/../Network
DEPENDPATH += $$PWD/../Network

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Network/release/libNetwork.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Network/debug/libNetwork.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Network/release/Network.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Network/debug/Network.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Network/libNetwork.a

RESOURCES += \
    Images.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../qxmpp/src/ -lqxmpp_d0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../qxmpp/src/ -lqxmpp_d0
else:unix: LIBS += -L$$OUT_PWD/../qxmpp/src/ -lqxmpp_d

INCLUDEPATH += $$PWD/../qxmpp/src
DEPENDPATH += $$PWD/../qxmpp/src
INCLUDEPATH += $$PWD/../qxmpp/src/base
DEPENDPATH += $$PWD/../qxmpp/src/base
INCLUDEPATH += $$PWD/../qxmpp/src/client
DEPENDPATH += $$PWD/../qxmpp/src/client
INCLUDEPATH += $$PWD/../qxmpp/src/server
DEPENDPATH += $$PWD/../qxmpp/src/serverr

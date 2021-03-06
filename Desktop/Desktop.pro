QT += core gui widgets network webkit webkitwidgets multimedia
QT -= qml quick sensors sql
TARGET = RedHelper
TEMPLATE = app
RC_FILE = icons.rc
GIT_VERSION = $$system(git rev-parse HEAD)
DEFINES += '__REVISION__=\'\"$$GIT_VERSION\"\''
OUT_WIN = $$replace(OUT_PWD, /, \\)
ICON = redhelper.icns

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
    cobrowseobject.cpp \
    chatcontrol.cpp \
    web.cpp \
    chatobject.cpp \
    tabbar.cpp \
    scrollarea.cpp \
    tabbutton.cpp \
    onlinestateselector.cpp \
    menubutton.cpp \
    menuseparator.cpp \
    aboutwindow.cpp \
    bugreportwindow.cpp \
    settingswindow.cpp \
    groupdelegate.cpp \
    webpage.cpp \
    application.cpp \
    redirectwindow.cpp

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
    cobrowseobject.h \
    chatcontrol.h \
    web.h \
    chatobject.h \
    tabbar.h \
    scrollarea.h \
    tabbutton.h \
    onlinestateselector.h \
    menubutton.h \
    menuseparator.h \
    aboutwindow.h \
    bugreportwindow.h \
    settingswindow.h \
    groupdelegate.h \
    webpage.h \
    application.h \
    redirectwindow.h

macx{
    OBJECTIVE_HEADERS += notificationcenter.h objectiveinitializer.h
    OBJECTIVE_SOURCES += notificationcenter.mm objectiveinitializer.mm
    QMAKE_LFLAGS += -F$$PWD/../ThirdParty
    LIBS += -framework Foundation -lobjc -framework Cocoa -framework Sparkle
    system(cp $$PWD/../dsa_pub.pem $$OUT_PWD/RedHelper.app/Contents/Resources/)
    QMAKE_INFO_PLIST = $$PWD/Info.plist
}

win32{
    #message(Test)
    #LIBS += -lWinSparkle
    #PRE_TARGETDEPS += $$PWD/../ThirdParty/winsparkle/WinSparkle.lib
    #INCLUDEPATH += $$PWD/../ThirdParty/winsparkle
    #DEPENDPATH += $$PWD/../ThirdParty/winsparkle

    system(xcopy $$OUT_WIN\\..\\..\\RedHelper\\ThirdParty $$OUT_WIN\\..\\ThirdParty /E /I /R /Y)
    LIBS += -L$$PWD/../ThirdParty/winsparkle/ -lWinSparkle
    INCLUDEPATH += $$PWD/../ThirdParty/winsparkle
    DEPENDPATH += $$PWD/../ThirdParty/winsparkle
    PRE_TARGETDEPS += $$OUT_PWD/../ThirdParty/winsparkle/WinSparkle.lib
}

FORMS += mainwindow.ui \
    mainmenu.ui \
    maintab.ui \
    visitorlistview.ui \
    visitorchatview.ui \
    logincontrol.ui \
    loginwindow.ui \
    visitordetailsview.ui \
    cobrowseview.ui \
    chatcontrol.ui \
    tabbar.ui \
    tabbutton.ui \
    onlinestateselector.ui \
    menubutton.ui \
    menuseparator.ui \
    aboutwindow.ui \
    bugreportwindow.ui \
    settingswindow.ui \
    redirectwindow.ui

CONFIG += mobility objective_c c++11
MOBILITY = 

##################### BUSINESS ####################

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

##################### NETWORK #####################

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

##################### CONTAINERS ##################

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

##################### QXMPP #######################

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../qxmpp/src/ -lqxmpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../qxmpp/src/ -lqxmpp_d
else:unix:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../qxmpp/src/ -lqxmpp
else:unix:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../qxmpp/src/ -lqxmpp_d


INCLUDEPATH += $$PWD/../qxmpp/src
DEPENDPATH += $$PWD/../qxmpp/src
INCLUDEPATH += $$PWD/../qxmpp/src/base
DEPENDPATH += $$PWD/../qxmpp/src/base
INCLUDEPATH += $$PWD/../qxmpp/src/client
DEPENDPATH += $$PWD/../qxmpp/src/client
INCLUDEPATH += $$PWD/../qxmpp/src/server
DEPENDPATH += $$PWD/../qxmpp/src/server

win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../qxmpp/src/qxmpp.lib
win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../qxmpp/src/qxmpp_d.lib
else:win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../qxmpp/src/libqxmpp.a
else:unix|win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../qxmpp/src/libqxmpp.a
else:unix|win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../qxmpp/src/libqxmpp_d.a


OTHER_FILES += \
    icons.rc \
    VisitorChat.html \
    jquery.js \
    chat.js \
    stylesheet.css \
    Incoming.wav \
    Incoming.mp3 \
    Info.plist

RESOURCES += \
    Images.qrc

defineReplace(out){
    win32:CONFIG(release, debug|release):QMAKE_POST_LINK += message($$quote(copy $$1 $$OUT_WIN\\release))
    else:win32:CONFIG(debug, debug|release):QMAKE_POST_LINK += $$quote(copy $$1 $$OUT_WIN\\debug)
    else:macx:QMAKE_POST_LINK += message($$system(cp $$1 $$OUT_PWD/RedHelper.app/Contents/MacOS/))
    else:QMAKE_POST_LINK += message($$system(cp $$1 $$OUT_PWD))

    win32:CONFIG(debug, debug|release):system(copy $$1 $$OUT_WIN\\debug)
    else:win32:CONFIG(release, debug|release):system(copy $$1 $$OUT_WIN\\release)
    else:macx:system(cp $$1 $$OUT_PWD/RedHelper.app/Contents/MacOS/)

    return(true)
}

EXTRA_BINFILES += \
    VisitorChat.html \
    jquery.js \
    chat.js \
    stylesheet.css \
    Incoming.wav \
    Incoming.mp3

for(FILE,EXTRA_BINFILES){
    $$out($$FILE)
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Smtp/release/ -lSmtp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Smtp/debug/ -lSmtp
else:unix: LIBS += -L$$OUT_PWD/../Smtp/ -lSmtp

INCLUDEPATH += $$PWD/../Smtp
DEPENDPATH += $$PWD/../Smtp

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Smtp/release/libSmtp.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Smtp/debug/libSmtp.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Smtp/release/Smtp.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Smtp/debug/Smtp.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Smtp/libSmtp.a



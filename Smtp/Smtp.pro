#-------------------------------------------------
#
# Project created by QtCreator 2014-02-21T16:27:28
#
#-------------------------------------------------

QT       -= gui

TARGET = Smtp
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    emailaddress.cpp \
    mimeattachment.cpp \
    mimefile.cpp \
    mimehtml.cpp \
    mimeinlinefile.cpp \
    mimemessage.cpp \
    mimepart.cpp \
    mimetext.cpp \
    smtpclient.cpp \
    quotedprintable.cpp \
    mimemultipart.cpp \
    mimecontentformatter.cpp

HEADERS  += \
    emailaddress.h \
    mimeattachment.h \
    mimefile.h \
    mimehtml.h \
    mimeinlinefile.h \
    mimemessage.h \
    mimepart.h \
    mimetext.h \
    smtpclient.h \
    SmtpMime \
    quotedprintable.h \
    mimemultipart.h \
    mimecontentformatter.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

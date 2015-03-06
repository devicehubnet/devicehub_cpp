#-------------------------------------------------
#
# Project created by QtCreator 2014-12-24T11:54:39
#
#-------------------------------------------------

QMAKE_MAC_SDK = macosx10.10

QT       -= core gui

TARGET = devicehub_cpp
TEMPLATE = app

DEFINES += DEVICEHUB_CPP_LIBRARY

SOURCES += dhconnection.cpp \
    devicehub.cpp \
    main.cpp

HEADERS += dhconnection.h\
        devicehub_cpp_global.h \
        devicehub.h

INCLUDEPATH += ../devicehub_cpp/

CONFIG += c++11

unix {
    target.path = /usr/lib
    INSTALLS += target
}

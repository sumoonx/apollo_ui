#-------------------------------------------------
#
# Project created by QtCreator 2016-07-08T15:37:09
#
#-------------------------------------------------

QT       += core gui
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = positioning
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    clientitem.cpp \
    anchoritem.cpp \
    graphicsmap.cpp \
    graphicsscene.cpp \
    anchor.cpp \
    client.cpp \
    location.cpp \
    serialport.cpp \
    serialportreader.cpp \
    rssiworker.cpp \
    positioningworker.cpp \
    threedimenworker.cpp \
    movingworker.cpp

HEADERS  += mainwindow.h \
    clientitem.h \
    anchoritem.h \
    graphicsmap.h \
    graphicsscene.h \
    anchor.h \
    client.h \
    location.h \
    serialport.h \
    serialportreader.h \
    rssiworker.h \
    positioningworker.h \
    threedimenworker.h \
    movingworker.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    drawable.qrc

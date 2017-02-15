#-------------------------------------------------
#
# Project created by QtCreator 2017-01-16T16:01:47
#
#-------------------------------------------------

QT       += core gui network
QT       += multimedia
QT       += multimediawidgets
QT       += widgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        MainWindow.cpp \
    CreateRoom.cpp \
    Room.cpp \
    TempData.cpp \
    MyVideoSend.cpp \
    Danmu.cpp \
    LiveWatch.cpp

HEADERS  += MainWindow.h \
    protocol.h \
    CreateRoom.h \
    Room.h \
    TempData.h \
    MyVideoSend.h \
    Danmu.h \
    LiveWatch.h \
    udppackage.h

FORMS    += MainWindow.ui \
    CreateRoom.ui \
    Room.ui \
    LiveWatch.ui

RESOURCES += \
    image.qrc

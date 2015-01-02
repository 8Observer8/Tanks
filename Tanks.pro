#-------------------------------------------------
#
# Project created by QtCreator 2014-12-28T13:08:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tanks
TEMPLATE = app


SOURCES += main.cpp\
        Dialog.cpp \
    Scene.cpp \
    Ice.cpp \
    Tank.cpp \
    Plane.cpp

HEADERS  += Dialog.h \
    Scene.h \
    Ice.h \
    Tank.h \
    Plane.h

FORMS    += Dialog.ui

RESOURCES += \
    Shaders.qrc \
    Textures.qrc

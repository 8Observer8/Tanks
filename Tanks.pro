#-------------------------------------------------
#
# Project created by QtCreator 2014-12-28T13:08:35
#
#-------------------------------------------------

QT       += core gui multimedia

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tanks
TEMPLATE = app


SOURCES += main.cpp\
        Dialog.cpp \
    Scene.cpp \
    Ice.cpp \
    Tank.cpp \
    Plane.cpp \
    Projectile.cpp \
    SmallExplosion.cpp \
    LargeExplosion.cpp \
    SoundOfShot.cpp \
    SoundOfTankExplosion.cpp \
    SoundOfProjectileExplosion.cpp \
    ExplosionOfProjectile.cpp \
    ExplosionOfTank.cpp

HEADERS  += Dialog.h \
    Scene.h \
    Ice.h \
    Tank.h \
    Plane.h \
    Projectile.h \
    SmallExplosion.h \
    LargeExplosion.h \
    SoundOfShot.h \
    SoundOfTankExplosion.h \
    SoundOfProjectileExplosion.h \
    ExplosionOfProjectile.h \
    ExplosionOfTank.h

FORMS    += Dialog.ui

RESOURCES += \
    Shaders.qrc \
    Textures.qrc \
    Sounds.qrc

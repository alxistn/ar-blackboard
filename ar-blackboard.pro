TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += link_pkgconfig
PKGCONFIG += opencv
PKGCONFIG += box2d
PKGCONFIG += sdl2

SOURCES += main.cpp \
    window.cpp \
    fpstimer.cpp \
    scene.cpp \
    gamescene.cpp \
    gameobject.cpp \
    player.cpp \
    opencvscene.cpp \
    vertexextractor.cpp\
    cubeobject.cpp \
    destructibleobject.cpp \
    PlayerContactListener.cpp

HEADERS += \
    window.h \
    fpstimer.h \
    scene.h \
    gamescene.h \
    gameobject.hpp \
    player.h \
    opencvscene.h \
    vertexextractor.h\
    cubeobject.h \
    destructibleobject.h \
    PlayerContactListener.hpp


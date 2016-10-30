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
    destructibleobject.cpp \
    ball.cpp \
    cube.cpp \
    missile.cpp \
    contactlistener.cpp

HEADERS += \
    window.h \
    fpstimer.h \
    scene.h \
    gamescene.h \
    player.h \
    opencvscene.h \
    vertexextractor.h\
    destructibleobject.h \
    ball.h \
    cube.h \
    missile.h \
    gameobject.h \
    contactlistener.h


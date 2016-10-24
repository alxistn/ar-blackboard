TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += link_pkgconfig
PKGCONFIG += opencv
PKGCONFIG += box2d
PKGCONFIG += sdl2

INCLUDEPATH += "/usr/include/"
DEPENDPATH += "/usr/include/"
SOURCES += main.cpp \
    window.cpp \
    fpstimer.cpp \
    scene.cpp \
    gamescene.cpp

HEADERS += \
    window.h \
    fpstimer.h \
    scene.h \
    gamescene.h


TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += link_pkgconfig
#PKGCONFIG += opencv
#PKGCONFIG += box2d
#PKGCONFIG += sdl2

#INCLUDEPATH += "/usr/include/"
#DEPENDPATH += "/usr/include/"

INCLUDEPATH += /Library/Frameworks/SDL2.framework/Headers
INCLUDEPATH += /Library/Frameworks/SDL2_image.framework/Headers
INCLUDEPATH += /Library/Frameworks/SDL2_ttf.framework/Headers
INCLUDEPATH += /usr/local/include/Box2D

LIBS += -framework Cocoa -framework SDL2
LIBS += -framework Cocoa -framework SDL2_image
LIBS += -framework Cocoa -framework SDL2_ttf

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


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./release/ -lBox2D
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./debug/ -lBox2D
else:unix: LIBS += -L$$PWD/./ -lBox2D

DEPENDPATH += $$PWD/../../../../../usr/local/include/Box2D

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/./release/libBox2D.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/./debug/libBox2D.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/./release/Box2D.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/./debug/Box2D.lib
else:unix: PRE_TARGETDEPS += $$PWD/./libBox2D.a


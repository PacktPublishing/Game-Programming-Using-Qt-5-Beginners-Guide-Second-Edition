QT = core gui widgets
TARGET = animated_cube
TEMPLATE = app
HEADERS += abstractglscene.h \
    sceneglwindow.h \
    cubeglscene.h
SOURCES += main.cpp abstractglscene.cpp \
    sceneglwindow.cpp \
    cubeglscene.cpp

CONFIG += c++11

RESOURCES += \
    texture.qrc

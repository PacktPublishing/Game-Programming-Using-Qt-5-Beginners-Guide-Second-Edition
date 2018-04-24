QT = core gui
TARGET = cube
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

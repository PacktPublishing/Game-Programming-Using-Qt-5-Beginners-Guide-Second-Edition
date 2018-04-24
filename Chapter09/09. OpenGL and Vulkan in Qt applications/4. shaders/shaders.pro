QT = core gui
TARGET = shaders
TEMPLATE = app
HEADERS += abstractglscene.h sceneglwindow.h shaderglscene.h \
    plyreader.h
SOURCES += main.cpp abstractglscene.cpp sceneglwindow.cpp shaderglscene.cpp \
    plyreader.cpp

CONFIG += c++11

RESOURCES += resources.qrc

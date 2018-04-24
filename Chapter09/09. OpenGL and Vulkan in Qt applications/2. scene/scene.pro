QT = core gui
TARGET = scene
TEMPLATE = app
HEADERS += abstractglscene.h \
    sceneglwindow.h
SOURCES += main.cpp abstractglscene.cpp \
    sceneglwindow.cpp

CONFIG += c++11

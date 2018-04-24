#-------------------------------------------------
#
# Project created by QtCreator 2017-11-20T17:53:25
#
#-------------------------------------------------

QT       += core gui widgets qml

TARGET = scripted_game
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    scene.cpp \
    sceneproxy.cpp \
    entityproxy.cpp \
    entity.cpp

HEADERS += \
    scene.h \
    sceneproxy.h \
    entityproxy.h \
    entity.h

RESOURCES += \
    resources.qrc

QT       += core
QT       -= gui
TARGET = qtpython
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

SOURCES += main.cpp \
    qtpython.cpp

HEADERS += \
    qtpython.h

CONFIG += link_pkgconfig no_keywords
PKGCONFIG += python-3.5m
CONFIG += c++11

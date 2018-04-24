QT = core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = regularexpression
TEMPLATE = app

SOURCES += \
    main.cpp
CONFIG += c++11

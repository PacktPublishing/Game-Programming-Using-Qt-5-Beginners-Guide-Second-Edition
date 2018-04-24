QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chess
TEMPLATE = app


SOURCES += main.cpp \
    chessboard.cpp \
    chessalgorithm.cpp \
    chessview.cpp \
    mainwindow.cpp

HEADERS  += \
    chessboard.h \
    chessalgorithm.h \
    chessview.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

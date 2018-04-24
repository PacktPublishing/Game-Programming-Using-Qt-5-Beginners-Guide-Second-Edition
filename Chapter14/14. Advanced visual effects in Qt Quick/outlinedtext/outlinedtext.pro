TEMPLATE = app
TARGET = outlinedtext
INCLUDEPATH += .

SOURCES += main.cpp outlinetextitem.cpp \
    outlinetextitemborder.cpp

QT += quick

HEADERS += outlinetextitem.h \
    outlinetextitemborder.h

RESOURCES += \
    resources.qrc

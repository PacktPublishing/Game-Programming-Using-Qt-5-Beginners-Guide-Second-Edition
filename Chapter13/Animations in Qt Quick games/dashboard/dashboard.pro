TEMPLATE = app
TARGET = dashboard
INCLUDEPATH += .

SOURCES += main.cpp \
    carinfo.cpp \
    carinfoengine.cpp \
    carinfoproxy.cpp

QT += quick widgets

FORMS += form.ui

HEADERS += \
    carinfo.h \
    carinfoengine.h \
    carinfoproxy.h

RESOURCES += \
    resources.qrc

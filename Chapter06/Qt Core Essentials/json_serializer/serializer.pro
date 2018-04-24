TEMPLATE = app
TARGET = jsonserializer
DEPENDPATH += .
INCLUDEPATH += .

HEADERS += playerinfo.h \
    playerinfojson.h

SOURCES += \
    playerinfo.cpp \
    playerinfojson.cpp \
    main.cpp

CONFIG += c++11

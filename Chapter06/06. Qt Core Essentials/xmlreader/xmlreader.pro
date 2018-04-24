TEMPLATE = app
TARGET = xmlreader
DEPENDPATH += .
INCLUDEPATH += .
QT = core

# Input
HEADERS += \
    playerinforeader.h \
    playerinfo.h

SOURCES += \
    playerinforeader.cpp \
    main.cpp \
    playerinfo.cpp

RESOURCES += \
    resources.qrc

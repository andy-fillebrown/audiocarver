TARGET = GLDatabase
TEMPLATE = lib

QT -= gui

include(../../projectplugin.pri)
include(gldatabaseplugin_dependencies.pri)

DEFINES += GLDATABASE_LIBRARY

HEADERS += \
    interfaces/igldatabase.h \
    \
    gldatabase_global.h \
    gldatabaseplugin.h

SOURCES += \
    interfaces/igldatabase.cpp \
    \
    gldatabaseplugin.cpp

RESOURCES += \

OTHER_FILES += \

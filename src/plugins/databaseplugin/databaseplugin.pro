TARGET = Database
TEMPLATE = lib

QT += xml

include(../../projectplugin.pri)
include(databaseplugin_dependencies.pri)

DEFINES += DATABASE_LIBRARY

HEADERS += \
    interfaces/idatabase.h \
    \
    classes/object.h \
    classes/root.h \
    \
    database_global.h \
    databaseplugin.h

SOURCES += \
    interfaces/idatabase.cpp \
    \
    classes/object.cpp \
    classes/root.cpp \
    \
    databaseplugin.cpp

TARGET = Database
TEMPLATE = lib

QT += xml

include(../../projectplugin.pri)
include(databaseplugin_dependencies.pri)

DEFINES += DATABASE_LIBRARY

HEADERS += \
    interfaces/idatabase.h \
    \
    classes/link.h \
    classes/object.h \
    classes/rootobject.h \
    \
    database_global.h \
    databaseplugin.h

SOURCES += \
    interfaces/idatabase.cpp \
    \
    classes/link.cpp \
    classes/object.cpp \
    classes/rootobject.cpp \
    \
    databaseplugin.cpp

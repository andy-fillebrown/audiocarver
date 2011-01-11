TARGET = Database
TEMPLATE = lib

QT += xml

include(../../projectplugin.pri)
include(databaseplugin_dependencies.pri)

DEFINES += DATABASE_LIBRARY

HEADERS += \
    interfaces/idatabase.h \
    \
    database_global.h \
    databaseplugin.h

SOURCES += \
    interfaces/idatabase.cpp \
    \
    databaseplugin.cpp

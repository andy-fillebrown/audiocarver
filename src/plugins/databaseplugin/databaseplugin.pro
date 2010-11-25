TEMPLATE = lib
TARGET   = Database

QT += xml

include(../../projectplugin.pri)
include(databaseplugin_dependencies.pri)

DEFINES += DATABASE_LIBRARY

SOURCES += \
    databaseplugin.cpp

HEADERS += \
    database_global.h \
    databaseplugin.h

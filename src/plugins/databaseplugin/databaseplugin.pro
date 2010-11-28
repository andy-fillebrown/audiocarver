TEMPLATE = lib
TARGET   = Database

QT += xml

include(../../projectplugin.pri)
include(databaseplugin_dependencies.pri)

DEFINES += DATABASE_LIBRARY

SOURCES += \
    implementations/uniqueNameManager.cpp \
    databaseplugin.cpp

HEADERS += \
    implementations/uniqueNameManager.h \
    database_global.h \
    databaseplugin.h

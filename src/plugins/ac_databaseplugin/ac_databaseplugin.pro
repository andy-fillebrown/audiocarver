TARGET = AC_Database
TEMPLATE = lib

QT += xml

include(../../projectplugin.pri)
include(ac_databaseplugin_dependencies.pri)

DEFINES += AC_DATABASE_LIBRARY

HEADERS += \
	ac_database_global.h \
	ac_databaseplugin.h

SOURCES += \
	ac_databaseplugin.cpp

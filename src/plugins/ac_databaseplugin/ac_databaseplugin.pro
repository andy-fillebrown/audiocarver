TARGET = AC_Database
TEMPLATE = lib

QT += xml

include(../../projectplugin.pri)
include(../databaseplugin/databaseplugin.pri)
include(ac_databaseplugin_dependencies.pri)

DEFINES += AC_DATABASE_LIBRARY

HEADERS += \
	implementations/database.h \
	implementations/model.h \
	\
	ac_database_global.h \
	ac_databaseplugin.h

SOURCES += \
	implementations/database.cpp \
	implementations/model.cpp \
	\
	ac_databaseplugin.cpp

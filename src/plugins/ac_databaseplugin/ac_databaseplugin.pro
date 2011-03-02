TARGET = AC_Database
TEMPLATE = lib

QT += xml

include(../../projectplugin.pri)
include(../databaseplugin/databaseplugin.pri)
include(ac_databaseplugin_dependencies.pri)

DEFINES += AC_DATABASE_LIBRARY

HEADERS += \
	classes/fcurve.h \
	classes/fpoint.h \
	\
	implementations/database.h \
	\
	ac_database_global.h \
	ac_databaseplugin.h

SOURCES += \
	classes/fcurve.cpp \
	classes/fpoint.cpp \
	\
	implementations/database.cpp \
	\
	ac_databaseplugin.cpp

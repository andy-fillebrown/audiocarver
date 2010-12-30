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
    interfaces/idatabase.h \
    interfaces/idataobject.h \
    interfaces/ifiler.h \
    interfaces/ilinkobject.h \
    interfaces/iobject.h \
    interfaces/ireader.h \
    interfaces/irootobject.h \
    interfaces/iwriter.h \
    database_global.h \
    databaseplugin.h

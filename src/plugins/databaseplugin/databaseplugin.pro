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
    interfaces/ilistobject.h \
    interfaces/iobject.h \
    interfaces/irootobject.h \
    database_global.h \
    databaseplugin.h

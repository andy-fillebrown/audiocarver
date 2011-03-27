TARGET = AC_Database
TEMPLATE = lib

include(../../plugin.pri)
include(ac_databaseplugin_dependencies.pri)

DEFINES += AC_DATABASE_LIBRARY

HEADERS += \
    classes/fcurve.h \
    classes/fpoint.h \
    classes/note.h \
    classes/track.h \
    classes/score.h \
    \
    implementations/database.h \
    \
    ac_database_global.h \
    ac_databaseplugin.h \

SOURCES += \
    classes/fcurve.cpp \
    classes/fpoint.cpp \
    classes/note.cpp \
    classes/track.cpp \
    classes/score.cpp \
    \
    implementations/database.cpp \
    \
    ac_databaseplugin.cpp \

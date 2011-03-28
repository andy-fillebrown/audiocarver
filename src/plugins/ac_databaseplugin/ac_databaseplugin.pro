TARGET = AC_Database
TEMPLATE = lib

include(../../plugin.pri)
include(ac_databaseplugin_dependencies.pri)

DEFINES += AC_DATABASE_LIBRARY

HEADERS += \
    classes/fcurve.h \
    classes/fpoint.h \
    classes/note.h \
    classes/score.h \
    classes/track.h \
    classes/tuning.h \
    \
    implementations/database.h \
    \
    settings/gridsettings.h \
    \
    ac_database_global.h \
    ac_databaseplugin.h \

SOURCES += \
    classes/fcurve.cpp \
    classes/fpoint.cpp \
    classes/note.cpp \
    classes/score.cpp \
    classes/track.cpp \
    classes/tuning.cpp \
    \
    implementations/database.cpp \
    \
    settings/gridsettings.cpp \
    \
    ac_databaseplugin.cpp \

TARGET = AC_Database
TEMPLATE = lib

include(../../plugin.pri)
include(ac_databaseplugin_dependencies.pri)

DEFINES += AC_DATABASE_LIBRARY

HEADERS += \
    classes/ac_barline.h \
    classes/ac_fcurve.h \
    classes/ac_fpoint.h \
    classes/ac_guideline.h \
    classes/ac_note.h \
    classes/ac_score.h \
    classes/ac_track.h \
    classes/ac_tuning.h \
    \
    implementations/ac_database.h \
    \
    settings/ac_gridsettings.h \
    settings/ac_viewsettings.h \
    \
    ac_database_global.h \
    ac_databaseplugin.h \

SOURCES += \
    classes/ac_barline.cpp \
    classes/ac_fcurve.cpp \
    classes/ac_fpoint.cpp \
    classes/ac_guideline.cpp \
    classes/ac_note.cpp \
    classes/ac_score.cpp \
    classes/ac_track.cpp \
    classes/ac_tuning.cpp \
    \
    implementations/ac_database.cpp \
    \
    settings/ac_gridsettings.cpp \
    settings/ac_viewsettings.cpp \
    \
    ac_databaseplugin.cpp \

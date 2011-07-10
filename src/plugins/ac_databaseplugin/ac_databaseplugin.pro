TARGET = AC_Database
TEMPLATE = lib

include(../../plugin.pri)
include(ac_databaseplugin_dependencies.pri)

DEFINES += AC_DATABASE_LIBRARY

HEADERS += \
    classes/ac_barline.h \
    classes/ac_curve.h \
    classes/ac_gridline.h \
    classes/ac_note.h \
    classes/ac_pitchcurve.h \
    classes/ac_point.h \
    classes/ac_score.h \
    classes/ac_track.h \
    classes/ac_tuningline.h \
    classes/ac_valueline.h \
    classes/ac_volumecurve.h \
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
    classes/ac_curve.cpp \
    classes/ac_gridline.cpp \
    classes/ac_note.cpp \
    classes/ac_point.cpp \
    classes/ac_pitchcurve.cpp \
    classes/ac_score.cpp \
    classes/ac_track.cpp \
    classes/ac_tuningline.cpp \
    classes/ac_valueline.cpp \
    classes/ac_volumecurve.cpp \
    \
    implementations/ac_database.cpp \
    \
    settings/ac_gridsettings.cpp \
    settings/ac_viewsettings.cpp \
    \
    ac_databaseplugin.cpp \

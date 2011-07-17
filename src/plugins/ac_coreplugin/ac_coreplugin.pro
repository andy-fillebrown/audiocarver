TARGET = AcCorePlugin
TEMPLATE = lib

include(../../plugin.pri)
include(ac_coreplugin_dependencies.pri)

DEFINES += AC_CORE_LIBRARY

HEADERS += \
    implementations/ac_database.h \
    \
#    score/ac_barline.h \
#    score/ac_curve.h \
#    score/ac_gridline.h \
#    score/ac_note.h \
#    score/ac_pitchcurve.h \
#    score/ac_point.h \
#    score/ac_score.h \
#    score/ac_track.h \
#    score/ac_tuningline.h \
#    score/ac_valueline.h \
#    score/ac_volumecurve.h \
#    \
#    settings/ac_gridsettings.h \
#    settings/ac_viewsettings.h \
    \
    ac_core_global.h \
    ac_coreplugin.h \

SOURCES += \
    implementations/ac_database.cpp \
    \
#    score/ac_barline.cpp \
#    score/ac_curve.cpp \
#    score/ac_gridline.cpp \
#    score/ac_note.cpp \
#    score/ac_point.cpp \
#    score/ac_pitchcurve.cpp \
#    score/ac_score.cpp \
#    score/ac_track.cpp \
#    score/ac_tuningline.cpp \
#    score/ac_valueline.cpp \
#    score/ac_volumecurve.cpp \
#    \
#    settings/ac_gridsettings.cpp \
#    settings/ac_viewsettings.cpp \
    \
    ac_coreplugin.cpp \

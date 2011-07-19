TARGET = AcCorePlugin
TEMPLATE = lib

include(../../plugin.pri)
include(ac_coreplugin_dependencies.pri)

DEFINES += AC_CORE_LIBRARY

HEADERS += \
    dataobjects/ac_curve.h \
#    dataobjects/ac_gridline.h \
#    dataobjects/ac_gridsettings.h \
#    dataobjects/ac_note.h \
#    dataobjects/ac_pitchcurve.h \
#    dataobjects/ac_pitchline.h \
    dataobjects/ac_point.h \
#    dataobjects/ac_score.h \
#    dataobjects/ac_timeline.h \
#    dataobjects/ac_track.h \
#    dataobjects/ac_valuecurve.h \
#    dataobjects/ac_valueline.h \
#    dataobjects/ac_viewsettings.h \
    \
    implementations/ac_database.h \
    \
    ac_core_global.h \
    ac_coreplugin.h \

SOURCES += \
    dataobjects/ac_curve.cpp \
#    dataobjects/ac_gridline.cpp \
#    dataobjects/ac_gridsettings.cpp \
#    dataobjects/ac_note.cpp \
    dataobjects/ac_point.cpp \
#    dataobjects/ac_pitchcurve.cpp \
#    dataobjects/ac_pitchline.cpp \
#    dataobjects/ac_score.cpp \
#    dataobjects/ac_timeline.cpp \
#    dataobjects/ac_track.cpp \
#    dataobjects/ac_valuecurve.cpp \
#    dataobjects/ac_valueline.cpp \
#    dataobjects/ac_viewsettings.cpp \
    \
    implementations/ac_database.cpp \
    \
    ac_coreplugin.cpp \

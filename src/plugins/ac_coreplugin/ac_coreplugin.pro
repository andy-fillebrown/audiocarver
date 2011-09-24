TARGET = AcCorePlugin
TEMPLATE = lib

include(../../plugin.pri)
include(ac_coreplugin_dependencies.pri)

DEFINES += AC_CORE_LIBRARY

HEADERS += \
    dataobjects/ac_objectlist.h \
    \
    model/interfaces/ac_imodelitem.h \
    \
    tools/ac_point.h \
    \
    ac_global.h \
    ac_namespace.h \

SOURCE_PAIRS += \
    dataobjects/ac_controlcurve \
    dataobjects/ac_curve \
    dataobjects/ac_note \
    dataobjects/ac_object \
    dataobjects/ac_pitchcurve \
    dataobjects/ac_score \
    dataobjects/ac_scoreobject \
    dataobjects/ac_track \
    dataobjects/ac_viewsettings \
    \
    graphicsitems/ac_graphicsitem \
    \
    implementations/ac_database \
    \
    model/ac_model \
    \
    ac_coreplugin \

for(pair, SOURCE_PAIRS) {
    HEADERS *= $${pair}.h
    SOURCES *= $${pair}.cpp
}

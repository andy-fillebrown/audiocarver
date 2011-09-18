TARGET = AcCorePlugin
TEMPLATE = lib

include(../../plugin.pri)
include(ac_coreplugin_dependencies.pri)

DEFINES += AC_CORE_LIBRARY

HEADERS += \
    model/interfaces/acimodelitem.h \
    \
    accoreglobal.h \
    accoreenums.h \

SOURCE_PAIRS += \
    dataobjects/accontrolcurve \
    dataobjects/accurve \
    dataobjects/acnote \
    dataobjects/acobject \
    dataobjects/acobjectlist \
    dataobjects/acpitchcurve \
    dataobjects/acscore \
    dataobjects/acscoreobject \
    dataobjects/actrack \
    \
    graphicsitems/acgraphicsitem \
    \
    implementations/ac_database \
    \
    model/acmodel \
    \
    tools/acpoint \
    \
    accoreplugin \

for(pair, SOURCE_PAIRS) {
    HEADERS *= $${pair}.h
    SOURCES *= $${pair}.cpp
}

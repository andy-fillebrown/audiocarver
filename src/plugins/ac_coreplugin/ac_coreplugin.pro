TARGET = AcCorePlugin
TEMPLATE = lib

include(../../plugin.pri)
include(ac_coreplugin_dependencies.pri)

DEFINES += AC_CORE_LIBRARY

HEADERS += \
    ac_core_enums.h \
    ac_core_global.h \

SOURCE_PAIRS += \
    implementations/ac_database \
    \
    items/ac_model \
    \
#    tools/ac_point \
    \
    ac_coreplugin \

for(pair, SOURCE_PAIRS) {
    HEADERS *= $${pair}.h
    SOURCES *= $${pair}.cpp
}

TARGET = AcCorePlugin
TEMPLATE = lib

load(../../plugin.prf)
load(../ac_coreplugin/ac_coreplugin_dependencies.prf)

for(dir, DIRS) {
    include($$dir/$${dir}.pri)
}

DEFINES *= \
    AC_CORE_LIBRARY \

HEADERS *= \
    ac_coreconstants.h \
    ac_global.h \
    ac_namespace.h \

SOURCE_PAIRS = \
    ac_coreplugin \

for(pair, SOURCE_PAIRS) {
    HEADERS *= $${pair}.h
    SOURCES *= $${pair}.cpp
}

OTHER_FILES *= \
    ac_coreplugin.prf \
    ac_coreplugin_dependencies.prf \
    AcCorePlugin.pluginspec.in \

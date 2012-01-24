TARGET = MiCorePlugin
TEMPLATE = lib
QT -= gui

load(../../plugin.prf)
load(../mi_coreplugin/mi_coreplugin_dependencies.prf)

for(dir, DIRS) {
    include($$dir/$${dir}.pri)
}

DEFINES *= MI_CORE_LIBRARY

HEADERS *= \
    mi_global.h \

SOURCE_PAIRS = \
    mi_coreplugin \
    mi_namespace \

for(pair, SOURCE_PAIRS) {
    HEADERS *= $${pair}.h
    SOURCES *= $${pair}.cpp
}

OTHER_FILES *= \
    mi_coreplugin.prf \
    mi_coreplugin_dependencies.prf \
    MiCorePlugin.pluginspec.in \

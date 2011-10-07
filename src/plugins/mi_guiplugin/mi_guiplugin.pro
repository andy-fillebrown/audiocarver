TARGET = MiGuiPlugin
TEMPLATE = lib

load(../../plugin.prf)
load(../mi_guiplugin/mi_guiplugin_dependencies.prf)

for(dir, DIRS) {
    include($$dir/$${dir}.pri)
}

DEFINES *= \
    MI_GUI_LIBRARY

HEADERS *= \
    mi_guiconstants.h \

SOURCE_PAIRS = \
    mi_guiplugin \

for(pair, SOURCE_PAIRS) {
    HEADERS *= $${pair}.h
    SOURCES *= $${pair}.cpp
}

RESOURCES *= \
    mi_guiplugin.qrc \

OTHER_FILES *= \
    mi_guiplugin.prf \
    mi_guiplugin_dependencies.prf \
    MiGuiPlugin.pluginspec.in \

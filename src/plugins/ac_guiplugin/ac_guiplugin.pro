TARGET = AcGuiPlugin
TEMPLATE = lib

load(../../plugin.prf)
load(../ac_guiplugin/ac_guiplugin_dependencies.prf)

for(dir, DIRS) {
    include($$dir/$${dir}.pri)
}

HEADERS *= \
    ac_guiconstants.h \

SOURCE_PAIRS = \
    ac_guiplugin \
    ac_mainwidget \

for(pair, SOURCE_PAIRS) {
    HEADERS *= $${pair}.h
    SOURCES *= $${pair}.cpp
}

RESOURCES *= \
    ac_guiplugin.qrc \

OTHER_FILES *= \
    ac_guiplugin.prf \
    ac_guiplugin_dependencies.prf \
    AcGuiPlugin.pluginspec.in \

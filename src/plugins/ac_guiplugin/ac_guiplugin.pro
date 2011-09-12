TARGET = AcGuiPlugin
TEMPLATE = lib

include(../../plugin.pri)
include(ac_guiplugin_dependencies.pri)

HEADERS += \
    ac_guiconstants.h \
    ac_guienums.h \
    ac_guiutil.h \

SOURCE_PAIRS = \
    graphics/ac_graphicsitem \
    graphics/ac_graphicsscene \
    graphics/ac_graphicssceneitem \
    \
    graphicsview/ac_editorview \
    graphicsview/ac_labelview \
    graphicsview/ac_graphicsview \
    graphicsview/ac_pitchlabelview \
    graphicsview/ac_pitchview \
    graphicsview/ac_timelabelview \
    graphicsview/ac_viewmanager \
    graphicsview/ac_volumelabelview \
    graphicsview/ac_volumeview \
    \
    implementations/ac_editorimpl \
    implementations/ac_mainwindowimpl \
    \
    itemviews/ac_itemview \
    \
    ac_guiplugin \
    ac_mainwidget \

for(pair, SOURCE_PAIRS) {
    HEADERS *= $${pair}.h
    SOURCES *= $${pair}.cpp
}

RESOURCES = ac_gui.qrc

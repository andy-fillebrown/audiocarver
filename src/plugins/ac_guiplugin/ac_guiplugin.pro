TARGET = AcGuiPlugin
TEMPLATE = lib

include(../../plugin.pri)
include(ac_guiplugin_dependencies.pri)

HEADERS += \
    ac_guiconstants.h \
    ac_guienums.h \
    ac_guiutil.h \

SOURCE_PAIRS = \
#    factories/ac_guifactory \
#    \
#    graphicsitem/gridlines/ac_graphicsgridlineitem \
#    graphicsitem/gridlines/ac_graphicshgridlineitem \
#    graphicsitem/gridlines/ac_graphicspitchlineitem \
#    graphicsitem/gridlines/ac_graphicstimelineitem \
#    graphicsitem/gridlines/ac_graphicsvolumelineitem \
#    \
#    graphicsitem/ac_graphicsitem \
#    graphicsitem/ac_graphicsnoteitem \
#    graphicsitem/ac_graphicspitchpointitem \
#    graphicsitem/ac_graphicspointitem \
#    graphicsitem/ac_graphicstrackitem \
#    graphicsitem/ac_graphicsvolumepointitem \
#    graphicsitem/ac_scaledgraphicsitem \
#    \
    graphicsscene/ac_graphicsscene \
    graphicsscene/ac_labelscene \
    graphicsscene/ac_pitchlabelscene \
    graphicsscene/ac_pitchscene \
    graphicsscene/ac_scenemanager \
    graphicsscene/ac_timelabelscene \
    graphicsscene/ac_volumelabelscene \
    graphicsscene/ac_volumescene \
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

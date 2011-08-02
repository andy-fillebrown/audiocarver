TARGET = AcGuiPlugin
TEMPLATE = lib

include(../../plugin.pri)
include(ac_guiplugin_dependencies.pri)

HEADERS += \
    graphicsitem/ac_graphicsgridlineitem.h \
    graphicsitem/ac_graphicsitem.h \
    graphicsitem/ac_graphicsnoteitem.h \
    graphicsitem/ac_graphicspitchlineitem.h \
    graphicsitem/ac_graphicspitchpointitem.h \
    graphicsitem/ac_graphicspointitem.h \
    graphicsitem/ac_graphicstimelineitem.h \
    graphicsitem/ac_graphicstrackitem.h \
    graphicsitem/ac_graphicsvolumelineitem.h \
    graphicsitem/ac_graphicsvolumepointitem.h \
    graphicsitem/ac_scaledgraphicsitem.h \
#    \
#    graphicsscene/ac_graphicsscene.h \
#    graphicsscene/ac_labelscene.h \
#    graphicsscene/ac_pitchlabelscene.h \
#    graphicsscene/ac_pitchscene.h \
#    graphicsscene/ac_scenemanager.h \
#    graphicsscene/ac_timelabelscene.h \
#    graphicsscene/ac_volumelabelscene.h \
#    graphicsscene/ac_volumescene.h \
#    \
#    graphicsview/ac_editorview.h \
#    graphicsview/ac_labelview.h \
#    graphicsview/ac_graphicsview.h \
#    graphicsview/ac_pitchlabelview.h \
#    graphicsview/ac_pitchview.h \
#    graphicsview/ac_timelabelview.h \
#    graphicsview/ac_viewmanager.h \
#    graphicsview/ac_volumelabelview.h \
#    graphicsview/ac_volumeview.h \
    \
    implementations/ac_editorimpl.h \
    implementations/ac_mainwindowimpl.h \
    \
    ac_guiconstants.h \
    ac_guiplugin.h \
#    ac_mainwidget.h \
    ac_scene_util.h \

SOURCES += \
    graphicsitem/ac_graphicsgridlineitem.cpp \
    graphicsitem/ac_graphicsitem.cpp \
    graphicsitem/ac_graphicsnoteitem.cpp \
    graphicsitem/ac_graphicspitchlineitem.cpp \
    graphicsitem/ac_graphicspitchpointitem.cpp \
    graphicsitem/ac_graphicspointitem.cpp \
    graphicsitem/ac_graphicstimelineitem.cpp \
    graphicsitem/ac_graphicstrackitem.cpp \
    graphicsitem/ac_graphicsvolumelineitem.cpp \
    graphicsitem/ac_graphicsvolumepointitem.cpp \
    graphicsitem/ac_scaledgraphicsitem.cpp \
#    \
#    graphicsscene/ac_graphicsscene.cpp \
#    graphicsscene/ac_labelscene.cpp \
#    graphicsscene/ac_pitchlabelscene.cpp \
#    graphicsscene/ac_pitchscene.cpp \
#    graphicsscene/ac_scenemanager.cpp \
#    graphicsscene/ac_timelabelscene.cpp \
#    graphicsscene/ac_volumelabelscene.cpp \
#    graphicsscene/ac_volumescene.cpp \
#    \
#    graphicsview/ac_editorview.cpp \
#    graphicsview/ac_labelview.cpp \
#    graphicsview/ac_graphicsview.cpp \
#    graphicsview/ac_pitchlabelview.cpp \
#    graphicsview/ac_pitchview.cpp \
#    graphicsview/ac_timelabelview.cpp \
#    graphicsview/ac_viewmanager.cpp \
#    graphicsview/ac_volumelabelview.cpp \
#    graphicsview/ac_volumeview.cpp \
    \
    implementations/ac_editorimpl.cpp \
    implementations/ac_mainwindowimpl.cpp \
    \
    ac_guiplugin.cpp \
#    ac_mainwidget.cpp \

RESOURCES = ac_gui.qrc

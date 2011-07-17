TARGET = AcGuiPlugin
TEMPLATE = lib

include(../../plugin.pri)
include(ac_guiplugin_dependencies.pri)

HEADERS += \
    graphicsitem/ac_graphicsbarlineitem.h \
    graphicsitem/ac_graphicscontrolpointitem.h \
    graphicsitem/ac_graphicsgridlineitem.h \
    graphicsitem/ac_graphicsitem.h \
    graphicsitem/ac_graphicsnoteitem.h \
    graphicsitem/ac_graphicspointitem.h \
    graphicsitem/ac_graphicsscorepointitem.h \
    graphicsitem/ac_graphicstrackitem.h \
    graphicsitem/ac_graphicstuninglineitem.h \
    graphicsitem/ac_graphicsvaluelineitem.h \
    graphicsitem/ac_scaledgraphicsitem.h \
    \
    graphicsscene/ac_controlscene.h \
    graphicsscene/ac_graphicsscene.h \
    graphicsscene/ac_pitchscene.h \
    graphicsscene/ac_scaledscene.h \
    graphicsscene/ac_scenemanager.h \
    graphicsscene/ac_scorescene.h \
    graphicsscene/ac_timescene.h \
    graphicsscene/ac_valuescene.h \
    \
    graphicsview/ac_controlview.h \
    graphicsview/ac_editorview.h \
    graphicsview/ac_graphicsview.h \
    graphicsview/ac_pitchview.h \
    graphicsview/ac_scoreview.h \
    graphicsview/ac_timeview.h \
    graphicsview/ac_valueview.h \
    graphicsview/ac_viewmanager.h \
    \
    implementations/ac_editorimpl.h \
    implementations/ac_mainwindowimpl.h \
    \
    ac_guiconstants.h \
    ac_guiplugin.h \
    ac_mainwidget.h \
    ac_scene_util.h \

SOURCES += \
    graphicsitem/ac_graphicsbarlineitem.cpp \
    graphicsitem/ac_graphicscontrolpointitem.cpp \
    graphicsitem/ac_graphicsgridlineitem.cpp \
    graphicsitem/ac_graphicsitem.cpp \
    graphicsitem/ac_graphicsnoteitem.cpp \
    graphicsitem/ac_graphicspointitem.cpp \
    graphicsitem/ac_graphicsscorepointitem.cpp \
    graphicsitem/ac_graphicstrackitem.cpp \
    graphicsitem/ac_graphicstuninglineitem.cpp \
    graphicsitem/ac_graphicsvaluelineitem.cpp \
    graphicsitem/ac_scaledgraphicsitem.cpp \
    \
    graphicsscene/ac_controlscene.cpp \
    graphicsscene/ac_graphicsscene.cpp \
    graphicsscene/ac_pitchscene.cpp \
    graphicsscene/ac_scaledscene.cpp \
    graphicsscene/ac_scenemanager.cpp \
    graphicsscene/ac_scorescene.cpp \
    graphicsscene/ac_timescene.cpp \
    graphicsscene/ac_valuescene.cpp \
    \
    graphicsview/ac_controlview.cpp \
    graphicsview/ac_editorview.cpp \
    graphicsview/ac_graphicsview.cpp \
    graphicsview/ac_pitchview.cpp \
    graphicsview/ac_scoreview.cpp \
    graphicsview/ac_timeview.cpp \
    graphicsview/ac_valueview.cpp \
    graphicsview/ac_viewmanager.cpp \
    \
    implementations/ac_editorimpl.cpp \
    implementations/ac_mainwindowimpl.cpp \
    \
    ac_guiplugin.cpp \
    ac_mainwidget.cpp \

RESOURCES = ac_gui.qrc

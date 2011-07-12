TARGET = AC_Scene
TEMPLATE = lib

include(../../plugin.pri)
include(ac_sceneplugin_dependencies.pri)

DEFINES += AC_SCENE_LIBRARY

HEADERS += \
    implementations/ac_sceneimpl.h \
    \
    items/ac_graphicsbarlineitem.h \
    items/ac_graphicsgridlineitem.h \
    items/ac_graphicsnoteitem.h \
    items/ac_graphicstrackitem.h \
    items/ac_graphicstuninglineitem.h \
    items/ac_graphicsvaluelineitem.h \
    \
    scenes/ac_controlscene.h \
    scenes/ac_graphicsscene.h \
    scenes/ac_pitchscene.h \
    scenes/ac_scaledscene.h \
    scenes/ac_scenemanager.h \
    scenes/ac_scorescene.h \
    scenes/ac_timescene.h \
    scenes/ac_valuescene.h \
    \
    ac_scene_common.h \
    ac_scene_global.h \
    ac_sceneplugin.h \

SOURCES += \
    implementations/ac_sceneimpl.cpp \
    \
    items/ac_graphicsbarlineitem.cpp \
    items/ac_graphicsgridlineitem.cpp \
    items/ac_graphicsnoteitem.cpp \
    items/ac_graphicstrackitem.cpp \
    items/ac_graphicstuninglineitem.cpp \
    items/ac_graphicsvaluelineitem.cpp \
    \
    scenes/ac_controlscene.cpp \
    scenes/ac_graphicsscene.cpp \
    scenes/ac_pitchscene.cpp \
    scenes/ac_scaledscene.cpp \
    scenes/ac_scenemanager.cpp \
    scenes/ac_scorescene.cpp \
    scenes/ac_timescene.cpp \
    scenes/ac_valuescene.cpp \
    \
    ac_sceneplugin.cpp \

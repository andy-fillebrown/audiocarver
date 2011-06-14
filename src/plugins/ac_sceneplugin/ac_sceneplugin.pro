TARGET = AC_Scene
TEMPLATE = lib

include(../../plugin.pri)
include(ac_sceneplugin_dependencies.pri)

DEFINES += AC_SCENE_LIBRARY

HEADERS += \
    implementations/ac_sceneimpl.h \
    \
    items/ac_barlineitem.h \
    items/ac_guidelineitem.h \
    items/ac_tuningitem.h \
    \
    scenes/ac_graphicsscene.h \
    scenes/ac_pitchscene.h \
    scenes/ac_scorescene.h \
    scenes/ac_timescene.h \
    \
    ac_scene_global.h \
    ac_sceneplugin.h \

SOURCES += \
    implementations/ac_sceneimpl.cpp \
    \
    items/ac_barlineitem.cpp \
    items/ac_guidelineitem.cpp \
    items/ac_tuningitem.cpp \
    \
    scenes/ac_graphicsscene.cpp \
    scenes/ac_pitchscene.cpp \
    scenes/ac_scorescene.cpp \
    scenes/ac_timescene.cpp \
    \
    ac_sceneplugin.cpp \

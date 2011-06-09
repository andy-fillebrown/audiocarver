TARGET = AC_Scene
TEMPLATE = lib

include(../../plugin.pri)
include(ac_sceneplugin_dependencies.pri)

DEFINES += AC_SCENE_LIBRARY

HEADERS += \
    classes/ac_graphicsscene.h \
    classes/ac_pitchscene.h \
    classes/ac_scorescene.h \
    classes/ac_timescene.h \
#    classes/ac_volumescene.h \
    \
    implementations/ac_sceneimpl.h \
    \
    ac_scene_global.h \
    ac_sceneplugin.h \

SOURCES += \
    classes/ac_graphicsscene.cpp \
    classes/ac_pitchscene.cpp \
    classes/ac_scorescene.cpp \
    classes/ac_timescene.cpp \
#    classes/ac_volumescene.cpp \
    \
    implementations/ac_sceneimpl.cpp \
    \
    ac_sceneplugin.cpp \

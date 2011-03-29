TARGET = AC_Scene
TEMPLATE = lib

include(../../plugin.pri)
include(ac_sceneplugin_dependencies.pri)

DEFINES += AC_SCENE_LIBRARY

HEADERS += \
    classes/ac_graphicsscene.h \
    \
    implementations/ac_sceneimpl.h \
    \
    ac_scene_global.h \
    ac_sceneplugin.h \

SOURCES += \
    classes/ac_graphicsscene.cpp \
    \
    implementations/ac_sceneimpl.cpp \
    \
    ac_sceneplugin.cpp \

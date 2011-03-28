TARGET = AC_Scene
TEMPLATE = lib

include(../../plugin.pri)
include(ac_sceneplugin_dependencies.pri)

DEFINES += AC_SCENE_LIBRARY

HEADERS += \
    classes/graphicsscene.h \
    \
    implementations/sceneimpl.h \
    \
    ac_scene_global.h \
    ac_sceneplugin.h \

SOURCES += \
    classes/graphicsscene.cpp \
    \
    implementations/sceneimpl.cpp \
    \
    ac_sceneplugin.cpp \

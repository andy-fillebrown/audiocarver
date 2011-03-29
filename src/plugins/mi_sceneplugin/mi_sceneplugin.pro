TARGET = MI_Scene
TEMPLATE = lib

include(../../plugin.pri)
include(mi_sceneplugin_dependencies.pri)

DEFINES += MI_SCENE_LIBRARY

HEADERS += \
    classes/mi_graphicsscene.h \
    \
    interfaces/mi_iscene.h \
    \
    mi_scene_global.h \
    mi_sceneplugin.h \

SOURCES += \
    classes/mi_graphicsscene.cpp \
    \
    interfaces/mi_iscene.cpp \
    \
    mi_sceneplugin.cpp \

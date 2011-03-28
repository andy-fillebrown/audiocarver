TARGET = Scene
TEMPLATE = lib

include(../../plugin.pri)
include(sceneplugin_dependencies.pri)

DEFINES += SCENE_LIBRARY

HEADERS += \
    classes/graphicsscene.h \
    \
    interfaces/iscene.h \
    \
    scene_global.h \
    sceneplugin.h \

SOURCES += \
    classes/graphicsscene.cpp \
    \
    interfaces/iscene.cpp \
    \
    sceneplugin.cpp \

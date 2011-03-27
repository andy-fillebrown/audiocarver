TARGET = Scene
TEMPLATE = lib

include(../../plugin.pri)
include(sceneplugin_dependencies.pri)

DEFINES += SCENE_LIBRARY

HEADERS += \
    interfaces/iscene.h \
    \
    scene_global.h \
    sceneplugin.h \

SOURCES += \
    interfaces/iscene.cpp \
    \
    sceneplugin.cpp \

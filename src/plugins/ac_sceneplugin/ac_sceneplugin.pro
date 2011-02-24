TARGET = AC_Scene
TEMPLATE = lib

QT += opengl

include(../../projectplugin.pri)
include(ac_sceneplugin_dependencies.pri)

DEFINES += AC_SCENE_LIBRARY

HEADERS += \
	implementations/scene.h \
	\
	ac_scene_global.h \
	ac_sceneplugin.h

SOURCES += \
	implementations/scene.cpp \
	\
	ac_sceneplugin.cpp

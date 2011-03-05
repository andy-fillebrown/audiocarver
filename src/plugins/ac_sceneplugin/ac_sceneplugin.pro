TARGET = AC_Scene
TEMPLATE = lib

QT += opengl

include(../../projectplugin.pri)
include(ac_sceneplugin_dependencies.pri)

DEFINES += AC_SCENE_LIBRARY

HEADERS += \
	classes/fcurvenode.h \
	classes/node.h \
	classes/notenode.h \
	classes/scorenode.h \
	classes/tracknode.h \
	\
	implementations/scene.h \
	\
	ac_scene_global.h \
	ac_sceneplugin.h

SOURCES += \
	classes/fcurvenode.cpp \
	classes/node.cpp \
	classes/notenode.cpp \
	classes/scorenode.cpp \
	classes/tracknode.cpp \
	\
	implementations/scene.cpp \
	\
	ac_sceneplugin.cpp

RESOURCES = \
	ac_scene.qrc

OTHER_FILES = \
	shaders/note_fragment.glsl \
	shaders/note_vertex.glsl

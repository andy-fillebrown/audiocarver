TARGET = AC_Scene
TEMPLATE = lib

QT += opengl

include(../../projectplugin.pri)
include(ac_sceneplugin_dependencies.pri)

DEFINES += AC_SCENE_LIBRARY

HEADERS += \
	classes/scene_fcurve.h \
	classes/scene_note.h \
	classes/scene_score.h \
	classes/scene_track.h \
	\
	implementations/scene.h \
	\
	ac_scene_global.h \
	ac_sceneplugin.h

SOURCES += \
	classes/scene_fcurve.cpp \
	classes/scene_note.cpp \
	classes/scene_score.cpp \
	classes/scene_track.cpp \
	\
	implementations/scene.cpp \
	\
	ac_sceneplugin.cpp

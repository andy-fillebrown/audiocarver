TARGET = AC_Scene
TEMPLATE = lib

QT += opengl

include(../../projectplugin.pri)
include(ac_sceneplugin_dependencies.pri)

DEFINES += AC_SCENE_LIBRARY

HEADERS += \
	classes/fcurvescene.h \
	classes/notescene.h \
	classes/sceneobject.h \
	classes/scorescene.h \
	classes/trackscene.h \
	\
	implementations/scene.h \
	\
	ac_scene_global.h \
	ac_sceneplugin.h

SOURCES += \
	classes/fcurvescene.cpp \
	classes/notescene.cpp \
	classes/sceneobject.cpp \
	classes/scorescene.cpp \
	classes/trackscene.cpp \
	\
	implementations/scene.cpp \
	\
	ac_sceneplugin.cpp

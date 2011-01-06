TARGET = AC_Editor
TEMPLATE = lib

include(../../projectplugin.pri)
include(ac_editorplugin_dependencies.pri)

DEFINES += AC_EDITOR_LIBRARY

HEADERS += \
	ac_editor_global.h \
	ac_editorconstants.h \
	ac_editorplugin.h

SOURCES += \
	ac_editorplugin.cpp

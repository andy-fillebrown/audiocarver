TARGET = AC_Editor
TEMPLATE = lib

include(../../projectplugin.pri)
include(ac_editorplugin_dependencies.pri)

DEFINES += AC_EDITOR_LIBRARY

HEADERS += \
    implementations/editor.h \
    \
    ac_editor_global.h \
    ac_editorconstants.h \
    ac_editorplugin.h

SOURCES += \
    implementations/editor.cpp \
    \
    ac_editorplugin.cpp

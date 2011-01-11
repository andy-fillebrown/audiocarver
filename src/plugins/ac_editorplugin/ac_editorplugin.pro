TARGET = AC_Editor
TEMPLATE = lib

include(../../projectplugin.pri)
include(ac_editorplugin_dependencies.pri)

DEFINES += AC_EDITOR_LIBRARY

HEADERS += \
    implementations/ac_editorimpl.h \
    implementations/ac_editor3dimpl.h \
    implementations/ac_mainwindowimpl.h \
    \
    ac_editor.h \
    ac_editor_global.h \
    ac_editorconstants.h \
    ac_editorplugin.h

SOURCES += \
    implementations/ac_editorimpl.cpp \
    implementations/ac_editor3dimpl.cpp \
    implementations/ac_mainwindowimpl.cpp \
    \
    ac_editor.cpp \
    ac_editorplugin.cpp

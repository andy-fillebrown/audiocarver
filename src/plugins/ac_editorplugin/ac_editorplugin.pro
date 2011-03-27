TARGET = AC_Editor
TEMPLATE = lib

include(../../plugin.pri)
include(ac_editorplugin_dependencies.pri)

DEFINES += AC_EDITOR_LIBRARY

HEADERS += \
    implementations/editorimpl.h \
    implementations/mainwindowimpl.h \
    \
    ac_editor_global.h \
    ac_editorconstants.h \
    ac_editorplugin.h \

SOURCES += \
    implementations/editorimpl.cpp \
    implementations/mainwindowimpl.cpp \
    \
    ac_editorplugin.cpp \

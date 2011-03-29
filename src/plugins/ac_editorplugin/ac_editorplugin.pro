TARGET = AC_Editor
TEMPLATE = lib

include(../../plugin.pri)
include(ac_editorplugin_dependencies.pri)

DEFINES += AC_EDITOR_LIBRARY

HEADERS += \
    classes/ac_mainwidget.h \
    \
    implementations/ac_editorimpl.h \
    implementations/ac_mainwindowimpl.h \
    \
    ac_editor_global.h \
    ac_editorconstants.h \
    ac_editorplugin.h \

SOURCES += \
    classes/ac_mainwidget.cpp \
    \
    implementations/ac_editorimpl.cpp \
    implementations/ac_mainwindowimpl.cpp \
    \
    ac_editorplugin.cpp \

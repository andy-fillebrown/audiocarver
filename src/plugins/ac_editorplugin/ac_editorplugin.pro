TARGET = AC_Editor
TEMPLATE = lib

include(../../plugin.pri)
include(ac_editorplugin_dependencies.pri)

DEFINES += AC_EDITOR_LIBRARY

HEADERS += \
    classes/ac_controllerview.h \
    classes/ac_graphicsview.h \
    classes/ac_mainwidget.h \
    classes/ac_pitchview.h \
    classes/ac_scoreview.h \
    classes/ac_timeview.h \
    classes/ac_viewmanager.h \
    \
    implementations/ac_editorimpl.h \
    implementations/ac_mainwindowimpl.h \
    \
    ac_editor_global.h \
    ac_editorconstants.h \
    ac_editorplugin.h \

SOURCES += \
    classes/ac_controllerview.cpp \
    classes/ac_graphicsview.cpp \
    classes/ac_mainwidget.cpp \
    classes/ac_pitchview.cpp \
    classes/ac_scoreview.cpp \
    classes/ac_timeview.cpp \
    classes/ac_viewmanager.cpp \
    \
    implementations/ac_editorimpl.cpp \
    implementations/ac_mainwindowimpl.cpp \
    \
    ac_editorplugin.cpp \

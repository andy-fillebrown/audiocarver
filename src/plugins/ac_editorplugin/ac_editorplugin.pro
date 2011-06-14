TARGET = AC_Editor
TEMPLATE = lib

include(../../plugin.pri)
include(ac_editorplugin_dependencies.pri)

DEFINES += AC_EDITOR_LIBRARY

HEADERS += \
    classes/ac_graphicsview.h \
    classes/ac_graphicsviewmanager.h \
    classes/ac_mainwidget.h \
    classes/ac_pitchgraphicsview.h \
    classes/ac_scoregraphicsview.h \
    classes/ac_timegraphicsview.h \
    \
    implementations/ac_editorimpl.h \
    implementations/ac_mainwindowimpl.h \
    \
    ac_editor_global.h \
    ac_editorconstants.h \
    ac_editorplugin.h \

SOURCES += \
    classes/ac_graphicsview.cpp \
    classes/ac_graphicsviewmanager.cpp \
    classes/ac_mainwidget.cpp \
    classes/ac_pitchgraphicsview.cpp \
    classes/ac_scoregraphicsview.cpp \
    classes/ac_timegraphicsview.cpp \
    \
    implementations/ac_editorimpl.cpp \
    implementations/ac_mainwindowimpl.cpp \
    \
    ac_editorplugin.cpp \

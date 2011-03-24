TARGET = AC_Editor
TEMPLATE = lib

QT += opengl

include(../../projectplugin.pri)
include(ac_editorplugin_dependencies.pri)

DEFINES += AC_EDITOR_LIBRARY

HEADERS += \
    classes/ac_editorwidget.h \
    \
    implementations/ac_editorimpl.h \
    implementations/ac_gleditorimpl.h \
    implementations/ac_mainwindowimpl.h \
    \
    ac_editor_global.h \
    ac_editorconstants.h \
    ac_editorplugin.h

SOURCES += \
    classes/ac_editorwidget.cpp \
    \
    implementations/ac_editorimpl.cpp \
    implementations/ac_gleditorimpl.cpp \
    implementations/ac_mainwindowimpl.cpp \
    \
    ac_editorplugin.cpp

OTHER_FILES += \
    classes/*.* \
    implementations/*.* \
    *.*

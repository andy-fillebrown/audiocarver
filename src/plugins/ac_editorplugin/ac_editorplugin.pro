TARGET = AC_Editor
TEMPLATE = lib

QT += opengl

include(../../projectplugin.pri)
include(ac_editorplugin_dependencies.pri)

DEFINES += AC_EDITOR_LIBRARY

HEADERS += \
    classes/widget.h \
    \
    implementations/editorimpl.h \
    implementations/gleditorimpl.h \
    implementations/mainwindowimpl.h \
    \
    ac_editor_global.h \
    ac_editorconstants.h \
    ac_editorplugin.h

SOURCES += \
    classes/widget.cpp \
    \
    implementations/editorimpl.cpp \
    implementations/gleditorimpl.cpp \
    implementations/mainwindowimpl.cpp \
    \
    ac_editorplugin.cpp

OTHER_FILES += \
    classes/*.* \
    implementations/*.* \
    *.*

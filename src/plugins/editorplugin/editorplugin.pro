TARGET = Editor
TEMPLATE = lib

include(../../plugin.pri)
include(editorplugin_dependencies.pri)

DEFINES += EDITOR_LIBRARY

HEADERS += \
    implementations/mainwindowimpl.h \
    \
    interfaces/ieditor.h \
    \
    editor_global.h \
    editorconstants.h \
    editorplugin.h \

SOURCES += \
    implementations/mainwindowimpl.cpp \
    \
    interfaces/ieditor.cpp \
    \
    editorplugin.cpp \

RESOURCES += editor.qrc

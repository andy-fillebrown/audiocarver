TARGET = MI_Editor
TEMPLATE = lib

include(../../plugin.pri)
include(mi_editorplugin_dependencies.pri)

DEFINES += MI_EDITOR_LIBRARY

HEADERS += \
    classes/mi_graphicsview.h \
    \
    implementations/mi_mainwindowimpl.h \
    \
    interfaces/mi_ieditor.h \
    \
    mi_editor_global.h \
    mi_editorconstants.h \
    mi_editorplugin.h \

SOURCES += \
    classes/mi_graphicsview.cpp \
    \
    implementations/mi_mainwindowimpl.cpp \
    \
    interfaces/mi_ieditor.cpp \
    \
    mi_editorplugin.cpp \

RESOURCES += mi_editor.qrc

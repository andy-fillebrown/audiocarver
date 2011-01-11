TARGET = Editor
TEMPLATE = lib

include(../../projectplugin.pri)
include(../coreplugin/coreplugin.pri)
include(editorplugin_dependencies.pri)

DEFINES += EDITOR_LIBRARY

HEADERS += \
    implementations/editormainwindowimpl.h \
    \
    interfaces/ieditor.h \
    \
    editor_global.h \
    editorconstants.h \
    editorplugin.h

SOURCES += \
    implementations/editormainwindowimpl.cpp \
    \
    interfaces/ieditor.cpp \
    \
    editorplugin.cpp

RESOURCES += \
    editor.qrc

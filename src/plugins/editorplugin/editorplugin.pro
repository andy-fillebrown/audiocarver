TEMPLATE = lib
TARGET   = Editor

include(../../projectplugin.pri)
include(../coreplugin/coreplugin.pri)
include(editorplugin_dependencies.pri)

DEFINES += EDITOR_LIBRARY

SOURCES += \
    editorplugin.cpp

HEADERS += \
    editor_global.h \
    editorconstants.h \
    editorplugin.h

RESOURCES += \
    editor.qrc

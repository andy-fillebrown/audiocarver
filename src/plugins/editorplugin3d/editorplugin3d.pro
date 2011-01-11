TARGET = Editor3D
TEMPLATE = lib

include(../../projectplugin.pri)
include(editorplugin3d_dependencies.pri)

DEFINES += EDITOR3D_LIBRARY

HEADERS += \
    implementations/editor3dmainwindowimpl.h \
    \
    interfaces/ieditor3d.h \
    interfaces/iviewport3d.h \
    \
    editor3d_global.h \
    editor3dconstants.h \
    editorplugin3d.h

SOURCES += \
    implementations/editor3dmainwindowimpl.cpp \
    \
    interfaces/ieditor3d.cpp \
    interfaces/iviewport3d.cpp \
    \
    editorplugin3d.cpp

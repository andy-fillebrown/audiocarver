TARGET = Editor3D
TEMPLATE = lib

QT += opengl

include(../../projectplugin.pri)
include(editorplugin3d_dependencies.pri)

DEFINES += EDITOR3D_LIBRARY

HEADERS += \
    classes/centralwidget3d.h \
    classes/viewport3d.h \
    \
    implementations/editor3dmainwindowimpl.h \
    \
    interfaces/ieditor3d.h \
    interfaces/iviewport3d.h \
    \
    editor3d_global.h \
    editor3dconstants.h \
    editorplugin3d.h

SOURCES += \
    classes/centralwidget3d.cpp \
    classes/viewport3d.cpp \
    \
    implementations/editor3dmainwindowimpl.cpp \
    \
    interfaces/ieditor3d.cpp \
    interfaces/iviewport3d.cpp \
    \
    editorplugin3d.cpp

RESOURCES += \
    editor3d.qrc

OTHER_FILES += \
    shaders/centralwidget3d_fragment.glsl \
    shaders/centralwidget3d_vertex.glsl

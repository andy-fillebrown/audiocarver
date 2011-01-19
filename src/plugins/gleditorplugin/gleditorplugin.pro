TARGET = GLEditor
TEMPLATE = lib

QT += opengl

include(../../projectplugin.pri)
include(gleditorplugin_dependencies.pri)

DEFINES += GLEDITOR_LIBRARY

HEADERS += \
    classes/glviewport.h \
    classes/glwidget.h \
    classes/glwidgetsplit.h \
    \
    implementations/gleditor_mainwindowimpl.h \
    \
    interfaces/igleditor.h \
    \
    gleditor_global.h \
    gleditorconstants.h \
    gleditorplugin.h

SOURCES += \
    classes/glviewport.cpp \
    classes/glwidget.cpp \
    classes/glwidgetsplit.cpp \
    \
    implementations/gleditor_mainwindowimpl.cpp \
    \
    interfaces/igleditor.cpp \
    \
    gleditorplugin.cpp

RESOURCES += \
    gleditor.qrc

OTHER_FILES += \
    shaders/glwidget_fragment.glsl \
    shaders/glwidget_vertex.glsl

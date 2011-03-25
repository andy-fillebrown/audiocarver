TARGET = GLScene
TEMPLATE = lib

QT += opengl

include(../../projectplugin.pri)
include(glsceneplugin_dependencies.pri)

DEFINES += GLSCENE_LIBRARY

HEADERS += \
    classes/buffer.h \
    classes/node.h \
    classes/root.h \
    classes/scene.h \
    \
    interfaces/iscene.h \
    \
    glscene_global.h \
    glsceneplugin.h

SOURCES += \
    classes/buffer.cpp \
    classes/node.cpp \
    classes/root.cpp \
    classes/scene.cpp \
    \
    interfaces/iscene.cpp \
    \
    glsceneplugin.cpp

RESOURCES += \

OTHER_FILES += \
    classes/*.* \
    interfaces/*.* \
    *.*

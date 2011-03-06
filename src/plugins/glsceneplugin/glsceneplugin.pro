TARGET = GLScene
TEMPLATE = lib

QT += opengl

include(../../projectplugin.pri)
include(glsceneplugin_dependencies.pri)

DEFINES += GLSCENE_LIBRARY

HEADERS += \
    classes/glbuffer.h \
    classes/glnode.h \
    classes/glroot.h \
    \
    interfaces/iglscene.h \
    \
    glscene_global.h \
    glsceneplugin.h

SOURCES += \
    classes/glbuffer.cpp \
    classes/glnode.cpp \
    classes/glroot.cpp \
    \
    interfaces/iglscene.cpp \
    \
    glsceneplugin.cpp

RESOURCES += \

OTHER_FILES += \

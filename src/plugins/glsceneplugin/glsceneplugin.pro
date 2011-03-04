TARGET = GLScene
TEMPLATE = lib

QT -= gui

include(../../projectplugin.pri)
include(glsceneplugin_dependencies.pri)

DEFINES += GLSCENE_LIBRARY

HEADERS += \
    classes/glbuffer.h \
    classes/globject.h \
    classes/glroot.h \
    classes/glsubarray.h \
    \
    interfaces/iglscene.h \
    \
    glscene_global.h \
    glsceneplugin.h

SOURCES += \
    classes/glbuffer.cpp \
    classes/globject.cpp \
    classes/glroot.cpp \
    classes/glsubarray.cpp \
    \
    interfaces/iglscene.cpp \
    \
    glsceneplugin.cpp

RESOURCES += \

OTHER_FILES += \

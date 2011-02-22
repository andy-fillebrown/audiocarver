TARGET = GLScene
TEMPLATE = lib

QT -= gui

include(../../projectplugin.pri)
include(glsceneplugin_dependencies.pri)

DEFINES += GLSCENE_LIBRARY

HEADERS += \
    interfaces/iglscene.h \
    \
    glscene_global.h \
    glsceneplugin.h

SOURCES += \
    interfaces/iglscene.cpp \
    \
    glsceneplugin.cpp

RESOURCES += \

OTHER_FILES += \

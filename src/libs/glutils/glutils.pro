TARGET   = GLUtils
TEMPLATE = lib

QT *= gui opengl

include(../../projectlibrary.pri)

DEFINES += GLUTILS_LIB

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    glutils_global.h

SOURCES += \

OTHER_FILES += \
    *.*

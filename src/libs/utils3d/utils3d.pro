TARGET   = Utils3D
TEMPLATE = lib

QT *= gui opengl

include(../../projectlibrary.pri)

DEFINES += UTILS3D_LIB

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    utils3d_global.h

SOURCES += \

OTHER_FILES += utils3d.pri

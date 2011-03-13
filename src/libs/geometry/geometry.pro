TARGET   = Geometry
TEMPLATE = lib

QT -= gui

include(../../projectlibrary.pri)

DEFINES += GEOMETRY_LIB

INCLUDEPATH += include
DEPENDPATH += include

HEADERS += \
    classes/axisalignedbox.h \
    classes/frustum.h \
    classes/helper.h \
    classes/linesegment.h \
    classes/matrix.h \
    classes/plane.h \
    classes/point.h \
    classes/ray.h \
    classes/sphere.h \
    classes/vector.h \
    \
    geometry_global.h

SOURCES += \
    classes/axisalignedbox.cpp \
    classes/frustum.cpp \
    classes/linesegment.cpp \
    classes/matrix.cpp \
    classes/plane.cpp \
    classes/point.cpp \
    classes/ray.cpp \
    classes/sphere.cpp \
    classes/vector.cpp

OTHER_FILES += \
    geometry.pri \
    \
    $$files(include/gmtl/*.h) \
    $$files(include/gmtl/External/*.h) \
    $$files(include/gmtl/Fit/*.h) \
    $$files(include/gmtl/Misc/*.h) \
    $$files(include/gmtl/Numerics/*.h) \
    $$files(include/gmtl/Util/*.h)

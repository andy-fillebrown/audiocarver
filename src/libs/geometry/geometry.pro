TARGET   = Geometry
TEMPLATE = lib

QT -= gui

include(../../projectlibrary.pri)

DEFINES += GEOMETRY_LIB

INCLUDEPATH += include
DEPENDPATH += include

HEADERS += \
#    classes/axisalignedbox.h \
#    classes/axisangle.h \
#    classes/axisanglecoord.h \
#    classes/cubiccurve.h \
#    classes/eulerangle.h \
#    classes/euleranglecoord.h \
#    classes/frustum.h \
#    classes/linearcurve.h \
#    classes/linesegment.h \
    classes/matrix4x4.h \
#    classes/plane.h \
    classes/point2d.h \
    classes/point3d.h \
    classes/point4d.h \
#    classes/quadraticcurve.h \
#    classes/quaternion.h \
#    classes/quaternioncoord.h \
#    classes/ray.h \
#    classes/sphere.h \
#    classes/sweptaxisalignedbox.h \
#    classes/sweptsphere.h \
#    classes/triangle.h \
    classes/vector2d.h \
    classes/vector3d.h \
    classes/vector4d.h \
    \
    geometry_global.h \
    helper.h \

SOURCES += \
#    classes/axisalignedbox.cpp \
#    classes/axisangle.cpp \
#    classes/axisanglecoord.cpp \
#    classes/cubiccurve.cpp \
#    classes/eulerangle.cpp \
#    classes/euleranglecoord.cpp \
#    classes/frustum.cpp \
#    classes/linearcurve.cpp \
#    classes/linesegment.cpp \
    classes/matrix4x4.cpp \
#    classes/plane.cpp \
    classes/point2d.cpp \
    classes/point3d.cpp \
    classes/point4d.cpp \
#    classes/quadraticcurve.cpp \
#    classes/quaternion.cpp \
#    classes/quaternioncoord.cpp \
#    classes/ray.cpp \
#    classes/sphere.cpp \
#    classes/sweptaxisalignedbox.cpp \
#    classes/sweptsphere.cpp \
#    classes/triangle.cpp \
    classes/vector2d.cpp \
    classes/vector3d.cpp \
    classes/vector4d.cpp \

OTHER_FILES += \
    geometry.pri \
    \
#    $$files(include/gmtl/*.h) \
#    $$files(include/gmtl/External/*.h) \
#    $$files(include/gmtl/Fit/*.h) \
#    $$files(include/gmtl/Misc/*.h) \
#    $$files(include/gmtl/Numerics/*.h) \
#    $$files(include/gmtl/Util/*.h)

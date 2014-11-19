TARGET   = Utils
TEMPLATE = lib
QT *= widgets

include(../../library.prf)

DEFINES += UTILS_LIB

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS = \
    basevalidatinglineedit.h \
    environment.h \
    fancylineedit.h \
    filenamevalidatinglineedit.h \
    filterlineedit.h \
    pathchooser.h \
    stringutils.h \
    treewidgetcolumnstretcher.h \
    utils_global.h \

SOURCES = \
    basevalidatinglineedit.cpp \
    environment.cpp \
    fancylineedit.cpp \
    filenamevalidatinglineedit.cpp \
    filterlineedit.cpp \
    pathchooser.cpp \
    stringutils.cpp \
    treewidgetcolumnstretcher.cpp \

OTHER_FILES *= \
    utils.prf \

unix: !macx {
    HEADERS *= unixutils.h
    SOURCES *= unixutils.cpp
}

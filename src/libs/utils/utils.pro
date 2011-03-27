TARGET   = Utils
TEMPLATE = lib

include(../../library.pri)

DEFINES += UTILS_LIB

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    basevalidatinglineedit.h \
    environment.h \
    fancylineedit.h \
    filenamevalidatinglineedit.h \
    filterlineedit.h \
    pathchooser.h \
    stringutils.h \
    treewidgetcolumnstretcher.h \
    utils_global.h \

SOURCES += \
    basevalidatinglineedit.cpp \
    environment.cpp \
    fancylineedit.cpp \
    filenamevalidatinglineedit.cpp \
    filterlineedit.cpp \
    pathchooser.cpp \
    stringutils.cpp \
    treewidgetcolumnstretcher.cpp \

unix: !macx {
    HEADERS += unixutils.h
    SOURCES += unixutils.cpp
}

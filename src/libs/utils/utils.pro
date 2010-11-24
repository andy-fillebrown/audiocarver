TEMPLATE = lib
TARGET   = Utils
QT += gui

CONFIG += dll
include(../../projectlibrary.pri)

dll {
    DEFINES += QTCREATOR_UTILS_LIB
} else {
    DEFINES += QTCREATOR_UTILS_STATIC_LIB
}

INCLUDEPATH += $$PWD

SOURCES += \
    basevalidatinglineedit.cpp \
    environment.cpp \
    fancylineedit.cpp \
    filenamevalidatinglineedit.cpp \
    filterlineedit.cpp \
    pathchooser.cpp \
    qtcolorbutton.cpp \
    stringutils.cpp \
    treewidgetcolumnstretcher.cpp

HEADERS += \
    basevalidatinglineedit.h \
    environment.h \
    fancylineedit.h \
    filenamevalidatinglineedit.h \
    filterlineedit.h \
    pathchooser.h \
    qtcolorbutton.h \
    stringutils.h \
    treewidgetcolumnstretcher.h \
    utils_global.h

OTHER_FILES += utils.pri

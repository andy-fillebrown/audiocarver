dll {
    DEFINES += QTCREATOR_UTILS_LIB
} else {
    DEFINES += QTCREATOR_UTILS_STATIC_LIB
}

INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/environment.cpp \
    $$PWD/stringutils.cpp \
    $$PWD/pathchooser.cpp \
    $$PWD/basevalidatinglineedit.cpp \
    $$PWD/filenamevalidatinglineedit.cpp \
    $$PWD/fancylineedit.cpp \
    $$PWD/qtcolorbutton.cpp \
    $$PWD/treewidgetcolumnstretcher.cpp \
    $$PWD/filterlineedit.cpp \

HEADERS += \
    $$PWD/environment.h \
    $$PWD/utils_global.h \
    $$PWD/stringutils.h \
    $$PWD/pathchooser.h \
    $$PWD/basevalidatinglineedit.h \
    $$PWD/filenamevalidatinglineedit.h \
    $$PWD/fancylineedit.h \
    $$PWD/qtcolorbutton.h \
    $$PWD/treewidgetcolumnstretcher.h \
    $$PWD/filterlineedit.h \

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
    $$PWD/wizard.cpp \
    $$PWD/filewizardpage.cpp \
    $$PWD/filewizarddialog.cpp \
    $$PWD/basevalidatinglineedit.cpp \
    $$PWD/filenamevalidatinglineedit.cpp \
    $$PWD/fancylineedit.cpp \
    $$PWD/qtcolorbutton.cpp \
    $$PWD/treewidgetcolumnstretcher.cpp \
    $$PWD/styledbar.cpp \
    $$PWD/stylehelper.cpp \
    $$PWD/fancymainwindow.cpp \
    $$PWD/filterlineedit.cpp \

HEADERS += \
    $$PWD/environment.h \
    $$PWD/utils_global.h \
    $$PWD/stringutils.h \
    $$PWD/pathchooser.h \
    $$PWD/wizard.h \
    $$PWD/filewizardpage.h \
    $$PWD/filewizarddialog.h \
    $$PWD/basevalidatinglineedit.h \
    $$PWD/filenamevalidatinglineedit.h \
    $$PWD/fancylineedit.h \
    $$PWD/qtcolorbutton.h \
    $$PWD/treewidgetcolumnstretcher.h \
    $$PWD/styledbar.h \
    $$PWD/stylehelper.h \
    $$PWD/fancymainwindow.h \
    $$PWD/filterlineedit.h \

FORMS += \
    $$PWD/filewizardpage.ui \

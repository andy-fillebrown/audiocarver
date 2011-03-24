TARGET = GLEditor
TEMPLATE = lib

QT += opengl

include(../../projectplugin.pri)
include(gleditorplugin_dependencies.pri)

DEFINES += GLEDITOR_LIBRARY

HEADERS += \
    classes/viewport.h \
    classes/widget.h \
    classes/widget_p.h \
    classes/widgetsplit.h \
    \
    dialogs/behaviorsettingspage.h \
    dialogs/displaysettingspage.h \
    \
    implementations/mainwindowimpl.h \
    \
    interfaces/ieditor.h \
    \
    settings/behaviorsettings.h \
    settings/displaysettings.h \
    \
    gleditor_global.h \
    gleditorconstants.h \
    gleditorplugin.h

SOURCES += \
    classes/viewport.cpp \
    classes/widget.cpp \
    classes/widget_p.cpp \
    classes/widgetsplit.cpp \
    \
    dialogs/behaviorsettingspage.cpp \
    dialogs/displaysettingspage.cpp \
    \
    implementations/mainwindowimpl.cpp \
    \
    interfaces/ieditor.cpp \
    \
    settings/behaviorsettings.cpp \
    settings/displaysettings.cpp \
    \
    gleditorplugin.cpp

FORMS += \
    dialogs/behaviorsettingspage.ui \
    dialogs/displaysettingspage.ui

RESOURCES += \
    gleditor.qrc

OTHER_FILES += \
    classes/*.* \
    dialogs/*.* \
    images/*.* \
    implementations/*.* \
    interfaces/*.* \
    settings/*.* \
    shaders/*.* \
    *.*

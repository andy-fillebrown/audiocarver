TARGET = GLEditor
TEMPLATE = lib

QT += opengl

include(../../projectplugin.pri)
include(gleditorplugin_dependencies.pri)

DEFINES += GLEDITOR_LIBRARY

HEADERS += \
    classes/glviewport.h \
    classes/glwidget.h \
    classes/glwidget_p.h \
    classes/glwidgetsplit.h \
    \
    dialogs/behaviorsettingspage.h \
    dialogs/displaysettingspage.h \
    \
    implementations/gleditor_mainwindowimpl.h \
    \
    interfaces/igleditor.h \
    \
    settings/behaviorsettings.h \
    settings/displaysettings.h \
    \
    gleditor_global.h \
    gleditorconstants.h \
    gleditorplugin.h

SOURCES += \
    classes/glviewport.cpp \
    classes/glwidget.cpp \
    classes/glwidget_p.cpp \
    classes/glwidgetsplit.cpp \
    \
    dialogs/behaviorsettingspage.cpp \
    dialogs/displaysettingspage.cpp \
    \
    implementations/gleditor_mainwindowimpl.cpp \
    \
    interfaces/igleditor.cpp \
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
    *.* \
    $$HEADERS \
    $$SOURCES \
    $$FORMS \
    $$RESOURCES \
    shaders/glwidget_fragment.glsl \
    shaders/glwidget_vertex.glsl

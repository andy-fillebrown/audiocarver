TARGET = ExtensionSystem
TEMPLATE = lib
QT *= widgets

include(../../_.library.prf)
include(../extensionsystem/_.extensionsystem_dependencies.prf)

DEFINES *= \
    EXTENSIONSYSTEM_LIBRARY \

HEADERS = \
    pluginerrorview.h \
    plugindetailsview.h \
    iplugin.h \
    iplugin_p.h \
    extensionsystem_global.h \
    pluginmanager.h \
    pluginmanager_p.h \
    pluginspec.h \
    pluginspec_p.h \
    pluginview.h \
    pluginview_p.h \
    optionsparser.h \
    plugincollection.h \

SOURCES = \
    pluginerrorview.cpp \
    plugindetailsview.cpp \
    iplugin.cpp \
    pluginmanager.cpp \
    pluginspec.cpp \
    pluginview.cpp \
    optionsparser.cpp \
    plugincollection.cpp \

FORMS = \
    pluginview.ui \
    pluginerrorview.ui \
    plugindetailsview.ui \

RESOURCES = pluginview.qrc

OTHER_FILES *= \
    _.extensionsystem.prf \
    _.extensionsystem_dependencies.prf \

unix:!macx:!freebsd* {
    LIBS *= \
        -ldl \
}

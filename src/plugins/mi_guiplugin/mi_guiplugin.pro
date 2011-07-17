TARGET = MiGuiPlugin
TEMPLATE = lib

include(../../plugin.pri)
include(mi_guiplugin_dependencies.pri)

DEFINES += MI_GUI_LIBRARY

HEADERS += \
#    graphicsscene/mi_graphicsscene.h \
#    \
#    graphicsview/mi_graphicsview.h \
    \
    implementations/mi_mainwindowimpl.h \
    \
    interfaces/mi_ieditor.h \
    \
    mi_gui_global.h \
    mi_guiconstants.h \
    mi_guiplugin.h \

SOURCES += \
#    graphicsscene/mi_graphicsscene.cpp \
#    \
#    graphicsview/mi_graphicsview.cpp \
    \
    implementations/mi_mainwindowimpl.cpp \
    \
    interfaces/mi_ieditor.cpp \
    \
    mi_guiplugin.cpp \

RESOURCES += mi_gui.qrc

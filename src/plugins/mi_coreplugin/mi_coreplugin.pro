TARGET = MiCorePlugin
TEMPLATE = lib
QT -= gui

include(../../plugin.pri)
include(mi_coreplugin_dependencies.pri)

DEFINES += MI_CORE_LIBRARY

HEADERS += \
#    dataobjects/settings/mi_fontsettings.h \
#    \
#    dataobjects/mi_listobject.h \
#    dataobjects/mi_object.h \
#    dataobjects/mi_sortedlistobject.h \
#    \
#    factories/mi_dataobjectfactory.h \
#    factories/mi_filerfactory.h \
#    \
    interfaces/mi_idatabase.h \
    \
#    tools/mi_scopedsignalblocker.h \
#    tools/mi_scopedchange.h \
    \
    mi_core_global.h \
    mi_coreenums.h \
    mi_coreplugin.h \
    mi_propertyindexes.h \

SOURCES += \
#    dataobjects/settings/mi_fontsettings.cpp \
#    \
#    dataobjects/mi_listobject.cpp \
#    dataobjects/mi_object.cpp \
#    dataobjects/mi_sortedlistobject.cpp \
    \
#    factories/mi_dataobjectfactory.cpp \
#    factories/mi_filerfactory.cpp \
    \
    interfaces/mi_idatabase.cpp \
    \
#    tools/mi_scopedsignalblocker.cpp \
#    tools/mi_scopedchange.cpp \
    \
    mi_coreplugin.cpp \

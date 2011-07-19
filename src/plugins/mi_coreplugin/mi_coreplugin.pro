TARGET = MiCorePlugin
TEMPLATE = lib

include(../../plugin.pri)
include(mi_coreplugin_dependencies.pri)

DEFINES += MI_CORE_LIBRARY

HEADERS += \
    components/mi_propertybag.h \
    \
    dataobjects/mi_database.h \
    dataobjects/mi_font.h \
    dataobjects/mi_object.h \
    dataobjects/mi_objectlist.h \
    \
    interfaces/mi_idatabase.h \
    \
    tools/mi_scopedsignalblocker.h \
    \
    mi_core_global.h \
    mi_coreplugin.h \

SOURCES += \
    components/mi_propertybag.cpp \
    \
    dataobjects/mi_database.cpp \
    dataobjects/mi_font.cpp \
    dataobjects/mi_object.cpp \
    dataobjects/mi_objectlist.cpp \
    \
    interfaces/mi_idatabase.cpp \
    \
    tools/mi_scopedsignalblocker.cpp \
    \
    mi_coreplugin.cpp \

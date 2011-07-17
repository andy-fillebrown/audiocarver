TARGET = MiCorePlugin
TEMPLATE = lib

include(../../plugin.pri)
include(mi_coreplugin_dependencies.pri)

DEFINES += MI_CORE_LIBRARY

HEADERS += \
    database/mi_font.h \
    database/mi_link.h \
    database/mi_object.h \
    database/mi_objectlist.h \
    database/mi_root.h \
    database/mi_scopedsignalblocker.h \
    \
    interfaces/mi_idatabase.h \
    \
    mi_core_global.h \
    mi_coreplugin.h \

SOURCES += \
    database/mi_font.cpp \
    database/mi_link.cpp \
    database/mi_object.cpp \
    database/mi_objectlist.cpp \
    database/mi_root.cpp \
    database/mi_scopedsignalblocker.cpp \
    \
    interfaces/mi_idatabase.cpp \
    \
    mi_coreplugin.cpp \

TARGET = MI_Database
TEMPLATE = lib

include(../../plugin.pri)
include(mi_databaseplugin_dependencies.pri)

DEFINES += MI_DATABASE_LIBRARY

HEADERS += \
    interfaces/mi_idatabase.h \
    \
    classes/mi_link.h \
    classes/mi_list.h \
    classes/mi_object.h \
    classes/mi_root.h \
    \
    mi_database_global.h \
    mi_databaseplugin.h \

SOURCES += \
    interfaces/mi_idatabase.cpp \
    \
    classes/mi_link.cpp \
    classes/mi_list.cpp \
    classes/mi_object.cpp \
    classes/mi_root.cpp \
    \
    mi_databaseplugin.cpp \

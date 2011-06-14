TARGET = MI_Database
TEMPLATE = lib

include(../../plugin.pri)
include(mi_databaseplugin_dependencies.pri)

DEFINES += MI_DATABASE_LIBRARY

HEADERS += \
    interfaces/mi_idatabase.h \
    \
    classes/mi_font.h \
    classes/mi_link.h \
    classes/mi_list.h \
    classes/mi_object.h \
    classes/mi_objectlist.h \
    classes/mi_prioritylist.h \
    classes/mi_root.h \
    classes/mi_scopedsignalblocker.h \
    \
    mi_database_global.h \
    mi_databaseplugin.h \

SOURCES += \
    interfaces/mi_idatabase.cpp \
    \
    classes/mi_font.cpp \
    classes/mi_link.cpp \
    classes/mi_list.cpp \
    classes/mi_object.cpp \
    classes/mi_objectlist.cpp \
    classes/mi_prioritylist.cpp \
    classes/mi_root.cpp \
    classes/mi_scopedsignalblocker.cpp \
    \
    mi_databaseplugin.cpp \

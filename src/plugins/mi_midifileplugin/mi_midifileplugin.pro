TARGET = MiMidiFilePlugin
TEMPLATE = lib

load(../../plugin.prf)
load(../mi_midifileplugin/mi_midifileplugin_dependencies.prf)

for(dir, DIRS) {
    include($$dir/$${dir}.pri)
}

DEFINES *= \
    MI_MIDIFILE_LIBRARY

HEADERS *= \
    mi_midifileglobal.h \
    mi_midifilenamespace.h \

SOURCE_PAIRS = \
    mi_midifileplugin \

for(pair, SOURCE_PAIRS) {
    HEADERS *= $${pair}.h
    SOURCES *= $${pair}.cpp
}

OTHER_FILES *= \
    mi_midifileplugin.prf \
    mi_midifileplugin_dependencies.prf \
    MiMidiFilePlugin.pluginspec.in \

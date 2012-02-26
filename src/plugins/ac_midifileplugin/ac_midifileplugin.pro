TARGET = AcMidiFilePlugin
TEMPLATE = lib

load(../../plugin.prf)
load(../ac_midifileplugin/ac_midifileplugin_dependencies.prf)

for(dir, DIRS) {
    include($$dir/$${dir}.pri)
}

DEFINES *= \
    AC_MIDIFILE_LIBRARY

HEADERS *= \
    ac_midifileconstants.h \
    ac_midifileglobal.h \
    ac_midifilenamespace.h \

SOURCE_PAIRS = \
    ac_midifileplugin \

for(pair, SOURCE_PAIRS) {
    HEADERS *= $${pair}.h
    SOURCES *= $${pair}.cpp
}

OTHER_FILES *= \
    ac_midifileplugin.prf \
    ac_midifileplugin_dependencies.prf \
    AcMidiFilePlugin.pluginspec.in \

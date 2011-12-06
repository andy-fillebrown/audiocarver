TARGET = AcSynthesizer
TEMPLATE = lib

load(../../plugin.prf)
load(../ac_synthesizer/ac_synthesizer_dependencies.prf)

DEFINES *= \
    USE_DOUBLE \

for(dir, DIRS) {
    include($$dir/$${dir}.pri)
}

SOURCE_PAIRS = \
    ac_synthesizerplugin \

for(pair, SOURCE_PAIRS) {
    HEADERS *= $${pair}.h
    SOURCES *= $${pair}.cpp
}

QMAKE_SUBSTITUTES *= \
    ../../../testing/moogladder.csd.in \

OTHER_FILES *= \
    ac_synthesizer.prf \
    ac_synthesizer_dependencies.prf \
    AcSynthesizer.pluginspec.in \

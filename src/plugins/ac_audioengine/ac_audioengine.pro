TARGET = AcAudioEngine
TEMPLATE = lib
QT *= multimedia

load(../../plugin.prf)
load(../ac_audioengine/ac_audioengine_dependencies.prf)

for(dir, DIRS) {
    include($$dir/$${dir}.pri)
}

HEADERS *= \
    ac_audioengineconstants.h \

SOURCE_PAIRS = \
    ac_audioengineplugin \

for(pair, SOURCE_PAIRS) {
    HEADERS *= $${pair}.h
    SOURCES *= $${pair}.cpp
}

#RESOURCES = \
#    ac_audioengine.qrc \

OTHER_FILES *= \
    ac_audioengine.prf \
    ac_audioengine_dependencies.prf \
    AcAudioEngine.pluginspec.in \

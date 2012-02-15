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

ACI_FILES = \
    instruments/aci/instrument-control.aci \
    instruments/aci/track-control.aci \

copy_aci_files.name = COPY $(QMAKE_FILE_IN)
copy_aci_files.input = ACI_FILES
copy_aci_files.output = $$PRO_BUILD_TREE/instruments/aci/${QMAKE_FUNC_FILE_IN_stripDir}
copy_aci_files.commands = $$QMAKE_COPY ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
copy_aci_files.CONFIG *= no_link
isEmpty(vcproj): copy_aci_files.variable_out = PRE_TARGETDEPS
QMAKE_EXTRA_COMPILERS *= copy_aci_files

ORC_FILES = \
    instruments/pluck.orc \
    instruments/pulse.orc \
    instruments/saw.orc \
    instruments/sine.orc \
    instruments/sine--smooth-envelope.orc \
    instruments/square.orc \
    instruments/triangle.orc \
    instruments/wgbow.orc \

copy_orc_files.name = COPY $(QMAKE_FILE_IN)
copy_orc_files.input = ORC_FILES
copy_orc_files.output = $$PRO_BUILD_TREE/instruments/${QMAKE_FUNC_FILE_IN_stripDir}
copy_orc_files.commands = $$QMAKE_COPY ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
copy_orc_files.CONFIG *= no_link
isEmpty(vcproj): copy_orc_files.variable_out = PRE_TARGETDEPS
QMAKE_EXTRA_COMPILERS *= copy_orc_files

OTHER_FILES *= \
    $$ACI_FILES \
    $$ORC_FILES \
    ac_synthesizer.prf \
    ac_synthesizer_dependencies.prf \
    AcSynthesizer.pluginspec.in \

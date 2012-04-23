TARGET = AcSynthesizer
TEMPLATE = lib

load(../../plugin.prf)
load(../ac_synthesizer/ac_synthesizer_dependencies.prf)

DEFINES *= \
    USE_DOUBLE \

for(dir, DIRS) {
    include($$dir/$${dir}.pri)
}

SOURCE_FILES = \
    ac_synthesizerplugin \

ACI_FILES = \
    instrument-control \
    track-control \

ORC_FILES = \
    pluck \
    pulse \
    saw \
    sine \
    sine--smooth-envelope \
    subtractive-synth-01 \
    square \
    triangle \
    wgbow \

for(file, SOURCE_FILES) {
    HEADERS *= $${file}.h
    SOURCES *= $${file}.cpp
}

for(file, ACI_FILES) {
    aci_files *= instruments/aci/$${file}.aci
}
copy_aci_files.name = COPY $(QMAKE_FILE_IN)
copy_aci_files.input = aci_files
copy_aci_files.output = $$PRO_BUILD_TREE/instruments/aci/${QMAKE_FUNC_FILE_IN_stripDir}
copy_aci_files.commands = $$QMAKE_COPY ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
copy_aci_files.CONFIG *= no_link
isEmpty(vcproj): copy_aci_files.variable_out = POST_TARGETDEPS
QMAKE_EXTRA_COMPILERS *= copy_aci_files

for(file, ORC_FILES) {
    orc_files *= instruments/$${file}.orc
}
copy_orc_files.name = COPY $(QMAKE_FILE_IN)
copy_orc_files.input = orc_files
copy_orc_files.output = $$PRO_BUILD_TREE/instruments/${QMAKE_FUNC_FILE_IN_stripDir}
copy_orc_files.commands = $$QMAKE_COPY ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
copy_orc_files.CONFIG *= no_link
isEmpty(vcproj): copy_orc_files.variable_out = POST_TARGETDEPS
QMAKE_EXTRA_COMPILERS *= copy_orc_files

OTHER_FILES *= \
    $$aci_files \
    $$orc_files \
    ac_synthesizer.prf \
    ac_synthesizer_dependencies.prf \
    AcSynthesizer.pluginspec.in \

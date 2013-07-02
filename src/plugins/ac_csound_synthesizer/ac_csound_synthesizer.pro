TARGET_PREFIX = Ac
TARGET_NAME = CsoundSynthesizerPlugin

TEMPLATE = lib

include(../../_.plugin.prf)

DEFINES *= \
    AC_CSOUND_SYNTHESIZER_LIBRARY \
    USE_DOUBLE \

SOURCE_FILES = \
    global \
    plugin \

ACI_FILES = \
    instrument-control \
    track-control \
    volume-envelope \

ORC_FILES = \
    pluck \
    pulse \
    saw \
    sine \
    sine--smooth-envelope \
    subtractive-synth-01 \
    subtractive-synth-01--reverb \
    square \
    triangle \
    wgbow \

for(file, SOURCE_FILES) {
    file = $${SOURCE_FILE_PREFIX}_$$file
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= $$header
    exists($$source): SOURCES *= $$source
}
resource = $${SOURCE_FILE_PREFIX}.qrc
prf = $${SOURCE_FILE_PREFIX}.prf
dependencies_prf = _.$${SOURCE_FILE_PREFIX}_dependencies.prf
pluginspec = $${SOURCE_FILE_PREFIX}.pluginspec.in
exists($$resource): RESOURCES *= $$resource
exists($$prf): OTHER_FILES *= $$prf
exists($$dependencies_prf): OTHER_FILES *= $$dependencies_prf
exists($$pluginspec): OTHER_FILES *= $$pluginspec
include(../$$SOURCE_FILE_PREFIX/$$dependencies_prf)
for(dir, DIRS) {
    pri_file = $$dir/$${dir}.pri
    exists($$pri_file): include($$pri_file)
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

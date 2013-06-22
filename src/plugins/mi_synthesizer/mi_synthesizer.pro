TARGET_PREFIX = Mi
TARGET_NAME = SynthesizerPlugin

TEMPLATE = lib

include(../../_.plugin.prf)

DEFINES *= \
    MI_SYNTHESIZER_LIBRARY \
    USE_DOUBLE \

SOURCE_FILES = \
    global \
    plugin \

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

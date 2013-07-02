TARGET_PREFIX = Ac
TARGET_NAME = MidiPlugin

TEMPLATE = lib

include(../../_.plugin.prf)

DEFINES *= \
    AC_MIDI_LIBRARY

SOURCE_FILES = \
    constants \
    global \
    mainwindowextension \
    namespace \
    plugin \

for(file, SOURCE_FILES) {
    name = $${SOURCE_FILE_PREFIX}_$$file
    header = $${name}.h
    source = $${name}.cpp
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
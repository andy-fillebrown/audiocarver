TARGET_PREFIX = Mi
TARGET_NAME = CorePlugin

TEMPLATE = lib
QT -= gui

include(../../_.plugin.prf)

DEFINES *= \
    MI_CORE_LIBRARY

QOBJECT_INTERFACE_FILES *= \
    model \

SOURCE_FILES = \
    global \
    namespace \
    plugin \

for(file, QOBJECT_INTERFACE_FILES) {
    eval(HEADERS *= ../_.interfaces/i$${file}.h)
}

for(file, SOURCE_FILES) {
    name = $${SOURCE_FILE_PREFIX}_$$file
    header = $${name}.h
    source = $${name}.cpp
    exists($$header): HEADERS *= $$header
    exists($$source): SOURCES *= $$source
}

resource = $${SOURCE_FILE_PREFIX}.qrc
prf = _.$${SOURCE_FILE_PREFIX}.prf
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

TARGET_PREFIX = Ac
TARGET_NAME = CorePlugin

TEMPLATE = lib

load(../../plugin.prf)

DEFINES *= \
    AC_CORE_LIBRARY \

SOURCE_FILES = \
    coreconstants \
    global \
    namespace \

SOURCE_FILES *= $$target_name
for(file, SOURCE_FILES) {
    name = $$SOURCE_FILE_PREFIX$$file
    header = $${name}.h
    source = $${name}.cpp
    exists($$header): HEADERS *= $$header
    exists($$source): SOURCES *= $$source
}
resource = $${prefixed_target_name}.qrc
prf = $${prefixed_target_name}.prf
dependencies_prf = $${prefixed_target_name}_dependencies.prf
pluginspec = $${PREFIXED_TARGET_NAME}.pluginspec.in
exists($$resource): RESOURCES *= $$resource
exists($$prf): OTHER_FILES *= $$prf
exists($$dependencies_prf): OTHER_FILES *= $$dependencies_prf
exists($$pluginspec): OTHER_FILES *= $$pluginspec

load(../$$prefixed_target_name/$$dependencies_prf)
for(dir, DIRS) {
    include($$dir/$${dir}.pri)
}

TARGET_PREFIX = Mi
TARGET_NAME = GuiPlugin

TEMPLATE = lib

load(../../plugin.prf)
load(../mi_guiplugin/mi_guiplugin_dependencies.prf)

for(dir, DIRS) {
    include($$dir/$${dir}.pri)
}

DEFINES *= \
    MI_GUI_LIBRARY

SOURCE_FILES = \
    guiconstants \
    guiplugin \

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


SOURCE_FILES = \
    abstractcurve \
    controlcurve \
#    gridline \
#    gridsettings \
    note \
    pitchcurve \
#    projectsettings \
#    score \
#    track \
#    viewsettings \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
SUFFIX = graphicsobject
for(file, SOURCE_FILES) {
    name = $${SOURCE_FILE_PREFIX}$$file$$SUFFIX
    header = $${name}.h
    source = $${name}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

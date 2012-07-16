
SOURCE_FILES = \
    controlcurve \
    curve \
    graphicsobject \
#    gridline \
#    gridsettings \
    note \
    pitchcurve \
    scoreobject \
    track \
#    projectsettings \
    score \
#    track \
#    viewsettings \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    name = $${SOURCE_FILE_PREFIX}_$${file}
    header = $${name}.h
    source = $${name}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}


SOURCE_FILES = \
    controlcurve \
    curve \
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
    name = $${SOURCE_FILE_PREFIX}graphics_$${file}
    header = $${name}.h
    source = $${name}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

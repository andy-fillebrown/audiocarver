
SOURCE_FILES = \
    curve \
    controlcurve \
#    gridline \
#    gridsettings \
    note \
    pitchcurve \
    scoreobject \
#    projectsettings \
#    score \
#    track \
#    viewsettings \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    name = $${SOURCE_FILE_PREFIX}database_$$file
    header = $${name}.h
    source = $${name}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

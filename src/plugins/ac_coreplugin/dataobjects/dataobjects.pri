
SOURCE_FILES = \
    controlcurvedata \
    curvedataobject \
#    gridline \
#    gridsettings \
#    note \
    pitchcurvedata \
#    projectsettings \
#    score \
    scoredataobject \
#    track \
#    viewsettings \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    name = $$SOURCE_FILE_PREFIX$$file
    header = $${name}.h
    source = $${name}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

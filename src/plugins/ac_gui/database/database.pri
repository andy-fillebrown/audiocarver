
SOURCE_FILES = \
#    controlcurve \
    curve_entity \
    curve_graphicsitem \
    curve_subentity \
#    graphicsobject \
#    gridline \
#    gridsettings \
#    note \
#    pitchcurve \
#    scoreobject \
#    track \
#    projectsettings \
#    score \
#    track \
#    viewsettings \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    file = $${SOURCE_FILE_PREFIX}_$${file}
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

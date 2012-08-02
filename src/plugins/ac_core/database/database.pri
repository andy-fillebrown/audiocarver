
SOURCE_FILES = \
#    curve_aggregate \
    curve_modeldata \
    curve_modelitem \
#    curve_points \
#    controlcurve \
#    gridline \
#    gridsettings \
#    note \
#    objectlist_aggregate \
#    pitchcurve \
#    projectsettings \
#    score \
#    scoreobject_aggregate \
    scoreobject_modeldata \
    scoreobject_modelitem \
#    track \
#    viewsettings \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    name = $${SOURCE_FILE_PREFIX}_$$file
    header = $${name}.h
    source = $${name}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

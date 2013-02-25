
SOURCE_FILES = \
    controlcurve_graphicsitem \
    controlgridline_graphicsitem \
    curve_graphicsitem \
    gridline_graphicsitem \
    gridsettings_graphicsitem \
    horizontalgridline_graphicsitem \
    note_graphicsitem \
    note_modelitem \
    object_graphicscurve \
    object_graphicsentity \
    object_graphicsitem \
    pitchcurve_graphicsitem \
    pitchgridline_graphicsitem \
    score_graphicsitem \
    scoreobject_graphicsitem \
    timegridline_graphicsitem \
    track_graphicsitem \
    velocity_graphicsitem \
    velocity_modelitem \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    file = $${SOURCE_FILE_PREFIX}_$${file}
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

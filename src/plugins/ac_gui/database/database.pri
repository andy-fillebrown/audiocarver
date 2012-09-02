
SOURCE_FILES = \
    controlcurve_graphicsitem \
    controlcurve_subentity \
    controlgridline_entity \
    curve_entity \
    curve_graphicsitem \
    curve_subentity \
    gridline_entity \
    gridsettings_entity \
    horizontalgridline_entity \
    note_entity \
    object_childentity \
    object_entity \
    object_graphicsitem \
    object_modeldatawatcher \
    object_modelitemwatcher \
    object_parententity \
    object_subentity \
    pitchcurve_graphicsitem \
    pitchcurve_subentity \
    pitchgridline_entity \
    score_entity \
    scoreobject_entity \
    timegridline_entity \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    file = $${SOURCE_FILE_PREFIX}_$${file}
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}


SOURCE_FILES = \
    controlcurve_subentity \
    controlgridline_entity \
    curve_entity \
    curve_graphicsitem \
    curve_subentity \
    gridline_entity \
    horizontalgridline_entity \
    note_entity \
    object_entity \
    object_graphicsitem \
    object_parententity \
    object_subentity \
    pitchcurve_subentity \
    pitchgridline_entity \
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

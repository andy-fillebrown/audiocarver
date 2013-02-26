
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

for(file, SOURCE_FILES) {
    header = ac_gui_$${file}.h
    source = ac_gui_$${file}.cpp
    exists($$header): HEADERS *= database/$$header
    exists($$source): SOURCES *= database/$$source
}

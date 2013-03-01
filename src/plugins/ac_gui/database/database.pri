
SOURCE_FILES = \
    controlcurve_graphicsdata \
    controlgridline_graphicsdata \
    curve_graphicsdata \
    gridline_graphicsdata \
    gridsettings_graphicsdata \
    horizontalgridline_graphicsdata \
    note_graphicsdata \
    note_modelitem \
    object_graphicsitem \
    pitchcurve_graphicsdata \
    pitchgridline_graphicsdata \
    score_graphicsdata \
    scoreobject_graphicsdata \
    scoreobject_graphicsentity \
    timegridline_graphicsdata \
    track_graphicsdata \
    velocity_graphicsdata \
    velocity_modelitem \

for(file, SOURCE_FILES) {
    header = ac_gui_$${file}.h
    source = ac_gui_$${file}.cpp
    exists($$header): HEADERS *= database/$$header
    exists($$source): SOURCES *= database/$$source
}


SOURCE_FILES = \
    controlcurve_graphicsdata \
    controlgridline_graphicsdata \
    curve_graphicsdata \
    gridline_graphicsdata \
    gridsettings_graphicsdata \
    grip_graphicsitem \
    horizontalgridline_graphicsdata \
    note_graphicsdata \
    object_graphicsitem \
    pitchcurve_graphicsdata \
    pitchgridline_graphicsdata \
    score_graphicsdata \
    scoreobject_graphicsdata \
    scoreobject_graphicsentity \
    timegridline_graphicsdata \
    track_graphicsdata \
    velocity_graphicsdata \

for(file, SOURCE_FILES) {
    header = ac_gui_$${file}.h
    source = ac_gui_$${file}.cpp
    exists($$header): HEADERS *= graphics/$$header
    exists($$source): SOURCES *= graphics/$$source
}


SOURCE_FILES = \
    controlcurve_graphicsiteminfo \
    controlgridline_graphicsdata \
    curve_graphicsdata \
    curve_graphicsitem \
    curve_graphicsiteminfo \
    gridline_graphicsdata \
    gridsettings_graphicsdata \
    griplist_graphicsdata \
    griplist_graphicsitem \
    horizontalgridline_graphicsdata \
    note_graphicsdata \
    note_graphicsitem \
    object_graphicsitem \
    object_graphicsitemhelper \
    pitchcurve_graphicsdata \
    pitchcurve_graphicsiteminfo \
    pitchgridline_graphicsdata \
    score_graphicsdata \
    scoreobject_graphicsdata \
    scoreobject_graphicsitem \
    timegridline_graphicsdata \
    track_graphicsdata \
    velocity_graphicsdata \

for(file, SOURCE_FILES) {
    header = ac_gui_$${file}.h
    source = ac_gui_$${file}.cpp
    exists($$header): HEADERS *= graphics/$$header
    exists($$source): SOURCES *= graphics/$$source
}

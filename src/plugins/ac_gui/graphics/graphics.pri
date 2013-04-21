
SOURCE_FILES = \
    controlcurve_graphicsitem \
#    controlgridline_graphicsdata \
#    curve_graphicsdata \
#    curve_graphicsdelegate \
    curve_graphicsitem \
#    curve_graphicsiteminfo \
#    curve_griplistdata \
#    gridline_graphicsdata \
#    gridsettings_graphicsdata \
#    grip_graphicsdata \
#    horizontalgridline_graphicsdata \
#    note_graphicsdata \
    note_graphicsitem \
#    object_graphicsitem \
#    object_graphicsitemhelper \
#    object_griplistdata \
    objectlist_graphicsitem \
    pitchcurve_graphicsitem \
#    pitchgridline_graphicsdata \
    score_graphicsitem \
    scoreobject_graphicsitem \
#    timegridline_graphicsdata \
    track_graphicsitem \
#    velocity_graphicsdelegate \
    velocity_graphicsitem \
#    velocity_griplistdata \

for(file, SOURCE_FILES) {
    header = ac_gui_$${file}.h
    source = ac_gui_$${file}.cpp
    exists($$header): HEADERS *= graphics/$$header
    exists($$source): SOURCES *= graphics/$$source
}

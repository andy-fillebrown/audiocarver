
SOURCE_FILES = \
    controlcurve_graphicsitem \
    controlgridline_graphicsitem \
    curve_graphicsdelegate \
    curve_graphicsitem \
    curve_graphicsgriplist \
    gridline_graphicsitem \
    gridsettings_graphicsitem \
    grip_graphicsitem \
    horizontalgridline_graphicsitem \
    note_graphicsitem \
    object_graphicsitem \
    object_graphicsgrip \
    object_graphicsgriplist \
    objectlist_graphicsitem \
    pitchcurve_graphicsitem \
    pitchgridline_graphicsitem \
    score_graphicsitem \
    scoreobject_graphicsitem \
    timegridline_graphicsitem \
    track_graphicsitem \
    velocity_graphicsdelegate \
    velocity_graphicsgriplist \
    velocity_graphicsitem \

for(file, SOURCE_FILES) {
    header = ac_gui_$${file}.h
    source = ac_gui_$${file}.cpp
    exists($$header): HEADERS *= graphics/$$header
    exists($$source): SOURCES *= graphics/$$source
}

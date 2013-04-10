
SOURCE_FILES = \
    controlcurve_modelitem \
    controlgridline_modelitem \
    curve_aggregate \
    curve_modelitem \
    gridline_aggregate \
    gridline_modelitem \
    gridsettings_aggregate \
    gridsettings_modelitem \
    note_aggregate \
    note_modelitem \
    pitchcurve_modelitem \
    pitchgridline_modelitem \
    projectsettings_aggregate \
    projectsettings_modelitem \
    score_aggregate \
    score_modelitem \
    scoreobject_aggregate \
    scoreobject_modelitem \
    timegridline_modelitem \
    track_aggregate \
    track_modelitem \
    viewsettings_aggregate \
    viewsettings_modelitem \

for(file, SOURCE_FILES) {
    header = ac_core_$${file}.h
    source = ac_core_$${file}.cpp
    exists($$header): HEADERS *= database/$$header
    exists($$source): SOURCES *= database/$$source
}

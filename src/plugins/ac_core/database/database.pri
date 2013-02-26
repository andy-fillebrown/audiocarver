
SOURCE_FILES = \
    curve_modeldata \
    curve_modelitem \
    controlcurve_modeldata \
    controlcurve_modelitem \
    controlgridline_modelitem \
    gridline_modeldata \
    gridline_modelitem \
    gridsettings_modeldata \
    gridsettings_modelitem \
    note_modelitem \
    pitchcurve_modeldata \
    pitchcurve_modelitem \
    pitchgridline_modelitem \
    projectsettings_modeldata \
    projectsettings_modelitem \
    score_modeldata \
    score_modelitem \
    scoreobject_modeldata \
    scoreobject_modelitem \
    timegridline_modelitem \
    track_modeldata \
    track_modelitem \
    viewsettings_modeldata \
    viewsettings_modelitem \

for(file, SOURCE_FILES) {
    header = ac_core_$${file}.h
    source = ac_core_$${file}.cpp
    exists($$header): HEADERS *= database/$$header
    exists($$source): SOURCES *= database/$$source
}

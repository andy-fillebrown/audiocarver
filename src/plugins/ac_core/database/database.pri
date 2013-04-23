
SOURCE_FILES = \
    controlcurve_modelitem \
    controlgridline_modelitem \
    curve_modelitem \
    gridline_modelitem \
    gridsettings_modelitem \
    note_modelitem \
    pitchcurve_modelitem \
    pitchgridline_modelitem \
    projectsettings_modelitem \
    score_modelitem \
    scoreobject_modelitem \
    timegridline_modelitem \
    track_modelitem \
    viewsettings_modelitem \

for(file, SOURCE_FILES) {
    header = ac_core_$${file}.h
    source = ac_core_$${file}.cpp
    exists($$header): HEADERS *= database/$$header
    exists($$source): SOURCES *= database/$$source
}

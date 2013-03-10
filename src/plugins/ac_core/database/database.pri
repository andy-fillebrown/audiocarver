
SOURCE_FILES = \
    controlcurve_modeldata \
    controlcurve_modeliteminfo \
    controlgridline_modeliteminfo \
    curve_modeldata \
    curve_modeliteminfo \
    gridline_modeldata \
    gridline_modeliteminfo \
    gridsettings_modeldata \
    gridsettings_modelitem \
    gridsettings_modeliteminfo \
    note_modeliteminfo \
    pitchcurve_modeldata \
    pitchcurve_modeliteminfo \
    pitchgridline_modeliteminfo \
    projectsettings_modeldata \
    projectsettings_modeliteminfo \
    score_modeldata \
    score_modelitem \
    score_modeliteminfo \
    scoreobject_modeldata \
    scoreobject_modelitem \
    scoreobject_modeliteminfo \
    timegridline_modeliteminfo \
    track_modeldata \
    track_modelitem \
    track_modeliteminfo \
    viewsettings_modeldata \
    viewsettings_modelitem \
    viewsettings_modeliteminfo \

for(file, SOURCE_FILES) {
    header = ac_core_$${file}.h
    source = ac_core_$${file}.cpp
    exists($$header): HEADERS *= database/$$header
    exists($$source): SOURCES *= database/$$source
}

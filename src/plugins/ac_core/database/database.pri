
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

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    name = ac_$$file
    header = $${name}.h
    source = $${name}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

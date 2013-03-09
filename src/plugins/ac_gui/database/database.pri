
SOURCE_FILES = \
    controlcurve_modelitem \
    curve_modelitemhelper \
    note_modelitem \
    pitchcurve_modelitem \
    velocity_modelitem \

for(file, SOURCE_FILES) {
    header = ac_gui_$${file}.h
    source = ac_gui_$${file}.cpp
    exists($$header): HEADERS *= database/$$header
    exists($$source): SOURCES *= database/$$source
}

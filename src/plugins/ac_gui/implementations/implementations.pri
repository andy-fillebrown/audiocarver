
SOURCE_FILES = \
    graphicscurve \
    graphicsdata \
    graphicsentity \
    graphicsitem \

for(file, SOURCE_FILES) {
    header = ac_gui_base_$${file}.h
    source = ac_gui_base_$${file}.cpp
    exists($$header): HEADERS *= implementations/$$header
    exists($$source): SOURCES *= implementations/$$source
}
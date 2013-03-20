
SOURCE_FILES = \
    graphicscurvedata \
    graphicsdelegate \
    graphicsentitydata \
    graphicsentityitem \
    graphicsitem \
    graphicsiteminfo \
    graphicssubentitydata \
    graphicssubentityitem \
    gripdata \
    griplistdata \

for(file, SOURCE_FILES) {
    header = ac_gui_base_$${file}.h
    source = ac_gui_base_$${file}.cpp
    exists($$header): HEADERS *= implementations/$$header
    exists($$source): SOURCES *= implementations/$$source
}

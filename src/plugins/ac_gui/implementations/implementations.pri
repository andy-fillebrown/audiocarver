
SOURCE_FILES = \
    graphicscurvedata \
    graphicsentitydata \
    graphicsentityitem \
    graphicsitem \
    graphicsitemeditor \
    graphicsiteminfo \
    graphicssubentitydata \
    graphicssubentityitem \

for(file, SOURCE_FILES) {
    header = ac_gui_base_$${file}.h
    source = ac_gui_base_$${file}.cpp
    exists($$header): HEADERS *= implementations/$$header
    exists($$source): SOURCES *= implementations/$$source
}


SOURCE_FILES = \
    graphicsscene \
    graphicsview \

for(file, SOURCE_FILES) {
    header = mi_gui_$${file}.h
    source = mi_gui_$${file}.cpp
    exists($$header): HEADERS *= graphicsview/$$header
    exists($$source): SOURCES *= graphicsview/$$source
}

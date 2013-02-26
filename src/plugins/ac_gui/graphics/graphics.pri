
SOURCE_FILES = \
    grip_graphicsitem \

for(file, SOURCE_FILES) {
    header = ac_gui_$${file}.h
    source = ac_gui_$${file}.cpp
    exists($$header): HEADERS *= graphics/$$header
    exists($$source): SOURCES *= graphics/$$source
}

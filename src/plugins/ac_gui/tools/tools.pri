
SOURCE_FILES = \
    griplist_tools \

for(file, SOURCE_FILES) {
    header = ac_gui_$${file}.h
    source = ac_gui_$${file}.cpp
    exists($$header): HEADERS *= tools/$$header
    exists($$source): SOURCES *= tools/$$source
}

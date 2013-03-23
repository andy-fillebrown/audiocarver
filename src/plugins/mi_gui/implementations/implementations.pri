
SOURCE_FILES = \
    editor \
    selectionset \
    selectionsetwatcher \

for(file, SOURCE_FILES) {
    header = mi_gui_base_$${file}.h
    source = mi_gui_base_$${file}.cpp
    exists($$header): HEADERS *= implementations/$$header
    exists($$source): SOURCES *= implementations/$$source
}

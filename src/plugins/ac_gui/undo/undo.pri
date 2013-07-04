
SOURCE_FILES = \
    undo_stack \
    undo_viewsettingscommand \

for(file, SOURCE_FILES) {
    header = ac_gui_$${file}.h
    source = ac_gui_$${file}.cpp
    exists($$header): HEADERS *= undo/$$header
    exists($$source): SOURCES *= undo/$$source
}

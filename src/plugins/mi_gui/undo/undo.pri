
SOURCE_FILES = \
    undo_command \
    undo_datachangecommand \
    undo_insertcommand \
    undo_listcommand \
    undo_modelitemcommand \
    undo_removecommand \
    undo_stack \

for(file, SOURCE_FILES) {
    header = mi_gui_$${file}.h
    source = mi_gui_$${file}.cpp
    exists($$header): HEADERS *= undo/$$header
    exists($$source): SOURCES *= undo/$$source
}

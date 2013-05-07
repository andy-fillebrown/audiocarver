
SOURCE_FILES = \
    gridlinedialog \

for(file, SOURCE_FILES) {
    HEADERS *= dialogs/ac_gui_$${file}.h
    SOURCES *= dialogs/ac_gui_$${file}.cpp
    FORMS *= dialogs/ac_gui_$${file}.ui
}

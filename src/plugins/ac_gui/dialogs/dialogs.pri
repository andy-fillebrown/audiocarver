
SOURCE_FILES = \
    gridlinedialog \

for(file, SOURCE_FILES) {
    HEADERS *= dialogs/ac_$${file}.h
    SOURCES *= dialogs/ac_$${file}.cpp
    FORMS *= dialogs/ac_$${file}.ui
}

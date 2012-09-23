
FILES = \
    ac_midifileimportdialog \

for(file, FILES) {
    HEADERS *= dialogs/$${file}.h
    SOURCES *= dialogs/$${file}.cpp
    FORMS *= dialogs/$${file}.ui
}

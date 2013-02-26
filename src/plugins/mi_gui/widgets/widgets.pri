
SOURCE_FILES = \
    doublespinbox \

for(file, SOURCE_FILES) {
    header = mi_gui_$${file}.h
    source = mi_gui_$${file}.cpp
    exists($$header): HEADERS *= widgets/$$header
    exists($$source): SOURCES *= widgets/$$source
}

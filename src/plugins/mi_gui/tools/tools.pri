
SOURCE_FILES = \
    scopedselectionchange \

for(file, SOURCE_FILES) {
    header = mi_gui_$${file}.h
    source = mi_gui_$${file}.cpp
    exists($$header): HEADERS *= tools/$$header
    exists($$source): SOURCES *= tools/$$source
}


SOURCE_FILES = \
    delegate \

for(file, SOURCE_FILES) {
    header = mi_gui_$${file}.h
    source = mi_gui_$${file}.cpp
    exists($$header): HEADERS *= itemviews/$$header
    exists($$source): SOURCES *= itemviews/$$source
}


SOURCE_FILES = \
    core_databasesaver \

for(file, SOURCE_FILES) {
    header = mi_gui_$${file}.h
    source = mi_gui_$${file}.cpp
    exists($$header): HEADERS *= watchers/$$header
    exists($$source): SOURCES *= watchers/$$source
}


SOURCE_FILES = \
    gridline_modelupdater \

for(file, SOURCE_FILES) {
    header = ac_core_$${file}.h
    source = ac_core_$${file}.cpp
    exists($$header): HEADERS *= watchers/$$header
    exists($$source): SOURCES *= watchers/$$source
}

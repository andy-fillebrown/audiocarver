
SOURCE_FILES = \
    object_aggregate \
    object_modelitem \
    objectlist_modelitem \

for(file, SOURCE_FILES) {
    header = mi_core_$${file}.h
    source = mi_core_$${file}.cpp
    exists($$header): HEADERS *= database/$$header
    exists($$source): SOURCES *= database/$$source
}

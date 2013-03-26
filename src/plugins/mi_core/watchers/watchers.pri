
SOURCE_FILES = \
    object_modelupdater \
    objectlist_modelupdater \

for(file, SOURCE_FILES) {
    header = mi_core_$${file}.h
    source = mi_core_$${file}.cpp
    exists($$header): HEADERS *= watchers/$$header
    exists($$source): SOURCES *= watchers/$$source
}

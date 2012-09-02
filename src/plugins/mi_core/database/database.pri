
SOURCE_FILES = \
    aggregate \
    object_modeldata \
    object_modeldatawatcher \
    object_modelitem \
    objectlist_modeldata \
    objectlist_modelitem \
    objectlist_modelitemlistwatcher \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    file = $${SOURCE_FILE_PREFIX}_$$file
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}


SOURCE_FILES = \
    object.aggregate \
    object.modeldata \
    object.modelitem \
    objectlist.aggregate \
    objectlist.modelitemlist \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    name = $${SOURCE_FILE_PREFIX}_database_$$file
    header = $${name}.h
    source = $${name}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

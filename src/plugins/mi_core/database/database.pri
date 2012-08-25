
SOURCE_FILES = \
    aggregate \
    database \
    databaseobjectfactory \
    filerfactory \
    math \
    model \
    modeldata \
    modelitem \
    modelitemlist \
    qmodel \
    session \
    utilities \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    file = $${SOURCE_FILE_PREFIX}_$$file
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

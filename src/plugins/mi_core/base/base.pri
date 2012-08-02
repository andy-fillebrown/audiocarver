
SOURCE_FILES = \
    aggregate \
    classfactory \
    database \
    model \
    modeldata \
    modelitem \
    modelitemlist \
    qmodel \
    session \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    name = $${SOURCE_FILE_PREFIX}_$${DIR}_$$file
    header = $${name}.h
    source = $${name}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

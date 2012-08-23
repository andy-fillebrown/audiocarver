
SOURCE_FILES = \
    ieditor \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    header = $${file}.h
    exists($$header): HEADERS *= $$DIR/$$header
}

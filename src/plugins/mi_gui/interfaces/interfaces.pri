
SOURCE_FILES = \
    ieditor \
    iselectionset \
    iselectionsetwatcher \
    iundomanager \

for(file, SOURCE_FILES) {
    header = $${file}.h
    exists($$header): HEADERS *= interfaces/$$header
}


SOURCE_FILES = \
    ieditor \
    iselectionset \
    iselectionsetwatcher \

for(file, SOURCE_FILES) {
    header = $${file}.h
    exists($$header): HEADERS *= interfaces/$$header
}

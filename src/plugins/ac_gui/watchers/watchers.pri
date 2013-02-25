
SOURCE_FILES = \
    note_graphicsitemupdater \
    object_graphicsdataupdater \
    object_graphicsitemupdater \
    tracklist_graphicsdataupdater \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    file = $${SOURCE_FILE_PREFIX}_$$file
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

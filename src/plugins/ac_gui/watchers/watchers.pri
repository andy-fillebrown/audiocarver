
SOURCE_FILES = \
    note_graphicsitemupdater \
    object_graphicsdataupdater \
    object_graphicsentityitemupdater \
    object_graphicsitemupdater \
    tracklist_graphicsdataupdater \

for(file, SOURCE_FILES) {
    header = ac_gui_$${file}.h
    source = ac_gui_$${file}.cpp
    exists($$header): HEADERS *= watchers/$$header
    exists($$source): SOURCES *= watchers/$$source
}


SOURCE_FILES = \
    note_graphicsupdater \
    object_graphicsupdater \
    tracklist_graphicsupdater \

for(file, SOURCE_FILES) {
    header = ac_gui_$${file}.h
    source = ac_gui_$${file}.cpp
    exists($$header): HEADERS *= watchers/$$header
    exists($$source): SOURCES *= watchers/$$source
}

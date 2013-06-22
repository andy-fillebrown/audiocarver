
SOURCE_FILES = \
    dialogupdater \

for(file, SOURCE_FILES) {
    header = mi_audioengine_$${file}.h
    source = mi_audioengine_$${file}.cpp
    exists($$header): HEADERS *= watchers/$$header
    exists($$source): SOURCES *= watchers/$$source
}

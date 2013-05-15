
SOURCE_FILES = \
    event \

for(file, SOURCE_FILES) {
    file = ac_midi_$$file
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= tools/$$header
    exists($$source): SOURCES *= tools/$$source
}

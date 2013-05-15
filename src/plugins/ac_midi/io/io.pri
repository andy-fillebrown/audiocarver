
SOURCE_FILES = \
    filereader \

for(file, SOURCE_FILES) {
    file = ac_midi_$$file
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= io/$$header
    exists($$source): SOURCES *= io/$$source
}

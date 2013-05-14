
SOURCE_FILES = \
    csound_synthesizer \

for(file, SOURCE_FILES) {
    file = ac_synthesizer_$$file
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= csound/$$header
    exists($$source): SOURCES *= csound/$$source
}

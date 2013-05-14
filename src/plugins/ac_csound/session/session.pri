
SOURCE_FILES = \
    synthesizer \

for(file, SOURCE_FILES) {
    file = ac_csound_$$file
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= session/$$header
    exists($$source): SOURCES *= session/$$source
}

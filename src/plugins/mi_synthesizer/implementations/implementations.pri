
SOURCE_FILES = \
    base_synthesizer \

for(file, SOURCE_FILES) {
    file = mi_synthesizer_$${file}
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= implementations/$$header
    exists($$source): SOURCES *= implementations/$$source
}

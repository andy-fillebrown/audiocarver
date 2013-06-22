
SOURCE_FILES = \
    settings \
    sink \
    utilities \

for(file, SOURCE_FILES) {
    file = ac_audioengine_$${file}
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= tools/$$header
    exists($$source): SOURCES *= tools/$$source
}

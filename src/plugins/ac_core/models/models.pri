
SOURCE_FILES = \
    gridlinemodel \
    rolestocolumnsproxymodel \
    trackmodel \

for(file, SOURCE_FILES) {
    header = ac_core_$${file}.h
    source = ac_core_$${file}.cpp
    exists($$header): HEADERS *= models/$$header
    exists($$source): SOURCES *= models/$$source
}

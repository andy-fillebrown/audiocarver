
SOURCE_FILES = \
    filefiler \
    reader \
    writer \

for(file, SOURCE_FILES) {
    header = ac_core_$${file}.h
    source = ac_core_$${file}.cpp
    exists($$header): HEADERS *= filers/$$header
    exists($$source): SOURCES *= filers/$$source
}

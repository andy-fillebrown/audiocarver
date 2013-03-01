
SOURCE_FILES = \
    aggregate \
    database \
    databaseobjectfactory \
    filerfactory \
    model \
    session \

for(file, SOURCE_FILES) {
    header = mi_core_base_$${file}.h
    source = mi_core_base_$${file}.cpp
    exists($$header): HEADERS *= implementations/$$header
    exists($$source): SOURCES *= implementations/$$source
}

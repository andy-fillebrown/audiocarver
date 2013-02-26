
SOURCE_FILES = \
    database \
    databaseobjectfactory \
    filerfactory \
    model \
    session \

for(file, SOURCE_FILES) {
    header = mi_core_$${file}.h
    source = mi_core_$${file}.cpp
    exists($$header): HEADERS *= session/$$header
    exists($$source): SOURCES *= session/$$source
}

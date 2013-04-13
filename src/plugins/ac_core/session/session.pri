
SOURCE_FILES = \
    database \
    databaseobjectfactory \
    filerfactory \
    model \

for(file, SOURCE_FILES) {
    header = ac_core_$${file}.h
    source = ac_core_$${file}.cpp
    exists($$header): HEADERS *= session/$$header
    exists($$source): SOURCES *= session/$$source
}

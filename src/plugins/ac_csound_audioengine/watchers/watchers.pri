
SOURCE_FILES = \
    database_audioengineupdater \

for(file, SOURCE_FILES) {
    header = ac_csound_$${file}.h
    source = ac_csound_$${file}.cpp
    exists($$header): HEADERS *= watchers/$$header
    exists($$source): SOURCES *= watchers/$$source
}


SOURCE_FILES = \
    base_audioengine \
    base_audioenginesettings_watcher \

for(file, SOURCE_FILES) {
    file = mi_audioengine_$${file}
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= implementations/$$header
    exists($$source): SOURCES *= implementations/$$source
}


SOURCE_FILES = \
    dialog \

for(file, SOURCE_FILES) {
    file = mi_audioengine_$${file}
    header = $${file}.h
    source = $${file}.cpp
    form = $${file}.ui
    exists($$header): HEADERS *= dialogs/$$header
    exists($$source): SOURCES *= dialogs/$$source
    exists($$form): FORMS *= dialogs/$$form
}

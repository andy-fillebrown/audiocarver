
SOURCE_FILES = \
    databaseobjectfactory \
    editor \
    filerfactory \
    mainwindow \
    selectionset \
    undomanager \

for(file, SOURCE_FILES) {
    header = ac_gui_$${file}.h
    source = ac_gui_$${file}.cpp
    exists($$header): HEADERS *= session/$$header
    exists($$source): SOURCES *= session/$$source
}

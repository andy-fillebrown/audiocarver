
SOURCE_FILES = \
    controllabelview \
    controlview \
    labelview \
#    graphicsentityitem \
#    graphicsgripitem \
    graphicsitem \
    graphicsscene \
    graphicsview \
    graphicsviewmanager \
    pitchlabelview \
    pitchview \
    timelabelview \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    file = $${SOURCE_FILE_PREFIX}_$$file
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

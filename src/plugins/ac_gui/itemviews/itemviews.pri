
SOURCE_FILES = \
    colordelegate \
    doubledelegate \
#    gridlineview \
#    gripitemspropertyview \
    instrumentdelegate \
    lengthdelegate \
#    propertyview \
    recordbuttondelegate \
#    selecteditemspropertyview \
    togglebuttondelegate \
    volumedelegate \
    trackview \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    file = $${SOURCE_FILE_PREFIX}_$$file
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

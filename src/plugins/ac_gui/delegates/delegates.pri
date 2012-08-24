
SOURCE_FILES = \
    colordelegate \
    doubledelegate \
    instrumentdelegate \
    lengthdelegate \
    recordbuttondelegate \
    togglebuttondelegate \
    volumedelegate \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

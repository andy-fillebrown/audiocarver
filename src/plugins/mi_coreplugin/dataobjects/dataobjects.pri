
SOURCE_FILES = \
    dataobject \
    dataobjectlist \

_DIR_ = $$dirname(_FILE_)
_DIR_ = $$basename(_DIR_)
for(file, SOURCE_FILES) {
    name = $$SOURCE_FILE_PREFIX$$file
    header = $${name}.h
    source = $${name}.cpp
    exists($$header): HEADERS *= $$_DIR_/$$header
    exists($$source): SOURCES *= $$_DIR_/$$source
}

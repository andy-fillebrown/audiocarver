
SOURCE_FILES = \
    dataobject \
    dataobjectlist \

DIR = dataobjects
PREFIX = mi_

for(file, SOURCE_FILES) {
    name = $$PREFIX$$file
    header = $${name}.h
    source = $${name}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

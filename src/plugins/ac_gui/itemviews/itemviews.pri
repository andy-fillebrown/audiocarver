
SOURCE_FILES = \
#    gridlineview \
#    gripitemspropertyview \
#    propertyview \
#    selecteditemspropertyview \
    trackview \

for(file, SOURCE_FILES) {
    HEADERS *= itemviews/$${file}.h
    SOURCES *= itemviews/$${file}.cpp
}

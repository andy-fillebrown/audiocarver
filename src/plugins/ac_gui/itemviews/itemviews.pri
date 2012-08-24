
SOURCE_FILES = \
    trackview \

for(pair, SOURCE_PAIRS) {
    HEADERS *= itemviews/$${pair}.h
    SOURCES *= itemviews/$${pair}.cpp
}

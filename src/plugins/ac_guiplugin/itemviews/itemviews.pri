
SOURCE_PAIRS = \
    ac_gridlineview \
    ac_gripitemspropertyview \
    ac_propertyview \
    ac_selecteditemspropertyview \
    ac_trackview \

for(pair, SOURCE_PAIRS) {
    HEADERS *= itemviews/$${pair}.h
    SOURCES *= itemviews/$${pair}.cpp
}

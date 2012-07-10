
SOURCE_PAIRS = \
    ac_gridlinemodel \
    ac_gripselectionmodel \
    ac_propertymodel \
    ac_selecteditemspropertymodel \
    ac_noteselectionmodel \
    ac_trackselectionmodel \

for(pair, SOURCE_PAIRS) {
    HEADERS *= models/$${pair}.h
    SOURCES *= models/$${pair}.cpp
}

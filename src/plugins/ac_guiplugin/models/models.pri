
SOURCE_PAIRS = \
    ac_propertymodel \
    ac_noteselectionmodel \
    ac_trackselectionmodel \

for(pair, SOURCE_PAIRS) {
    HEADERS *= models/$${pair}.h
    SOURCES *= models/$${pair}.cpp
}


SOURCE_PAIRS = \
    ac_undo \

for(pair, SOURCE_PAIRS) {
    HEADERS *= util/$${pair}.h
    SOURCES *= util/$${pair}.cpp
}

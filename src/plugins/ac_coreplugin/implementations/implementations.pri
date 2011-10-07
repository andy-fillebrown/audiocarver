
SOURCE_PAIRS = \
    ac_database \

for(pair, SOURCE_PAIRS) {
    HEADERS *= implementations/$${pair}.h
    SOURCES *= implementations/$${pair}.cpp
}

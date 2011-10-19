
SOURCE_PAIRS = \
    ac_database \
    ac_factory \

for(pair, SOURCE_PAIRS) {
    HEADERS *= implementations/$${pair}.h
    SOURCES *= implementations/$${pair}.cpp
}


SOURCE_PAIRS = \
    ac_model \
    ac_trackmodel \

for(pair, SOURCE_PAIRS) {
    HEADERS *= models/$${pair}.h
    SOURCES *= models/$${pair}.cpp
}

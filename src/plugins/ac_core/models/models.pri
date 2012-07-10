
SOURCE_PAIRS = \
    ac_proxymodel \
    ac_trackmodel \

for(pair, SOURCE_PAIRS) {
    HEADERS *= models/$${pair}.h
    SOURCES *= models/$${pair}.cpp
}

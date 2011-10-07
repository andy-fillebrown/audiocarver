
SOURCE_PAIRS = \
    ac_graphicsitem \

for(pair, SOURCE_PAIRS) {
    HEADERS *= graphicsview/$${pair}.h
    SOURCES *= graphicsview/$${pair}.cpp
}

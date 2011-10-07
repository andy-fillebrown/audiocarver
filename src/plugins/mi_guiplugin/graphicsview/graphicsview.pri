
SOURCE_PAIRS = \
    mi_graphicsscene \
    mi_graphicsview \

for(pair, SOURCE_PAIRS) {
    HEADERS *= graphicsview/$${pair}.h
    SOURCES *= graphicsview/$${pair}.cpp
}

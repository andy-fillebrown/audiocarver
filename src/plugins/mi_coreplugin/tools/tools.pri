
SOURCE_PAIRS = \
    mi_coreutils \

for(pair, SOURCE_PAIRS) {
    HEADERS *= tools/$${pair}.h
    SOURCES *= tools/$${pair}.cpp
}


SOURCE_PAIRS = \
    mi_coreutils \
    mi_mathutils \

for(pair, SOURCE_PAIRS) {
    HEADERS *= tools/$${pair}.h
    SOURCES *= tools/$${pair}.cpp
}

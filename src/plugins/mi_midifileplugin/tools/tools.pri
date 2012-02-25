
SOURCE_PAIRS = \
    mi_midievent \

for(pair, SOURCE_PAIRS) {
    HEADERS *= tools/$${pair}.h
    SOURCES *= tools/$${pair}.cpp
}

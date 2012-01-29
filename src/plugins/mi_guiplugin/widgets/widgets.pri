
SOURCE_PAIRS = \
    mi_doublespinbox \

for(pair, SOURCE_PAIRS) {
    HEADERS *= widgets/$${pair}.h
    SOURCES *= widgets/$${pair}.cpp
}

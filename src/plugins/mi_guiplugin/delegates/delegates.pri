
SOURCE_PAIRS = \
    mi_delegate \

for(pair, SOURCE_PAIRS) {
    HEADERS *= delegates/$${pair}.h
    SOURCES *= delegates/$${pair}.cpp
}

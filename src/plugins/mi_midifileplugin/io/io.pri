
SOURCE_PAIRS = \
    mi_midifilereader \

for(pair, SOURCE_PAIRS) {
    HEADERS *= io/$${pair}.h
    SOURCES *= io/$${pair}.cpp
}

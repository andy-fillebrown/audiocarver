
SOURCE_PAIRS = \
    ac_csoundaudioengine \

for(pair, SOURCE_PAIRS) {
    HEADERS *= csound/$${pair}.h
    SOURCES *= csound/$${pair}.cpp
}

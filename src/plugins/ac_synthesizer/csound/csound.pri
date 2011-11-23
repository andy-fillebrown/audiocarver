
SOURCE_PAIRS = \
    ac_csoundsynthesizer \

for(pair, SOURCE_PAIRS) {
    HEADERS *= csound/$${pair}.h
    SOURCES *= csound/$${pair}.cpp
}


SOURCE_PAIRS = \
    ac_filer \
    ac_undofiler \
    ac_xmlfiler \

for(pair, SOURCE_PAIRS) {
    HEADERS *= filers/$${pair}.h
    SOURCES *= filers/$${pair}.cpp
}

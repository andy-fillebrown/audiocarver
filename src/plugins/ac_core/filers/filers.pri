
SOURCE_PAIRS = \
    ac_xmlfilefiler \
    ac_xmlreader \
    ac_xmlwriter \

for(pair, SOURCE_PAIRS) {
    HEADERS *= filers/$${pair}.h
    SOURCES *= filers/$${pair}.cpp
}

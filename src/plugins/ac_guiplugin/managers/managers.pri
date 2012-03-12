
SOURCE_PAIRS = \
    ac_viewmanager \

for(pair, SOURCE_PAIRS) {
    HEADERS *= managers/$${pair}.h
    SOURCES *= managers/$${pair}.cpp
}

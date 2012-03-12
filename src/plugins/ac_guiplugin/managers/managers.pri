
SOURCE_PAIRS = \
    ac_gripmanager \
    ac_viewmanager \

for(pair, SOURCE_PAIRS) {
    HEADERS *= managers/$${pair}.h
    SOURCES *= managers/$${pair}.cpp
}

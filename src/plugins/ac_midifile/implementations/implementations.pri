
SOURCE_PAIRS = \
    ac_midimainwindowextension \

for(pair, SOURCE_PAIRS) {
    HEADERS *= implementations/$${pair}.h
    SOURCES *= implementations/$${pair}.cpp
}

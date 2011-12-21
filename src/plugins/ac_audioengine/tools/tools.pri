
SOURCE_PAIRS = \
    ac_audioengineutils \
    ac_audiosink \

for(pair, SOURCE_PAIRS) {
    HEADERS *= tools/$${pair}.h
    SOURCES *= tools/$${pair}.cpp
}

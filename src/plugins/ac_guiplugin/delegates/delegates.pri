
SOURCE_PAIRS = \
    ac_colorbuttondelegate \
    ac_recordbuttondelegate \
    ac_togglebuttondelegate \

for(pair, SOURCE_PAIRS) {
    HEADERS *= delegates/$${pair}.h
    SOURCES *= delegates/$${pair}.cpp
}
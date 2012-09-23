
SOURCE_PAIRS = \
    ac_colordelegate \
    ac_doubledelegate \
    ac_instrumentdelegate \
    ac_lengthdelegate \
    ac_recordbuttondelegate \
    ac_togglebuttondelegate \
    ac_volumedelegate \

for(pair, SOURCE_PAIRS) {
    HEADERS *= delegates/$${pair}.h
    SOURCES *= delegates/$${pair}.cpp
}

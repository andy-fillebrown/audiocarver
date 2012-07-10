
SOURCE_PAIRS = \
    ac_gui_xmlcopyfiler \

for(pair, SOURCE_PAIRS) {
    HEADERS *= filers/$${pair}.h
    SOURCES *= filers/$${pair}.cpp
}


SOURCE_PAIRS = \
    ac_editor \
    ac_guimainwindowextension \

for(pair, SOURCE_PAIRS) {
    HEADERS *= implementations/$${pair}.h
    SOURCES *= implementations/$${pair}.cpp
}

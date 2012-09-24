
SOURCE_PAIRS = \
    mi_guimainwindowextension \

for(pair, SOURCE_PAIRS) {
    HEADERS *= implementations/$${pair}.h
    SOURCES *= implementations/$${pair}.cpp
}

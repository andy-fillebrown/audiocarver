
SOURCE_PAIRS = \
    ac_editor \
    ac_mainwindow \

for(pair, SOURCE_PAIRS) {
    HEADERS *= implementations/$${pair}.h
    SOURCES *= implementations/$${pair}.cpp
}


SOURCE_PAIRS = \
    mi_mainwindowimpl \

for(pair, SOURCE_PAIRS) {
    HEADERS *= implementations/$${pair}.h
    SOURCES *= implementations/$${pair}.cpp
}

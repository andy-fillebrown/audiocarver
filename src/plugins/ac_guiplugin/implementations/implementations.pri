
SOURCE_PAIRS = \
    ac_editorimpl \
    ac_mainwindowimpl \

for(pair, SOURCE_PAIRS) {
    HEADERS *= implementations/$${pair}.h
    SOURCES *= implementations/$${pair}.cpp
}

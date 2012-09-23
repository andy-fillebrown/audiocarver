
SOURCE_PAIRS = \
    ac_gridlinedialog \

for(pair, SOURCE_PAIRS) {
    HEADERS *= dialogs/$${pair}.h
    SOURCES *= dialogs/$${pair}.cpp
}

FORMS *= \
    ac_gridlinedialog.ui \


HEADERS *= \
    interfaces/mi_iunknown.h \

SOURCE_PAIRS = \
    mi_idatabase \

for(pair, SOURCE_PAIRS) {
    HEADERS *= interfaces/$${pair}.h
    SOURCES *= interfaces/$${pair}.cpp
}

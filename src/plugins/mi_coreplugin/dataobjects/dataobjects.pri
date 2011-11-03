
SOURCE_PAIRS = \
    mi_object \
    mi_objectlist \

for(pair, SOURCE_PAIRS) {
    HEADERS *= dataobjects/$${pair}.h
    SOURCES *= dataobjects/$${pair}.cpp
}

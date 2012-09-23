
SOURCE_PAIRS = \
    mi_object \
    mi_objectlist \
    mi_uniquelynamedobject \
    mi_uniquelynamedobjectlist \

for(pair, SOURCE_PAIRS) {
    HEADERS *= dataobjects/$${pair}.h
    SOURCES *= dataobjects/$${pair}.cpp
}

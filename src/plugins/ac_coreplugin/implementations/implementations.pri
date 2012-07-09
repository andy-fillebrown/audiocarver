
SOURCE_PAIRS = \
    ac_database \
    ac_model \
    ac_objectfactory \

for(pair, SOURCE_PAIRS) {
    HEADERS *= implementations/$${pair}.h
    SOURCES *= implementations/$${pair}.cpp
}

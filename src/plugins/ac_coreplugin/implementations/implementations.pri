
SOURCE_PAIRS = \
    ac_coredataobjectfactory \
#    ac_database \
#    ac_factory \
#    ac_model \

for(pair, SOURCE_PAIRS) {
    HEADERS *= implementations/$${pair}.h
    SOURCES *= implementations/$${pair}.cpp
}

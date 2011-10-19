
HEADERS *= \
    ac_ientity.h \
    ac_imodelitem.h \

SOURCE_PAIRS = \
    ac_ifactory \

for(pair, SOURCE_PAIRS) {
    HEADERS *= interfaces/$${pair}.h
    SOURCES *= interfaces/$${pair}.cpp
}

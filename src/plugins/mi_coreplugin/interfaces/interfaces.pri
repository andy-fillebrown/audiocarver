
HEADERS *= \
    interfaces/mi_imodel.h \
    interfaces/mi_imodelitem.h \

SOURCE_PAIRS = \
    mi_iunknown \
    mi_idatabase \

for(pair, SOURCE_PAIRS) {
    HEADERS *= interfaces/$${pair}.h
    SOURCES *= interfaces/$${pair}.cpp
}

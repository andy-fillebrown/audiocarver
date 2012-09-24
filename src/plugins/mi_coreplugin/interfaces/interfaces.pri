
HEADERS *= \
    interfaces/mi_iinterface.h \
    interfaces/mi_imodelitem.h \
    interfaces/mi_imodelitemlist.h \

SOURCE_PAIRS = \
    mi_idatabase \
    mi_imodel \
    mi_iunknown \

for(pair, SOURCE_PAIRS) {
    HEADERS *= interfaces/$${pair}.h
    SOURCES *= interfaces/$${pair}.cpp
}

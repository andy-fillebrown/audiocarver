
HEADERS += \
    interfaces/ac_imodelitem.h \

SOURCE_PAIRS = \
    ac_model \

for(pair, SOURCE_PAIRS) {
    HEADERS *= model/$${pair}.h
    SOURCES *= model/$${pair}.cpp
}

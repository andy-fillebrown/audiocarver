
HEADERS *= \
    ac_ientity.h \
    ac_ifiler.h \

SOURCE_PAIRS = \
    ac_iaudioengine \
    ac_ifactory \
    ac_isynthesizer \

for(pair, SOURCE_PAIRS) {
    HEADERS *= interfaces/$${pair}.h
    SOURCES *= interfaces/$${pair}.cpp
}

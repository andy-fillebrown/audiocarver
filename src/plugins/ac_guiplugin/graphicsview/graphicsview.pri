
SOURCE_PAIRS = \
    ac_controllabelview \
    ac_controlview \
    ac_graphicsentityitem \
    ac_graphicsgripitem \
    ac_graphicsscene \
    ac_graphicsview \
    ac_pitchlabelview \
    ac_pitchview \
    ac_timelabelview \
    ac_viewmanager \

for(pair, SOURCE_PAIRS) {
    HEADERS *= graphicsview/$${pair}.h
    SOURCES *= graphicsview/$${pair}.cpp
}

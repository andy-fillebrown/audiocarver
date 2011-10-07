
SOURCE_PAIRS = \
    ac_editorview \
    ac_graphicsentityitem \
    ac_graphicsgripitem \
    ac_graphicsscene \
    ac_graphicsview \
    ac_labelview \
    ac_pitchlabelview \
    ac_pitchview \
    ac_timelabelview \
    ac_viewmanager \
    ac_volumelabelview \
    ac_volumeview \

for(pair, SOURCE_PAIRS) {
    HEADERS *= graphicsview/$${pair}.h
    SOURCES *= graphicsview/$${pair}.cpp
}

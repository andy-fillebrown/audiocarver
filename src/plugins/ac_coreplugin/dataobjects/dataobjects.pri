
HEADERS += \
    ac_objectlist.h \

SOURCE_PAIRS = \
    ac_controlcurve \
    ac_curve \
    ac_graphicsobject \
    ac_graphicsparent \
    ac_gridline \
    ac_gridsettings \
    ac_note \
    ac_object \
    ac_pitchcurve \
    ac_score \
    ac_scoreobject \
    ac_track \
    ac_viewsettings \

for(pair, SOURCE_PAIRS) {
    HEADERS *= dataobjects/$${pair}.h
    SOURCES *= dataobjects/$${pair}.cpp
}

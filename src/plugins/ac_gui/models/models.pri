
SOURCE_PAIRS = \
#    ac_gripselectionmodel \
    ac_gui_propertymodel \
    ac_gui_selecteditemspropertymodel \
#    ac_noteselectionmodel \
#    ac_trackselectionmodel \

for(pair, SOURCE_PAIRS) {
    HEADERS *= models/$${pair}.h
    SOURCES *= models/$${pair}.cpp
}

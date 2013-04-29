
SOURCE_PAIRS = \
    gripselectionmodel \
    propertymodel \
    selecteditemspropertymodel \

for(file, SOURCE_PAIRS) {
    file = ac_gui_$$file
    HEADERS *= models/$${file}.h
    SOURCES *= models/$${file}.cpp
}

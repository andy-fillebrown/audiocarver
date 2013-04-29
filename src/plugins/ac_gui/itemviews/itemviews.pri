
SOURCE_FILES = \
    colordelegate \
    doubledelegate \
    gridlineview \
    gripitemspropertyview \
    instrumentdelegate \
    lengthdelegate \
    propertyview \
    recordbuttondelegate \
    selecteditemspropertyview \
    togglebuttondelegate \
    volumedelegate \
    trackview \

for(file, SOURCE_FILES) {
    header = ac_gui_$${file}.h
    source = ac_gui_$${file}.cpp
    exists($$header): HEADERS *= itemviews/$$header
    exists($$source): SOURCES *= itemviews/$$source
}

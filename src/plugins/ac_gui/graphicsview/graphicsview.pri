
SOURCE_FILES = \
    graphicscontrollabelscene \
    graphicscontrollabelview \
    graphicscontrolscene \
    graphicscontrolview \
    graphicscurvenode \
    graphicsgripnode \
    graphicsguidenode \
    graphicshorizontalscene \
    graphicshorizontalview \
    graphicsnode \
    graphicslabelview \
    graphicspathnode \
    graphicspitchlabelscene \
    graphicspitchlabelview \
    graphicspitchscene \
    graphicspitchview \
    graphicsrootnode \
    graphicsscene \
    graphicsscenemanager \
    graphicstextnode \
    graphicstimelabelscene \
    graphicstimelabelview \
    graphicsverticallabelview \
    graphicsview \
    graphicsviewmanager \

for(file, SOURCE_FILES) {
    header = ac_gui_$${file}.h
    source = ac_gui_$${file}.cpp
    exists($$header): HEADERS *= graphicsview/$$header
    exists($$source): SOURCES *= graphicsview/$$source
}

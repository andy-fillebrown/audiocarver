
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

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    file = $${SOURCE_FILE_PREFIX}_$$file
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

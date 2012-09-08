
SOURCE_FILES = \
    graphicscontrollabelscene \
    graphicscontrollabelview \
    graphicscontrolscene \
    graphicscontrolview \
    graphicscurveitem \
#    graphicsentityitem \
#    graphicsgripitem \
    graphicsguideitem \
    graphicshorizontalscene \
    graphicshorizontalview \
    graphicsitem \
    graphicslabelview \
    graphicspathitem \
    graphicspitchlabelscene \
    graphicspitchlabelview \
    graphicspitchscene \
    graphicspitchview \
    graphicsrootitem \
    graphicsscene \
    graphicsscenemanager \
    graphicstextitem \
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

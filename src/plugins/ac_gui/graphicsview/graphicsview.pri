
SOURCE_FILES = \
    graphicscontrollabelscene \
    graphicscontrollabelview \
    graphicscontrolscene \
    graphicscontrolview \
#    graphicsentityitem \
#    graphicsgripitem \
    graphicshorizontalscene \
    graphicshorizontalview \
    graphicsitem \
    graphicslabelview \
    graphicspitchlabelscene \
    graphicspitchlabelview \
    graphicspitchscene \
    graphicspitchview \
    graphicsscene \
    graphicsscenemanager \
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

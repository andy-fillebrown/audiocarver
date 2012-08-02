
SOURCE_FILES = \
    iaggregate \
    iclassfactory \
    idatabase \
    idataobjectfactory \
    ifiler \
    ifilerfactory \
    imodel \
    imodeldata \
    imodeldatawatcher \
    imodelitem \
    imodelitemlist \
    imodelitemwatcher \
    iorphanage \
    iqmodel \
    isession \
    iunknown \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    name = $${SOURCE_FILE_PREFIX}_$$file
    header = $${name}.h
    source = $${name}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

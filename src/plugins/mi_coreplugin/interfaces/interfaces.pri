
SOURCE_FILES = \
    idatabase \
    ifactory \
    ifiler \
    iaggregate \
    iaggregator \
    imodel \
    imodeldata \
    imodeldatawatcher \
    imodelitem \
    imodelitemwatcher \
    imodellist \
    iobject \
    iorphanage \
    iunknown \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    name = $$SOURCE_FILE_PREFIX$$file
    header = $${name}.h
    source = $${name}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

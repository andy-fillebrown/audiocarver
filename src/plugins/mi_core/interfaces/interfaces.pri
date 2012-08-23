
SOURCE_FILES = \
    iaggregate \
    idatabase \
    idatabaseobjectfactory \
    ifilefiler \
    ifilerfactory \
    imodel \
    imodeldata \
    imodeldatawatcher \
    imodelitem \
    imodelitemlist \
    imodelitemwatcher \
    iorphanage \
    iqmodel \
    ireader \
    isession \
    iunknown \
    iwriter \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    header = $${file}.h
    exists($$header): HEADERS *= $$DIR/$$header
}

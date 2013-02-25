
SOURCE_FILES = \
    iaggregate \
    icomponent \
    idatabase \
    idatabaseobjectfactory \
    ifilefiler \
    ifilerfactory \
    imodel \
    imodeldata \
    imodeldatawatcher \
    imodelitem \
    imodelitemlist \
    imodelitemlistwatcher \
    imodelitemwatcher \
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

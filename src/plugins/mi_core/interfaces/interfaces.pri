
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

for(file, SOURCE_FILES) {
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= interfaces/$$header
}

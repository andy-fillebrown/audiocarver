
SOURCE_FILES = \
    iaggregate \
    icomponent \
    idatabase \
    idatabaseobjectfactory \
    idatabasewatcher \
    ifiler \
    ifilerfactory \
    imodel \
    imodelitem \
    imodelitemwatcher \
    imodellistwatcher \
    ireader \
    isession \
    iunknown \
    iwriter \

for(file, SOURCE_FILES) {
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= interfaces/$$header
}

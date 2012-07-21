
SOURCE_FILES = \
    iaggregate \
    iaggregator \
    idatabase \
    idataobjectfactory \
    ifiler \
    ifilerfactory \
    imodel \
    imodeldata \
    imodelitem \
    imodellist \
    iobject \
    iorphanage \
    iunknown \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    name = mi_$$file
    header = $${name}.h
    source = $${name}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

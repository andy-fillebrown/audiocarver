
SOURCE_FILES = \
#    idatabase \
    iaggregate \
    iaggregator \
    imodel \
    imodeldata \
    imodelitem \
    imodellist \
    iobject \
    iunknown \

DIR = interfaces
PREFIX = mi_

for(file, SOURCE_FILES) {
    name = $$PREFIX$$file
    header = $${name}.h
    source = $${name}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

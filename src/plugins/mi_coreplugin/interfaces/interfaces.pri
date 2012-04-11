
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

_DIR_ = $$dirname(_FILE_)
_DIR_ = $$basename(_DIR_)
for(file, SOURCE_FILES) {
    name = $$SOURCE_FILE_PREFIX$$file
    header = $${name}.h
    source = $${name}.cpp
    exists($$header): HEADERS *= $$_DIR_/$$header
    exists($$source): SOURCES *= $$_DIR_/$$source
}


SOURCE_FILES *= \
    igraphicscurvedata \
    igraphicsdata \
    igraphicsdelegate \
    igraphicsitem \
    igraphicsiteminfo \
    igripdata \
    igriplistdata \
    iplaycursor \
    ipoint \
#    iqaudioengine \
    iselectionset \
    iselectionsetwatcher \
#    isynthesizer \

for(file, SOURCE_FILES) {
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= interfaces/$$header
    exists($$source): SOURCES *= interfaces/$$source
}

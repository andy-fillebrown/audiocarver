
SOURCE_FILES *= \
#    igraphicscurve \
#    igraphicsentity \
    igraphicsdata \
    igraphicsitem \
    igrip \
    iplaycursor \
    ipoint \
#    iqaudioengine \
    iselectionset \
    iselectionsetwatcher \
#    isynthesizer \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

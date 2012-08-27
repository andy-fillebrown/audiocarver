
SOURCE_FILES *= \
    ichildentity \
    ientity \
    igraphicsitem \
    igraphicsscene \
    igraphicsview \
    igraphicsviewgroup \
    igraphicsviewmanager \
    igrip \
    iparententity \
    iplaycursor \
    ipoint \
#    iqaudioengine \
    isubentity \
#    isynthesizer \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

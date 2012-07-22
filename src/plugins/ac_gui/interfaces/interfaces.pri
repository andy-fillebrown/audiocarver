
SOURCE_FILES *= \
    ichildentity \
    ientity \
    igraphicsscene \
    igraphicsview \
    igraphicsviewgroup \
    igraphicsviewmanager \
    igrip \
    iparententity \
    isubentity \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    name = ac_$$file
    header = $${name}.h
    source = $${name}.cpp
    exists($$header): HEADERS *= $$DIR/$$header
    exists($$source): SOURCES *= $$DIR/$$source
}

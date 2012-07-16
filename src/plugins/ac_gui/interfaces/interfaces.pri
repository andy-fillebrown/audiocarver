
SOURCE_FILES *= \
    ichildentity \
    ientity \
#    ientityitem \
    igraphicsscene \
    igraphicsview \
    igraphicsviewgroup \
    igraphicsviewmanager \
#    igripitem \
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

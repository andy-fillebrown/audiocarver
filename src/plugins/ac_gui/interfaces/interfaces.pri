
SOURCE_FILES *= \
    igraphicsdelegate \
    igraphicseditor \
    igraphicsgrip \
    igraphicsgriplist \
    igraphicsitem \
    iplaycursor \
#    iqaudioengine \
#    isynthesizer \

for(file, SOURCE_FILES) {
    header = $${file}.h
    source = $${file}.cpp
    exists($$header): HEADERS *= interfaces/$$header
    exists($$source): SOURCES *= interfaces/$$source
}

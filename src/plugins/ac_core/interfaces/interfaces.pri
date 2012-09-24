
SOURCE_FILES = \
    iplaycursor \
    ipoints \
    iqaudioengine \
    isynthesizer \

DIR = $$dirname(_FILE_)
DIR = $$basename(DIR)
for(file, SOURCE_FILES) {
    file = $${file}.h
    exists($$file): HEADERS *= $$DIR/$$file
}

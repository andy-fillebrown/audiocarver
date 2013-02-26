
SOURCE_FILES = \
    iplaycursor \
    ipoints \
    iqaudioengine \
    isynthesizer \

for(file, SOURCE_FILES) {
    file = {file}.h
    exists($$file): HEADERS *= interfaces/$$file
}


SOURCE_FILES = \
    copyfiler \

for(file, SOURCE_FILES) {
    name = ac_gui_$$file
    header = $${name}.h
    source = $${name}.cpp
    exists($$header): HEADERS *= filers/$$header
    exists($$source): SOURCES *= filers/$$source
}

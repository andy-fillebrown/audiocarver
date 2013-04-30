
SOURCE_FILES = \
    math \
    scopeddatabaseread \
    scopeddatabasewrite \
    scopeddatachange \
    scopediteminsert \
    scopeditemremove \
    scopedparentchange \
    utilities \

for(file, SOURCE_FILES) {
    header = mi_core_$${file}.h
    source = mi_core_$${file}.cpp
    exists($$header): HEADERS *= tools/$$header
    exists($$source): SOURCES *= tools/$$source
}

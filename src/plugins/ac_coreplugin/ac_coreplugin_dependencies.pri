
include(../mi_coreplugin/mi_coreplugin.pri)

DIRS = \
    dataobjects/gridlines \
    dataobjects \
    factories \
    implementations \
    . \

for(dir, DIRS) {
    INCLUDEPATH *= $$PWD/$$dir
    DEPENDPATH *= $$PWD/$$dir
}

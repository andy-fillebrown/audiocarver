
include(../mi_coreplugin/mi_coreplugin.pri)

DIRS = \
    dataobjects \
    implementations \
    . \

for(dir, DIRS) {
    INCLUDEPATH *= $$PWD/$$dir
    DEPENDPATH *= $$PWD/$$dir
}

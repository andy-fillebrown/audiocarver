
include(../mi_coreplugin/mi_coreplugin.pri)

DIRS = \
    implementations \
    score \
    settings \
    . \

for(dir, DIRS) {
    INCLUDEPATH *= $$PWD/$$dir
    DEPENDPATH *= $$PWD/$$dir
}

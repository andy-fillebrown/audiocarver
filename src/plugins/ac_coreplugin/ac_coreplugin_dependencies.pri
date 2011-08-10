
include(../mi_coreplugin/mi_coreplugin.pri)

DIRS = \
    implementations \
    items \
    tools \
    . \

for(dir, DIRS) {
    INCLUDEPATH *= $$PWD/$$dir
    DEPENDPATH *= $$PWD/$$dir
}

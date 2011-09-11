
include(../mi_coreplugin/mi_coreplugin.pri)

DIRS = \
    implementations \
    items \
    model \
    tools \
    . \

for(dir, DIRS) {
    INCLUDEPATH *= $$PWD/$$dir
    DEPENDPATH *= $$PWD/$$dir
}

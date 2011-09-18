
include(../mi_coreplugin/mi_coreplugin.pri)

DIRS = \
    dataobjects \
    implementations \
    graphicsitems \
    model \
    tools \
    . \

for(dir, DIRS) {
    INCLUDEPATH *= $$PWD/$$dir
    DEPENDPATH *= $$PWD/$$dir
}

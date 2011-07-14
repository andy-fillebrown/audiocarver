
include(../mi_coreplugin/mi_coreplugin.pri)

DIRS = \
    graphicsscene \
    graphicsview \
    implementations \
    interfaces \
    . \

for(dir, DIRS) {
    INCLUDEPATH *= $$PWD/$$dir
    DEPENDPATH *= $$PWD/$$dir
}

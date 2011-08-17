
include(../mi_guiplugin/mi_guiplugin.pri)
include(../ac_coreplugin/ac_coreplugin.pri)

DIRS = \
    factories \
    graphicsitem/gridlines \
    graphicsitem \
    graphicsscene \
    graphicsview \
    implementations \
    itemviews \
    . \

for(dir, DIRS) {
    INCLUDEPATH *= $$PWD/$$dir
    DEPENDPATH *= $$PWD/$$dir
}

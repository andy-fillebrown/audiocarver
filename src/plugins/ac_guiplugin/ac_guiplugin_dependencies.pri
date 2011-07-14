
include(../mi_guiplugin/mi_guiplugin.pri)
include(../ac_coreplugin/ac_coreplugin.pri)

DIRS = \
    graphicsitem \
    graphicsscene \
    graphicsview \
    implementations \
    . \

for(dir, DIRS) {
    INCLUDEPATH *= $$PWD/$$dir
    DEPENDPATH *= $$PWD/$$dir
}


include(../mi_editorplugin/mi_editorplugin.pri)
include(../ac_sceneplugin/ac_sceneplugin.pri)

DIRS = \
    classes \
    implementations \
    . \

for(dir, DIRS) {
    INCLUDEPATH *= $$PWD/$$dir
    DEPENDPATH *= $$PWD/$$dir
}

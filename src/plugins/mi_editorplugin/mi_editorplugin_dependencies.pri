
include(../mi_sceneplugin/mi_sceneplugin.pri)

DIRS = \
    classes \
    implementations \
    interfaces \
    . \

for(dir, DIRS) {
    INCLUDEPATH *= $$PWD/$$dir
    DEPENDPATH *= $$PWD/$$dir
}

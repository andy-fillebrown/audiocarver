
include(../mi_databaseplugin/mi_databaseplugin.pri)

DIRS = \
    classes \
    implementations \
    settings \
    . \

for(dir, DIRS) {
    INCLUDEPATH *= $$PWD/$$dir
    DEPENDPATH *= $$PWD/$$dir
}

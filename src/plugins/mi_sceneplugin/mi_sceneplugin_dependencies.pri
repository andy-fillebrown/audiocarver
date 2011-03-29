
include(../mi_databaseplugin/mi_databaseplugin.pri)

DIRS = \
    classes \
    interfaces \
    . \

for(dir, DIRS) {
    INCLUDEPATH *= $$PWD/$$dir
    DEPENDPATH *= $$PWD/$$dir
}

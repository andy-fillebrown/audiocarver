
include(../mi_sceneplugin/mi_sceneplugin.pri)
include(../ac_databaseplugin/ac_databaseplugin.pri)

DIRS = \
    implementations \
    items \
    scenes \
    . \

for(dir, DIRS) {
    INCLUDEPATH *= $$PWD/$$dir
    DEPENDPATH *= $$PWD/$$dir
}

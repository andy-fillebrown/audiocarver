
include(../coreplugin/coreplugin.pri)

DIRS = \
    database \
    interfaces \
    . \

for(dir, DIRS) {
    INCLUDEPATH *= $$PWD/$$dir
    DEPENDPATH *= $$PWD/$$dir
}


include(../coreplugin/coreplugin.pri)

DIRS = \
    classes \
    interfaces \
    . \

for(dir, DIRS) {
    INCLUDEPATH *= $$PWD/$$dir
    DEPENDPATH *= $$PWD/$$dir
}

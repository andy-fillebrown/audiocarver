
include(../qt_coreplugin/coreplugin.pri)

DIRS = \
    components \
    database \
    interfaces \
    . \

for(dir, DIRS) {
    INCLUDEPATH *= $$PWD/$$dir
    DEPENDPATH *= $$PWD/$$dir
}

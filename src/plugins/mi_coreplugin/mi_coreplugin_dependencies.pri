
include(../qt_coreplugin/coreplugin.pri)

DIRS = \
    components \
    dataobjects \
    interfaces \
    tools \
    . \

for(dir, DIRS) {
    INCLUDEPATH *= $$PWD/$$dir
    DEPENDPATH *= $$PWD/$$dir
}

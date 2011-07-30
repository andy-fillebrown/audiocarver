
include(../qt_coreplugin/coreplugin.pri)

DIRS = \
    dataobjects/settings \
    components \
    dataobjects \
    factories \
    interfaces \
    tools \
    . \

for(dir, DIRS) {
    INCLUDEPATH *= $$PWD/$$dir
    DEPENDPATH *= $$PWD/$$dir
}

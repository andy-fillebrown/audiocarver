
QT *= sql
QT *= xml

include(../../libs/extensionsystem/extensionsystem.pri)
include(../../libs/utils/utils.pri)

DIRS = \
    .. \
    actionmanager \
    dialogs \
    interfaces \
    . \

for(dir, DIRS) {
    INCLUDEPATH *= $$PWD/$$dir
    DEPENDPATH *= $$PWD/$$dir
}


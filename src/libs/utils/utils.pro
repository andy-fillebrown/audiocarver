TEMPLATE = lib
TARGET   = Utils
QT += gui

CONFIG += dll
include($$PWD/../../audiocarverlibrary.pri)

include(utils-lib.pri)

OTHER_FILES += utils.pri

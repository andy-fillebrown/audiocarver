# check qt version
contains(QT_VERSION, ^4\\.[0-6]\\..*) {
    message("Cannot build AudioCarver with Qt version $${QT_VERSION}.")
    error("Use at least Qt 4.7.")
}

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = src

OTHER_FILES *= \
    testing/test01.ac \
    testing/test02.ac \

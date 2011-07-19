# check qt version
contains(QT_VERSION, ^4\\.[0-6]\\..*) {
    message("Cannot build AudioCarver with Qt version $${QT_VERSION}.")
    error("Use at least Qt 4.7.")
}

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = src

FILETYPES = \
    pluginspec.in \
    pri \
    pro \

VARIABLES = \
    FORMS \
    HEADERS \
    OTHER_FILES \
    RESOURCES \
    SOURCES \

defineTest(addSubdirs) {
    for(subdir, $$1) {
        for(filetype, FILETYPES) {
            OTHER_FILES += $$subdir/*.$$filetype
            for(variable, VARIABLES) {
                values = $$fromfile($${subdir}/$$basename(subdir).pro, $$variable)
                for(value, values) {
                    OTHER_FILES += $$subdir/$$value
                }
            }
        }
        subdirs = $$fromfile($${subdir}/$$basename(subdir).pro, SUBDIRS)
        fullsubdirs =
        for(subsubdir, subdirs) {
            fullsubdirs *= $$subdir/$$subsubdir
        }
        addSubdirs(fullsubdirs)
    }
}

addSubdirs(SUBDIRS)
OTHER_FILES += \
    *.* \
    src/shared/*.* \

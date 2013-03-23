TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = \
    libs \
    plugins \
    app

OTHER_FILES *= \
    _.plugin.prf \
    library.prf \
    rpath.prf \

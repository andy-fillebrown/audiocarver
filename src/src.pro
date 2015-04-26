TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = \
    libs \
    plugins \
    app

OTHER_FILES *= \
    _.plugin.prf \
    _.library.prf \
    _.rpath.prf \

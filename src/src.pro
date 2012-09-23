TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = \
    libs \
    plugins \
    app

OTHER_FILES *= \
    library.prf \
    plugin.prf \
    rpath.prf \

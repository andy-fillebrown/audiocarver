TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = \
    libs \
    plugins \
    app

OTHER_FILES *= \
    _add_source_files.prf \
    library.prf \
    plugin.prf \
    rpath.prf \

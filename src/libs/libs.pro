TEMPLATE = subdirs
CONFIG += ordered

win32 {
    SUBDIRS = \
        libsndfile \
}

SUBDIRS += \
    csound \
    aggregation \
    extensionsystem \
    utils \

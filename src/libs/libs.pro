TEMPLATE = subdirs
CONFIG += ordered

win32 {
    SUBDIRS = \
        libsndfile \
        pthreads \
}

SUBDIRS += \
    csound \
    aggregation \
    extensionsystem \
    utils \

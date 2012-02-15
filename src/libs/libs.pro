TEMPLATE = subdirs
CONFIG += ordered

macx {
    SUBDIRS = \
        sndfile \
}
win32 {
    SUBDIRS = \
        pthreads \
        sndfile \
}

SUBDIRS += \
    csound \
    aggregation \
    extensionsystem \
    utils \

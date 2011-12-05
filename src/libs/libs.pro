TEMPLATE = subdirs
CONFIG += ordered

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

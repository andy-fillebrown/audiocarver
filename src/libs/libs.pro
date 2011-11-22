TEMPLATE = subdirs
CONFIG += ordered

win32 {
    SUBDIRS = \
        libsndfile \
}

SUBDIRS += \
    csound \
    csound/csound64.pro \
    aggregation \
    extensionsystem \
    utils \

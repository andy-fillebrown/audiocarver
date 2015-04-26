TARGET = Aggregation
TEMPLATE = lib

include(../../_.library.prf)

DEFINES *= \
    AGGREGATION_LIBRARY \

HEADERS = \
    aggregate.h \
    aggregation_global.h \

SOURCES = \
    aggregate.cpp \

OTHER_FILES *= \
    _.aggregation.prf \

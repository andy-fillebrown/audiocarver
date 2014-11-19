TARGET = Aggregation
TEMPLATE = lib

include(../../library.prf)

DEFINES *= \
    AGGREGATION_LIBRARY \

HEADERS = \
    aggregate.h \
    aggregation_global.h \

SOURCES = \
    aggregate.cpp \

OTHER_FILES *= \
    aggregation.prf \

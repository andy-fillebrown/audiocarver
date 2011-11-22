TARGET = Aggregation
TEMPLATE = lib

load(../../library.prf)

DEFINES *= \
    AGGREGATION_LIBRARY \

HEADERS = \
    aggregate.h \
    aggregation_global.h \

SOURCES = \
    aggregate.cpp \

OTHER_FILES *= \
    aggregation.prf \

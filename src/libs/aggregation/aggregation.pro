TARGET = Aggregation
TEMPLATE = lib

include(../../library.pri)

DEFINES += AGGREGATION_LIBRARY

HEADERS = \
    aggregate.h \
    aggregation_global.h \

SOURCES = \
    aggregate.cpp \

TARGET = mi_pthreads
TEMPLATE = lib

load(../../library.prf)

CONFIG -= qt

CONFIG(debug|release, release) {
    QMAKE_CFLAGS += \
        -finline-functions \
}

DEFINES -= \
    UNICODE \

DEFINES *= \
    HAVE_CONFIG_H \
    __CLEANUP_C \

INCLUDEPATH *= \
    src \
    src/include \

HEADERS = \
    src/implement.h \
    src/pthread.h \
    src/sched.h \
    src/semaphore.h \

SOURCES = \
    src/attr.c \
    src/barrier.c \
    src/cancel.c \
    src/cleanup.c \
    src/condvar.c \
    src/create.c \
    src/dll.c \
    src/errno.c \
    src/exit.c \
    src/fork.c \
    src/global.c \
    src/misc.c \
    src/mutex.c \
    src/nonportable.c \
    src/private.c \
    src/rwlock.c \
    src/sched.c \
    src/semaphore.c \
    src/signal.c \
    src/spin.c \
    src/sync.c \
    src/tsd.c \

LIBS *= \
    -lwsock32 \

OTHER_FILES *= \
    COPYING \
    pthreads.prf \

win32 {
    INCLUDEPATH *= \
        config/windows \

    HEADERS *= \
        config/windows/config.h
}
else {
    error("mi_pthreads should only be built on Windows")
}


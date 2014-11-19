TARGET = audiocarver
TEMPLATE = app
QT *= widgets

include(../../project.prf)
include(../rpath.prf)

DESTDIR = $$PRO_APP_PATH

DEFINES *= \
    PRO_LIBRARY_BASENAME=\\\"$$PRO_LIBRARY_BASENAME\\\" \

SOURCES = \
    main.cpp \

LIBS *= \
    -l$$qtLibraryName(ExtensionSystem) \
    -l$$qtLibraryName(Aggregation) \

win32 {
    RC_FILE = project.rc
    target.path = /bin
    INSTALLS += target
} else:macx {
    LIBS += -framework CoreFoundation
    ICON = audiocarver.icns
    info.input = Info.plist.in
    info.output = $$OUT_PWD/Info.plist
    QMAKE_SUBSTITUTES = info
} else {
    target.path  = /bin
    INSTALLS    += target
}

# Remove "d" suffix so QtCreator finds audiocarver.exe
TARGET = $$PRO_TARGET

OTHER_FILES *= \
    Info.plist.in \
    project.ico \
    project.rc \

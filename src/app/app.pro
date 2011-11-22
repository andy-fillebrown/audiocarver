TARGET = audiocarver
TEMPLATE = app

load(../../project.prf)
load(../rpath.prf)

DESTDIR = $$PRO_APP_PATH

QMAKE_SUBSTITUTES = Info.plist.in

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
    QMAKE_INFO_PLIST = Info.plist
    FILETYPES.files = profile.icns prifile.icns
    FILETYPES.path = Contents/Resources
    QMAKE_BUNDLE_DATA += FILETYPES
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

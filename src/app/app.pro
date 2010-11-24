TEMPLATE = app
TARGET   = audiocarver

include(../../audiocarver.pri)

DESTDIR = $$AC_APP_PATH

DEFINES += AC_LIBRARY_BASENAME=\\\"$$AC_LIBRARY_BASENAME\\\"

SOURCES += main.cpp

LIBS *= \
    -l$$qtLibraryName(ExtensionSystem) \
    -l$$qtLibraryName(Aggregation)

win32 {
    RC_FILE = audiocarver.rc
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

QMAKE_SUBSTITUTES = Info.plist.in

OTHER_FILES += \
    audiocarver.rc \
    Info.plist.in

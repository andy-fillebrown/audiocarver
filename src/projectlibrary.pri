include(../project.pri)

# use precompiled header for libraries by default
isEmpty(PRECOMPILED_HEADER):PRECOMPILED_HEADER = $$PWD/shared/project_pch.h
OTHER_FILES += $$PRECOMPILED_HEADER

win32:DLLDESTDIR = $$PRO_APP_PATH
DESTDIR = $$PRO_LIBRARY_PATH

include(rpath.pri)

TARGET = $$qtLibraryName($$TARGET)

contains(QT_CONFIG, reduce_exports):CONFIG += hide_symbols

!macx {
    win32 {
        target.path = /bin
        target.files = $$DESTDIR/$${TARGET}.dll
    } else {
        target.path = /$$PRO_LIBRARY_BASENAME/$$PRO_APP_TARGET
    }
    INSTALLS += target
}

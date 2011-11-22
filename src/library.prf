include(../project.pri)

win32:DLLDESTDIR = $$PRO_APP_PATH
DESTDIR = $$PRO_LIBRARY_PATH

include(rpath.pri)

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

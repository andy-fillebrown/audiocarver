!isEmpty(AUDIOCARVER_PRI_INCLUDED):error("audiocarver.pri already included")
AUDIOCARVER_PRI_INCLUDED = 1

!verbose:CONFIG += silent

AUDIOCARVER_VERSION = 1.0.0

defineReplace(cleanPath) {
    win32:1 ~= s|\\\\|/|g
    contains(1, ^/.*):pfx = /
    else:pfx =
    segs = $$split(1, /)
    out =
    for(seg, segs) {
        equals(seg, ..):out = $$member(out, 0, -2)
        else:!equals(seg, .):out += $$seg
    }
    return($$join(out, /, $$pfx))
}

defineReplace(targetPath) {
    return($$replace(1, /, $$QMAKE_DIR_SEP))
}

defineReplace(qtLibraryName) {
   unset(LIBRARY_NAME)
   LIBRARY_NAME = $$1
   CONFIG(debug, debug|release) {
      !debug_and_release|build_pass {
          mac:RET = $$member(LIBRARY_NAME, 0)_debug
              else:win32:RET = $$member(LIBRARY_NAME, 0)d
      }
   }
   isEmpty(RET):RET = $$LIBRARY_NAME
   return($$RET)
}

defineTest(minQtVersion) {
    maj = $$1
    min = $$2
    patch = $$3
    isEqual(QT_MAJOR_VERSION, $$maj) {
        isEqual(QT_MINOR_VERSION, $$min) {
            isEqual(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
            greaterThan(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
        }
        greaterThan(QT_MINOR_VERSION, $$min) {
            return(true)
        }
    }
    return(false)
}

# For use in custom compilers which just copy files
win32:i_flag = i
defineReplace(stripDir) {
    return($$basename(1))
}

isEmpty(TEST):CONFIG(debug, debug|release) {
    !debug_and_release|build_pass {
        TEST = 1
    }
}

isEmpty(AC_LIBRARY_BASENAME) {
    AC_LIBRARY_BASENAME = lib
}

DEFINES += AC_LIBRARY_BASENAME=\\\"$$AC_LIBRARY_BASENAME\\\"

equals(TEST, 1) {
    QT += testlib
    DEFINES += WITH_TESTS
}

AC_SOURCE_TREE = $$PWD
isEmpty(AC_BUILD_TREE) {
    pro_dir = $$cleanPath($$_PRO_FILE_PWD_)
    sub_dir = $$cleanPath($$OUT_PWD)
    pro_dir_split = $$split(pro_dir, /)
    sub_dir_split = $$split(sub_dir, /)
    for(dir, sub_dir_split) {
        last_pro_dir = $$last(pro_dir_split)
        last_sub_dir = $$last(sub_dir_split)
        isEqual(last_pro_dir, $$last_sub_dir) {
            pro_dir = $$dirname(pro_dir)
            sub_dir = $$dirname(sub_dir)
            isEqual(sub_dir, $$PRO_SOURCE_TREE) {
                break()
            }
            pro_dir_split = $$split(pro_dir, /)
            sub_dir_split = $$split(sub_dir, /)
        } else {
            break()
        }
    }
    AC_BUILD_TREE = $$sub_dir
}
AC_APP_PATH = $$AC_BUILD_TREE/bin
macx {
    AC_APP_TARGET   = "AudioCarver"
    AC_LIBRARY_PATH = $$AC_APP_PATH/$${IDE_APP_TARGET}.app/Contents/PlugIns
    AC_PLUGIN_PATH  = $$AC_LIBRARY_PATH
    AC_LIBEXEC_PATH = $$AC_APP_PATH/$${IDE_APP_TARGET}.app/Contents/Resources
    AC_DATA_PATH    = $$AC_APP_PATH/$${IDE_APP_TARGET}.app/Contents/Resources
    AC_DOC_PATH     = $$AC_DATA_PATH/doc
    AC_BIN_PATH     = $$AC_APP_PATH/$${AC_APP_TARGET}.app/Contents/MacOS
    contains(QT_CONFIG, ppc):CONFIG += ppc x86
    copydata = 1
    isEmpty(TIGER_COMPAT_MODE):TIGER_COMPAT_MODE=$$(QTC_TIGER_COMPAT)
    isEmpty(TIGER_COMPAT_MODE) {
        QMAKE_CXXFLAGS *= -mmacosx-version-min=10.5
        QMAKE_LFLAGS *= -mmacosx-version-min=10.5
    }
} else {
    win32 {
        contains(TEMPLATE, vc.*)|contains(TEMPLATE_PREFIX, vc):vcproj = 1
    }
    AC_APP_TARGET = audiocarver
    AC_LIBRARY_PATH = $$AC_BUILD_TREE/$$AC_LIBRARY_BASENAME/audiocarver
    AC_PLUGIN_PATH  = $$AC_LIBRARY_PATH/plugins
    AC_LIBEXEC_PATH = $$AC_APP_PATH
    AC_DATA_PATH    = $$AC_BUILD_TREE/share/audiocarver
    AC_DOC_PATH     = $$AC_BUILD_TREE/share/doc/audiocarver
    AC_BIN_PATH     = $$AC_APP_PATH
    !isEqual(AC_SOURCE_TREE, $$AC_BUILD_TREE):copydata = 1
}

INCLUDEPATH += \
    $$AC_SOURCE_TREE/src/libs \
    $$AC_SOURCE_TREE/tools

DEPENDPATH += \
    $$AC_SOURCE_TREE/src/libs \
    $$AC_SOURCE_TREE/tools

LIBS += -L$$AC_LIBRARY_PATH

DEFINES += QT_NO_CAST_TO_ASCII
!macx:DEFINES += QT_USE_FAST_OPERATOR_PLUS QT_USE_FAST_CONCATENATION

unix {
    CONFIG(debug, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/debug-shared
    CONFIG(release, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/release-shared

    CONFIG(debug, debug|release):MOC_DIR = $${OUT_PWD}/.moc/debug-shared
    CONFIG(release, debug|release):MOC_DIR = $${OUT_PWD}/.moc/release-shared

    RCC_DIR = $${OUT_PWD}/.rcc
    UI_DIR = $${OUT_PWD}/.uic
}

linux-g++-* {
    # Bail out on non-selfcontained libraries. Just a security measure
    # to prevent checking in code that does not compile on other platforms.
    QMAKE_LFLAGS += -Wl,--allow-shlib-undefined -Wl,--no-undefined
}

win32-msvc* {
    #Don't warn about sprintf, fopen etc being 'unsafe'
    DEFINES += _CRT_SECURE_NO_WARNINGS
}

# Handle S60 support: default on Windows, conditionally built on other platforms.
macx:SUPPORT_QT_S60 = $$(QTCREATOR_WITH_S60)
else:SUPPORT_QT_S60=1

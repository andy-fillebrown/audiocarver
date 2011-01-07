include(../project.pri)

# use gui precompiled header for plugins by default
isEmpty(PRECOMPILED_HEADER):PRECOMPILED_HEADER = $$PWD/shared/project_gui_pch.h
OTHER_FILES += $$PRECOMPILED_HEADER

isEmpty(PROVIDER) {
    PROVIDER = $$PRO_AUTHOR_NOSPACE
}

DESTDIR = $$PRO_PLUGIN_PATH/$$PROVIDER
LIBS += -L$$DESTDIR
INCLUDEPATH += $$PRO_SOURCE_TREE/src/plugins
DEPENDPATH += $$PRO_SOURCE_TREE/src/plugins

# copy the plugin spec
isEmpty(TARGET) {
    error("$$_FILE_: You must provide a TARGET")
}

PLUGINSPEC = $$_PRO_FILE_PWD_/$${TARGET}.pluginspec
PLUGINSPEC_IN = $${PLUGINSPEC}.in
OTHER_FILES += $$PLUGINSPEC_IN
PLUGINSPEC = $$OUT_PWD/$${TARGET}.pluginspec
QMAKE_SUBSTITUTES += $${PLUGINSPEC}.in
copy2build.output = $$DESTDIR/${QMAKE_FUNC_FILE_IN_stripDir}
copy2build.input = PLUGINSPEC
isEmpty(vcproj):copy2build.variable_out = PRE_TARGETDEPS
copy2build.commands = $$QMAKE_COPY ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
copy2build.name = COPY ${QMAKE_FILE_IN}
copy2build.CONFIG += no_link
QMAKE_EXTRA_COMPILERS += copy2build

macx {
    !isEmpty(TIGER_COMPAT_MODE) {
        QMAKE_LFLAGS_SONAME = -Wl,-install_name,@executable_path/../PlugIns/$${PROVIDER}/
    } else {
        QMAKE_LFLAGS_SONAME = -Wl,-install_name,@rpath/PlugIns/$${PROVIDER}/
        QMAKE_LFLAGS += -Wl,-rpath,@loader_path/../../
    }
} else:linux-* {
    # do the rpath by hand since it's not possible to use ORIGIN in QMAKE_RPATHDIR
    QMAKE_RPATHDIR += \$\$ORIGIN
    QMAKE_RPATHDIR += \$\$ORIGIN/..
    QMAKE_RPATHDIR += \$\$ORIGIN/../..
    IDE_PLUGIN_RPATH = $$join(QMAKE_RPATHDIR, ":")
    QMAKE_LFLAGS += -Wl,-z,origin \'-Wl,-rpath,$${PRO_PLUGIN_RPATH}\'
    QMAKE_RPATHDIR =
}

contains(QT_CONFIG, reduce_exports):CONFIG += hide_symbols

CONFIG += plugin plugin_with_soname

!macx {
    target.path = /$$PRO_LIBRARY_BASENAME/$$PRO_APP_TARGET/plugins/$$PROVIDER
    pluginspec.files += $${TARGET}.pluginspec
    pluginspec.path = /$$PRO_LIBRARY_BASENAME/$$PRO_APP_TARGET/plugins/$$PROVIDER
    INSTALLS += target pluginspec
}

TARGET = $$qtLibraryName($$TARGET)
macx {
    !isEmpty(TIGER_COMPAT_MODE) {
        QMAKE_LFLAGS_SONAME = -Wl,-install_name,@executable_path/../PlugIns/
    } else {
        QMAKE_LFLAGS_SONAME = -Wl,-install_name,@rpath/PlugIns/
        QMAKE_LFLAGS += -Wl,-rpath,@loader_path/../
    }
} else:linux-* {
    #do the rpath by hand since it's not possible to use ORIGIN in QMAKE_RPATHDIR
    # this expands to $ORIGIN (after qmake and make), it does NOT read a qmake var
    QMAKE_RPATHDIR += \$\$ORIGIN/../$$PRO_LIBRARY_BASENAME/$$PRO_APP_TARGET
    PRO_PLUGIN_RPATH = $$join(QMAKE_RPATHDIR, ":")

    QMAKE_LFLAGS += -Wl,-z,origin \'-Wl,-rpath,$${PRO_PLUGIN_RPATH}\'
    QMAKE_RPATHDIR =
}

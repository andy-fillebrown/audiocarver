include(coreplugin_dependencies.pri)

LIBS *= -L$$PRO_PLUGIN_PATH
LIBS *= -l$$qtLibraryName(Core)

# for ide_version.h
INCLUDEPATH *= $$AC_BUILD_TREE/src/plugins/coreplugin
DEPENDPATH *= $$AC_BUILD_TREE/src/plugins/coreplugin

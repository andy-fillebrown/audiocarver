
include(coreplugin_dependencies.pri)

# for pro_version.h
INCLUDEPATH *= $$PRO_BUILD_TREE/src/plugins/coreplugin
DEPENDPATH *= $$PRO_BUILD_TREE/src/plugins/coreplugin

LIBS *= -L$$PRO_PLUGIN_PATH
LIBS *= -l$$qtLibraryName(QtCorePlugin)

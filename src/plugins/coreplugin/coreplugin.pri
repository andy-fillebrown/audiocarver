
include(coreplugin_dependencies.pri)

LIBS *= -L$$PRO_PLUGIN_PATH
LIBS *= -l$$qtLibraryName(Core)

# for pro_version.h
INCLUDEPATH *= $$PRO_BUILD_TREE/src/plugins/coreplugin
DEPENDPATH *= $$PRO_BUILD_TREE/src/plugins/coreplugin


include(databaseplugin_dependencies.pri)

LIBS *= -L$$PRO_PLUGIN_PATH
LIBS *= -l$$qtLibraryName(Database)

# for ide_version.h
INCLUDEPATH *= $$PRO_BUILD_TREE/src/plugins/databaseplugin
DEPENDPATH *= $$PRO_BUILD_TREE/src/plugins/databaseplugin

include(glsceneplugin_dependencies.pri)

LIBS *= -L$$PRO_PLUGIN_PATH
LIBS *= -l$$qtLibraryName(GLScene)
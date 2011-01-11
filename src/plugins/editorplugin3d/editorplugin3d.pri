include(editorplugin3d_dependencies.pri)

LIBS *= -L$$PRO_PLUGIN_PATH
LIBS *= -l$$qtLibraryName(Editor3D)

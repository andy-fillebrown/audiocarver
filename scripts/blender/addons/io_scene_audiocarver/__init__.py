
# <pep8-80 compliant>

bl_info = {
    "name": "AudioCarver format",
    "author": "Andrew Fillebrown, Andy",
    "blender": (2, 5, 7),
    "location": "File > Import",
    "description": "Import AudioCarver",
    "warning": "",
    "wiki_url": "",
    "tracker_url": "",
    "support": 'COMMUNITY',
    "category": "Import"}

if "bpy" in locals():
    import imp
    if "import_ac" in locals():
        imp.reload(import_ac)

import bpy
from bpy.props import StringProperty, BoolProperty, EnumProperty
from bpy_extras.io_utils import (ImportHelper,
                                 ExportHelper,
                                 axis_conversion,
                                 path_reference_mode,
                                 )


class ImportAudioCarver(bpy.types.Operator, ImportHelper):
    '''Import an AudioCarver file'''
    bl_idname = "import_scene.audiocarver"
    bl_label = "Import AudioCarver"
    bl_options = {'PRESET', 'UNDO'}

    filename_ext = ".ac"
    filter_glob = StringProperty(default="*.ac", options={'HIDDEN'})

    axis_forward = EnumProperty(
            name="Forward",
            items=(('X', "X Forward", ""),
                   ('Y', "Y Forward", ""),
                   ('Z', "Z Forward", ""),
                   ('-X', "-X Forward", ""),
                   ('-Y', "-Y Forward", ""),
                   ('-Z', "-Z Forward", ""),
                   ),
            default='Z',
            )

    axis_up = EnumProperty(
            name="Up",
            items=(('X', "X Up", ""),
                   ('Y', "Y Up", ""),
                   ('Z', "Z Up", ""),
                   ('-X', "-X Up", ""),
                   ('-Y', "-Y Up", ""),
                   ('-Z', "-Z Up", ""),
                   ),
            default='Y',
            )

    def execute(self, context):
        from . import import_ac

        keywords = self.as_keywords(ignore=("axis_forward",
                                            "axis_up",
                                            "filter_glob",
                                            ))
        global_matrix = axis_conversion(from_forward=self.axis_forward,
                                        from_up=self.axis_up,
                                        ).to_4x4()
        keywords["global_matrix"] = global_matrix

        return import_ac.load(self, context, **keywords)


def menu_func_import(self, context):
    self.layout.operator(ImportAudioCarver.bl_idname,
                         text="AudioCarver (.ac)")


def register():
    bpy.utils.register_module(__name__)
    bpy.types.INFO_MT_file_import.append(menu_func_import)


def unregister():
    bpy.utils.unregister_module(__name__)
    bpy.types.INFO_MT_file_import.remove(menu_func_import)


if __name__ == "__main__":
    register()

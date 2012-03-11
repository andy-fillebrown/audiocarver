
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
    if "import_audiocarver" in locals():
        imp.reload(import_audiocarver)

import bpy
# from bpy.props import StringProperty, BoolProperty, EnumProperty
from bpy.props import (FloatProperty,
                       StringProperty
                       )

from bpy_extras.io_utils import (ImportHelper,
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

    pre_roll = FloatProperty(name="Pre-Roll", default=3.0)
    post_roll = FloatProperty(name="Post-Roll", default=3.0)
    height = FloatProperty(name="Height", default=10.0)
    min_pitch = FloatProperty(name="Minimum Pitch", default=0.0)
    max_pitch = FloatProperty(name="Maximum Pitch", default=127.0)
    inner_radius = FloatProperty(name="Inner Radius", default=10.0)
    track_width = FloatProperty(name="Track Width", default=1.0)

    def execute(self, context):
        from . import import_audiocarver
        input_variables = import_audiocarver.InputVariables()
        input_variables.filepath = self.filepath
        input_variables.pre_roll = self.pre_roll
        input_variables.post_roll = self.post_roll
        input_variables.height = self.height
        input_variables.min_pitch = self.min_pitch
        input_variables.max_pitch = self.max_pitch
        input_variables.inner_radius = self.inner_radius
        input_variables.track_width = self.track_width
        return import_audiocarver.load(self, context, input_variables)


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
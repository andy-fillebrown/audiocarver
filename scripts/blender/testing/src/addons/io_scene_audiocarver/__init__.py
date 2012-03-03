'''
Created on Mar 3, 2012

@author: Andy
'''

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
    if "import_audiocarver" in locals():
        imp.reload(import_audiocarver)

import bpy
# from bpy.props import StringProperty, BoolProperty, EnumProperty
from bpy.props import (FloatProperty,
                       StringProperty
                       )

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

    pre_roll = FloatProperty(name="Pre-Roll", default=3.0)
    post_roll = FloatProperty(name="Post-Roll", default=3.0)
    height = FloatProperty(name="Height", default=10.0)
    min_pitch = FloatProperty(name="Minimum Pitch", default=0.0)
    max_pitch = FloatProperty(name="Maximum Pitch", default=127.0)
    inner_radius = FloatProperty(name="Inner Radius", default=10.0)
    track_width = FloatProperty(name="Track Width", default=1.0)

    def execute(self, context):
        from . import import_audiocarver
        return import_audiocarver.load(self,
                              context,
                              self.filepath,
                              self.pre_roll,
                              self.post_roll,
                              self.height,
                              self.min_pitch,
                              self.max_pitch,
                              self.inner_radius,
                              self.track_width
                              )


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


# <pep8 compliant>

import bpy

class InputVariables:
    filepath = ""
    pre_roll = 0.0
    post_roll = 0.0
    height = 0.0
    min_pitch = 0.0
    max_pitch = 0.0
    inner_radius = 0.0
    track_width = 0.0

    def print_values(self):
        print("filepath     =", self.filepath)
        print("pre_roll     =", self.pre_roll)
        print("post_roll    =", self.post_roll)
        print("height       =", self.height)
        print("min_pitch    =", self.min_pitch)
        print("max_pitch    =", self.max_pitch)
        print("inner_radius =", self.inner_radius)
        print("track_width  =", self.track_width)

input = InputVariables()

def load(operator,
         context,
         filepath,
         pre_roll,
         post_roll,
         height,
         min_pitch,
         max_pitch,
         inner_radius,
         track_width
         ):
    input.filepath = filepath
    input.pre_roll = pre_roll
    input.post_roll = post_roll
    input.height = height
    input.min_pitch = min_pitch
    input.max_pitch = max_pitch
    input.inner_radius = inner_radius
    input.track_width = track_width

    print("\nImporting AudioCarver file ...\n")
    input.print_values()
    print("\n... done\n")

    return {'FINISHED'}

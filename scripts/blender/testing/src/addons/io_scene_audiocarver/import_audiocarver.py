
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
        print("file_path    =", self.filepath)
        print("pre_roll     =", self.pre_roll)
        print("post_roll    =", self.post_roll)
        print("height       =", self.height)
        print("min_pitch    =", self.min_pitch)
        print("max_pitch    =", self.max_pitch)
        print("inner_radius =", self.inner_radius)
        print("track_width  =", self.track_width)

input_variables = InputVariables()

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
    input_variables.filepath = filepath
    input_variables.pre_roll = pre_roll
    input_variables.post_roll = post_roll
    input_variables.height = height
    input_variables.min_pitch = min_pitch
    input_variables.max_pitch = max_pitch
    input_variables.inner_radius = inner_radius
    input_variables.track_width = track_width

    print("\nImporting AudioCarver file ...")
    input_variables.print_values()
    print("... done\n")

    return {'FINISHED'}

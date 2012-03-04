
class InputVariables:
    filepath = ""
    pre_roll = 0.0
    post_roll = 0.0
    height = 0.0
    min_pitch = 0.0
    max_pitch = 0.0
    inner_radius = 0.0
    track_width = 0.0

    def trace(self):
        print("file_path    =", self.filepath)
        print("pre_roll     =", self.pre_roll)
        print("post_roll    =", self.post_roll)
        print("height       =", self.height)
        print("min_pitch    =", self.min_pitch)
        print("max_pitch    =", self.max_pitch)
        print("inner_radius =", self.inner_radius)
        print("track_width  =", self.track_width)

input_variables = InputVariables()


import xml.dom as Dom
import xml.dom.minidom as Xml


def trace_node(node, tabCount = 0):
    if Dom.Node.TEXT_NODE == node.nodeType:
        return 0

    tabs = ""
    i = 0
    while i < tabCount:
        i += 1
        tabs += "    "

    attribute_string = " "
    i = 0
    attributes = node.attributes
    while i < attributes.length:
        attribute = attributes.item(i)
        if 0 < i:
            attribute_string += ", "
        i += 1
        attribute_string += attribute.name
        attribute_string += " = "
        attribute_string += attribute.value
    if attribute_string == " ":
        attribute_string = ""

    print(tabs + "<" + node.nodeName + attribute_string + ">")

    tabCount += 1
    for node in node.childNodes:
        trace_node(node, tabCount)
    tabCount -= 1


def load(operator,
         context,
         inputVariables
         ):
    input_variables = inputVariables

    print("\nImporting AudioCarver file ...")
    input_variables.trace()
    print("... done\n")

    dom = Xml.parse(input_variables.filepath)
    for node in dom.childNodes:
        trace_node(node)

    return {'FINISHED'}

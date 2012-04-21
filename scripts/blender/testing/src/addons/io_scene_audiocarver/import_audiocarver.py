
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
         fileName):
    print("\nImporting AudioCarver file ...")
    print(fileName)
    print("... done\n")
    dom = Xml.parse(fileName)
    for node in dom.childNodes:
        trace_node(node)
    return {'FINISHED'}

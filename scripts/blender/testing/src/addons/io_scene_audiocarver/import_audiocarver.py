
import bpy

import xml.dom as Dom
import xml.dom.minidom as Xml


layer_1 = (True, False, False, False, False, False, False, False, False, False,
           False, False, False, False, False, False, False, False, False, False)
layer_2 = (False, True, False, False, False, False, False, False, False, False,
           False, False, False, False, False, False, False, False, False, False)

note_count = 1
note_layer = 8
note_object_names = {
                     'Note.Root.Empty',
                     'Note.Velocity.Scale.Y',
                     'Note.Tail.Scale.X',
                     'Note.Head.Mesh',
                     'Note.Tail.Mesh'
                     }
timeline_count = 1
timeline_layer = 11
timeline_parent_layer = 10


def clear_ss():
    bpy.ops.object.select_all(action = 'DESELECT')


def import_note(note_node, color):
    if "Note" != note_node.nodeName:
        print("Xml node is not a note.")
        return

    global layer_1
    global layer_2
    global note_count
    global note_layer
    global note_object_names

    note_count += 1

    # Clear existing selection.
    clear_ss()

    # Select and duplicate the note template objects.
    bpy.ops.object.select_by_layer(layers = note_layer + 1)
    bpy.ops.object.duplicate()

    # Rename the new note objects and set their layers.
    for note_object_name in note_object_names:
        obj = bpy.data.objects[note_object_name + '.001']
        new_name = obj.name[:-3] + str(note_count)
        obj.name = new_name
        clear_ss()
        bpy.ops.object.select_pattern(pattern = new_name)
        if ("Note.Head.Mesh" == note_object_name):
            bpy.ops.object.move_to_layer(layers = layer_2)
        else:
            bpy.ops.object.move_to_layer(layers = layer_1)

    # Get the first and last pitch point positions.
    pitch_curve_node = Dom.Node
    first_pt_node = Dom.Node
    last_pt_node = Dom.Node
    first_pt_pos_value = 0
    last_pt_pos_value = 0
    for child_node in note_node.childNodes:
        if "PitchCurve" == child_node.nodeName:
            pitch_curve_node = child_node
            break
    for point_node in pitch_curve_node.childNodes:
        if "Point" == point_node.nodeName:
            first_pt_node = point_node
            break
    for point_node in pitch_curve_node.childNodes:
        if "Point" == point_node.nodeName:
            last_pt_node = point_node
    i = 0
    while i < first_pt_node.attributes.length:
        attribute = first_pt_node.attributes.item(i)
        if "position" == attribute.name:
            first_pt_pos_value = attribute.value.split(" ")
            break
        i += 1
    i = 0
    while i < last_pt_node.attributes.length:
        attribute = last_pt_node.attributes.item(i)
        if "position" == attribute.name:
            last_pt_pos_value = attribute.value.split(" ")
            break

    first_pt_x = float(first_pt_pos_value[0])
    first_pt_y = float(first_pt_pos_value[1])
    last_pt_x = float(last_pt_pos_value[0])

    # Move the note root object to the first pitch point.
    note_root_object = bpy.data.objects['Note.Root.Empty.' + str(note_count)]
    note_root_object.location[0] = first_pt_x
    note_root_object.location[2] = first_pt_y

    # Scale the note tail object to the pitch curve length
    note_tail_scale_object = bpy.data.objects['Note.Tail.Scale.X.' + str(note_count)]
    note_tail_scale_object.scale[0] = last_pt_x - first_pt_x

    # Get the note's velocity/volume.
    velocity = 1.0
    i = 0
    while i < note_node.attributes.length:
        attribute = note_node.attributes.item(i)
        if "volume" == attribute.name:
            velocity = float(attribute.value)
            break;
        i += 1

    # Scale the note velocity object to the volume.
    note_volume_scale_object = bpy.data.objects['Note.Velocity.Scale.Y.' + str(note_count)]
    note_volume_scale_object.scale[2] = velocity


def import_track(track_node):
    print("\nImporting track ...")
    color = '#ffffff'
    i = 0
    attributes = track_node.attributes
    while i < attributes.length:
        attribute = attributes.item(i)
        if "color" == attribute.name:
            color = attribute.value
        i += 1
    for child_node in track_node.childNodes:
        if "NoteList" == child_node.nodeName:
            for note_node in child_node.childNodes:
                if "Note" == note_node.nodeName:
                    import_note(note_node, color)


def import_timeline(timeline_node):
    global timeline_count

    timeline_label = ""
    timeline_location = 0.0
    attributes = timeline_node.attributes
    i = 0
    while i < attributes.length:
        attribute = attributes.item(i)
        if "label" == attribute.name:
            timeline_label = attribute.value
        elif "location" == attribute.name:
            timeline_location = float(attribute.value)
        i += 1

    if -1 != timeline_label.find("."):
        return
    if 0.0 == timeline_location:
        return

    timeline_count += 1

    clear_ss()
    bpy.ops.object.select_pattern(pattern = "TimeLine.*.000")
    bpy.ops.object.duplicate(linked = True)

    clear_ss()
    timeline_parent = bpy.data.objects["TimeLine.Parent.001"]
    timeline_parent.name = timeline_parent.name[0:-3] + str(timeline_count)
    timeline_parent.location[0] = timeline_location


def import_timelines(timelines_node):
    print("\nImporting timelines ...")

    global timeline_layer
    global timeline_parent_layer

    bpy.data.scenes[0].layers[timeline_layer] = True
    bpy.data.scenes[0].layers[timeline_parent_layer] = True

    for child_node in timelines_node.childNodes:
        if "TimeGridLine" == child_node.nodeName:
            import_timeline(child_node)

    bpy.data.scenes[0].layers[timeline_parent_layer] = False


def import_node(xml_node):
    if Dom.Node.TEXT_NODE == xml_node.nodeType:
        return
    if "Track" == xml_node.nodeName:
        import_track(xml_node)
    elif "TimeGridLineList" == xml_node.nodeName:
        import_timelines(xml_node)
        return
    else:
        for child_node in xml_node.childNodes:
            import_node(child_node)


def trace_node(xml_node, tabCount = 0):
    if Dom.Node.TEXT_NODE == xml_node.nodeType:
        return
    tabs = ""
    i = 0
    while i < tabCount:
        i += 1
        tabs += "    "
    attribute_string = " "
    i = 0
    attributes = xml_node.attributes
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
    print(tabs + "<" + xml_node.nodeName + attribute_string + ">")
    tabCount += 1
    for xml_node in xml_node.childNodes:
        trace_node(xml_node, tabCount)
    tabCount -= 1


def load(operator,
         context,
         fileName):
    print("\nImporting AudioCarver file ...")
    print(fileName)
    print("... done\n")

    global note_count
    global note_layer

    # Turn on the note layers so the note template objects can be selected.
    bpy.data.scenes[0].layers[0] = True
    bpy.data.scenes[0].layers[1] = True
    bpy.data.scenes[0].layers[note_layer] = True

    # Parse the input file.
    dom = Xml.parse(fileName)
    for xml_node in dom.childNodes:
        import_node(xml_node)

    # Turn the note layers back off
    bpy.data.scenes[0].layers[note_layer] = False
    bpy.data.scenes[0].layers[1] = False
    bpy.data.scenes[0].layers[0] = False

    note_count = 0

    return {'FINISHED'}

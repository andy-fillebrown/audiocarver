
import bpy

import xml.dom as Dom
import xml.dom.minidom as Xml

import time

layer_1_mask = (True, False, False, False, False, False, False, False, False, False,
                False, False, False, False, False, False, False, False, False, False)
layer_2_mask = (False, True, False, False, False, False, False, False, False, False,
                False, False, False, False, False, False, False, False, False, False)
note_template_layer_mask = (False, False, False, False, False, False, False, False, True, False,
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

note_template_objects = None
timeline_template_objects = None


def clear_ss():
    bpy.ops.object.select_all(action = 'DESELECT')


def current_ss():
    return bpy.context.selected_objects


def select_note_template_objects():
    global note_template_objects

    clear_ss()
    for obj in note_template_objects:
        obj.select = True


def select_timeline_template_objects():
    global timeline_template_objects

    clear_ss()
    for obj in timeline_template_objects:
        obj.select = True


def create_note_material(color = "#ffffff"):
    template_material = bpy.data.materials["Note.Material.000"]
    note_material = template_material.copy()
    note_material.diffuse_color[0] = float((16 * int(color[1:2], 16)) + int(color[2:3], 16)) / 255.0
    note_material.diffuse_color[1] = float((16 * int(color[3:4], 16)) + int(color[4:5], 16)) / 255.0
    note_material.diffuse_color[2] = float((16 * int(color[5:6], 16)) + int(color[6:7], 16)) / 255.0
    note_material.specular_color = note_material.diffuse_color
    return note_material


def import_note(note_node, note_material):
    global note_count
    global note_layer
    global note_object_names

    if "Note" != note_node.nodeName:
        print("Xml node is not a note.")
        return

    note_count += 1

    # Select and duplicate the note template objects.
    select_note_template_objects()
    bpy.ops.object.duplicate()

    # Rename the new note objects.
    for note_object_name in note_object_names:
        obj = bpy.data.objects["Template." + note_object_name + '.001']
        new_name = obj.name[9:-3] + str(note_count)
        obj.name = new_name

    # Set the note mesh's material.
    obj = bpy.data.objects["Note.Head.Mesh." + str(note_count)]
    obj.material_slots[0].material = note_material

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
    note_volume_scale_object.scale[0] = velocity
    note_volume_scale_object.scale[1] = velocity
    note_volume_scale_object.scale[2] = velocity


def import_track(track_node):
    # Read the track's attributes.
    color = "#ffffff"
    track_name = ""
    i = 0
    attributes = track_node.attributes
    while i < attributes.length:
        attribute = attributes.item(i)
        if "color" == attribute.name:
            color = attribute.value
        if "name" == attribute.name:
            track_name = attribute.value
        i += 1

    print(" \"" + track_name + "\"")

    # Create the track's note material.
    note_material = create_note_material(color)

    # Read the track's note list.
    for child_node in track_node.childNodes:
        if "NoteList" == child_node.nodeName:
            for note_node in child_node.childNodes:
                if "Note" == note_node.nodeName:
                    import_note(note_node, note_material)


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

    if "" == timeline_label:
        return
    if -1 != timeline_label.find("."):
        return
    if 0.0 == timeline_location:
        return

    timeline_count += 1

    select_timeline_template_objects()
    bpy.ops.object.duplicate(linked = True)

    clear_ss()
    timeline_parent = bpy.data.objects["TimeLine.Parent.001"]
    timeline_parent.name = timeline_parent.name[0:-3] + str(timeline_count)
    timeline_parent.location[0] = timeline_location


def import_timelines(timelines_node):
    global timeline_layer
    global timeline_parent_layer

    print("\nImporting time lines ...")

    bpy.context.scene.layers[timeline_layer] = True
    bpy.context.scene.layers[timeline_parent_layer] = True

    for child_node in timelines_node.childNodes:
        if "TimeGridLine" == child_node.nodeName:
            import_timeline(child_node)

    bpy.context.scene.layers[timeline_parent_layer] = False


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


def load(operator,
         context,
         file_name):
    global layer_1_mask
    global layer_2_mask
    global note_count
    global note_layer
    global note_template_layer_mask
    global note_template_objects
    global timeline_count
    global timeline_template_objects

    print("\nImporting AudioCarver file", file_name, "...")

    start_time = time.time()

    # Store the current selection set so it can be restored later.
    cur_ss = current_ss()

    # Turn on the note layers.
    bpy.context.scene.layers[0] = True
    bpy.context.scene.layers[1] = True
    bpy.context.scene.layers[note_layer] = True

    # Turn on the timeline layers.
    bpy.context.scene.layers[timeline_layer] = True
    bpy.context.scene.layers[timeline_parent_layer] = True

    # Set note template objects list.
    clear_ss()
    bpy.ops.object.select_pattern(pattern = "Template.Note.*.000")
    note_template_objects = current_ss()

    # Set timeline template objects list.
    clear_ss()
    bpy.ops.object.select_pattern(pattern = "TimeLine.*.000")
    timeline_template_objects = current_ss()

    print("\nImporting tracks ...")

    # Parse the input file.
    dom = Xml.parse(file_name)
    for xml_node in dom.childNodes:
        import_node(xml_node)

    # Move the note objects off the note template object layer.
    clear_ss()
    bpy.ops.object.select_by_layer(layers = note_layer + 1)
    bpy.ops.object.move_to_layer(layers = layer_1_mask)
    clear_ss()
    bpy.ops.object.select_pattern(pattern = "Note.Head.Mesh.*")
    bpy.ops.object.move_to_layer(layers = layer_2_mask)
    select_note_template_objects()
    bpy.ops.object.move_to_layer(layers = note_template_layer_mask)

    # Turn off the timeline parent objects layer.
    bpy.context.scene.layers[timeline_parent_layer] = False

    # Turn off the note template layer and note parent objects layer.
    bpy.context.scene.layers[note_layer] = False
    bpy.context.scene.layers[0] = False

    # Restore the original selection set.
    clear_ss()
    for obj in cur_ss:
        obj.select = True

    print("\n... done in %.3f seconds" % (time.time() - start_time))

    note_count = 1
    timeline_count = 1

    return {'FINISHED'}

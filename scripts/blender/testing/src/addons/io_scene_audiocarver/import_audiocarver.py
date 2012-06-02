
import bpy
import xml.dom as Dom
import xml.dom.minidom as Xml
import time

note_suffix_number = 2
note_layer = 18
note_template_object = None
track_count = 1
timeline_count = 0
timeline_layer = 17
timeline_text_layer = 16


def clear_ss():
    bpy.ops.object.select_all(action = 'DESELECT')


def current_ss():
    return bpy.context.selected_objects


def object_number(obj):
    return obj.name[obj.name.rfind(".") + 1 : len(obj.name)]


def to_zero_prefixed_string(number):
    zero_prefixed_string = ""
    if number < 100:
        zero_prefixed_string += "0"
    if number < 10:
        zero_prefixed_string += "0"
    zero_prefixed_string += str(int(number))
    return zero_prefixed_string


def select_note_template_object():
    clear_ss()
    note_template_object.select = True


def create_note_material(color = "#ffffff"):
    template_material = bpy.data.materials["Note.Material.0"]
    note_material = template_material.copy()
    note_material.name = "Note.Material." + str(track_count)
    note_material.diffuse_color[0] = float((16 * int(color[1:2], 16)) + int(color[2:3], 16)) / 255.0
    note_material.diffuse_color[1] = float((16 * int(color[3:4], 16)) + int(color[4:5], 16)) / 255.0
    note_material.diffuse_color[2] = float((16 * int(color[5:6], 16)) + int(color[6:7], 16)) / 255.0
    r_is_zero = 0.0 == note_material.diffuse_color[0]
    g_is_zero = 0.0 == note_material.diffuse_color[1]
    b_is_zero = 0.0 == note_material.diffuse_color[2]
    if r_is_zero:
        if g_is_zero or b_is_zero:
            note_material.diffuse_color[0] = 0.0005
        else:
            note_material.diffuse_color[0] = 0.001
    if g_is_zero:
        if r_is_zero or b_is_zero:
            note_material.diffuse_color[1] = 0.0005
        else:
            note_material.diffuse_color[1] = 0.001
    if b_is_zero:
        if r_is_zero or g_is_zero:
            note_material.diffuse_color[2] = 0.0005
        else:
            note_material.diffuse_color[2] = 0.001
    return note_material


def import_note(note_node, note_material):
    global note_suffix_number

    if "Note" != note_node.nodeName:
        print("Xml node is not a note.")
        return

    # Select and duplicate the note template objects.
    select_note_template_object()
    bpy.ops.object.duplicate()

    # Rename the new note object.
    obj = bpy.data.objects["Note.001"]
    obj.name = obj.name[0 : -3] + to_zero_prefixed_string(note_suffix_number)

    # Set the note mesh materials.
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
    obj.location[0] = first_pt_x
    obj.location[2] = first_pt_y

    # Scale the note duration to the pitch curve's duration.
    obj.scale[0] = last_pt_x - first_pt_x

    # Get the note's velocity/volume.
    velocity = 1.0
    i = 0
    while i < note_node.attributes.length:
        attribute = note_node.attributes.item(i)
        if "volume" == attribute.name:
            velocity = float(attribute.value)
            break;
        i += 1

    # Scale the note vertices y and z coordinates to the volume.
    verts = obj.data.vertices
    i = len(verts) - 1
    while 0 <= i:
        verts[i].co[1] *= velocity
        verts[i].co[2] *= velocity
        i -= 1

    note_suffix_number += 1


def import_track(track_node):
    global track_count

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

    track_count += 1


def import_timeline(timeline_node):
    global timeline_count

    if 0 == timeline_count:
        timeline_count += 1
        return

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
    timeline_count_string = to_zero_prefixed_string(timeline_count + 1)

    # Create the time line.
    clear_ss()
    bpy.data.objects["TimeLine.0"].select = True
    bpy.ops.object.duplicate(linked = True)
    timeline = bpy.data.objects["TimeLine.001"]
    timeline.name = timeline.name[0:-3] + timeline_count_string
    timeline.location[0] = timeline_location

    # Create the time line text.
    clear_ss()
    bpy.data.objects["TimeLine.Text.0"].select = True
    bpy.ops.object.duplicate(linked = False)
    timeline_text = bpy.data.objects["TimeLine.Text.001"]
    timeline_text.name = timeline_text.name[0:-3] + timeline_count_string
    timeline_text.location[0] = timeline_location
    timeline_text.data.body = timeline_label


def import_timelines(timelines_node):
    global timeline_layer

    print("\nImporting time lines ...")

    bpy.context.scene.layers[timeline_layer] = True
    bpy.context.scene.layers[timeline_text_layer] = True

    for child_node in timelines_node.childNodes:
        if "TimeGridLine" == child_node.nodeName:
            import_timeline(child_node)


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
    global note_layer
    global note_template_object
    global track_count

    print("\nImporting AudioCarver file", file_name, "...")

    start_time = time.time()

    # Store the current selection set so it can be restored later.
    cur_ss = current_ss()

    # Turn on the note layers.
    bpy.context.scene.layers[note_layer] = True

    # Set the note template object.
    note_template_object = bpy.data.objects["Note.0"]

    print("\nImporting tracks ...")
    track_count = 1

    # Parse the input file.
    dom = Xml.parse(file_name)
    for xml_node in dom.childNodes:
        import_node(xml_node)

    # Delete the note template objects.
    select_note_template_object()
    bpy.ops.object.delete()

    # Restore the original selection set.
    clear_ss()
    for obj in cur_ss:
        obj.select = True

    print("\n... done in %.3f seconds\n" % (time.time() - start_time))

    return {'FINISHED'}


def note_string(note_number):
    mod = int(note_number) % 12
    if 0 == mod:
        return "C"
    if 2 == mod:
        return "D"
    if 4 == mod:
        return "E"
    if 5 == mod:
        return "F"
    if 7 == mod:
        return "G"
    if 9 == mod:
        return "A"
    if 11 == mod:
        return "B"
    return ""


def create_pitch_lines():
    # Calculate note pitch range.
    pitch_min = 128
    pitch_max = -1
    bpy.ops.object.select_pattern(pattern = "Note.*", extend = False)
    notes = current_ss()
    for note in notes:
        y = note.location[2]
        if y < pitch_min:
            pitch_min = y
        if pitch_max < y:
            pitch_max = y

    # Create pitch line text objects for each note in the note pitch range.
    i = pitch_min
    while i <= pitch_max:
        i_string = str(int(i))
        text_string = note_string(i)
        has_text = "" != text_string

        # Duplicate pitch line text template objects.
        clear_ss()
        bpy.data.objects[".PitchLine.Text.Locator"].select = True
        bpy.data.objects["PitchLine.Text.Arrow.0"].select = True
        if has_text:
            bpy.data.objects["PitchLine.Text.0"].select = True
        bpy.ops.object.duplicate()

        # Setup pitch line text locator.
        clear_ss()
        obj = bpy.data.objects[".PitchLine.Text.Locator.001"]
        obj.location[2] = i
        obj.select = True
        bpy.context.scene.objects.active = obj
        bpy.ops.object.parent_clear(type = 'CLEAR_KEEP_TRANSFORM')
        bpy.ops.object.transform_apply(location = True, scale = True)
        bpy.ops.object.modifier_apply(modifier = "Curve")
        location = obj.data.vertices[0].co

        # Setup pitch line text arrow.
        obj = bpy.data.objects["PitchLine.Text.Arrow.001"]
        obj.location[2] = i
        obj.name = "PitchLine.Text.Arrow." + i_string

        if has_text:
            # Setup pitch line text.
            obj = bpy.data.objects["PitchLine.Text.001"]
            obj.location = location
            obj.data.body = note_string(i)
            obj.name = "PitchLine.Text." + i_string

            # Center pitch line text.
            bbox = obj.bound_box
            x_offset = bbox[0][1] + ((bbox[2][1] - bbox[0][1]) / 2.0)
            y_offset = bbox[0][0] + (bbox[4][0] - bbox[0][0])
            obj.location[1] += y_offset
            obj.location[2] -= x_offset

        # Delete pitch line text locator.
        clear_ss()
        bpy.data.objects[".PitchLine.Text.Locator.001"].select = True
        bpy.ops.object.delete()

        i += 1

    # Delete pitch line text template objects.
    clear_ss()
    bpy.data.objects[".PitchLine.Text.Locator"].select = True
    bpy.data.objects["PitchLine.Text.0"].select = True
    bpy.data.objects["PitchLine.Text.Arrow.0"].select = True
    bpy.ops.object.delete()


def apply_note_modifiers(note):
    # Apply modifiers.
    note.select = True
    bpy.context.scene.objects.active = note
    bpy.ops.object.modifier_apply(modifier = note.modifiers[0].name)


def prepare_for_render():
    prev_active_obj = bpy.context.scene.objects.active
    prev_ss = current_ss()

    start_time = time.time()

    print ("Preparing scene for render ...")

    print(" creating pitch lines ...")
    create_pitch_lines()

    # Apply note modifiers.
    print(" applying note modifiers ...")
    clear_ss()
    bpy.ops.object.select_pattern(pattern = "Note.*")
    notes = current_ss()
    for note in notes:
        apply_note_modifiers(note)

    # Delete pitch line location curve.
    print(" deleting the pitch location curve ...")
    clear_ss()
    bpy.data.objects[".Pitch.Location.Curve.Y"].select
    bpy.ops.object.delete()

    # Restore previous selection.
    clear_ss()
    bpy.context.scene.objects.active = prev_active_obj
    for obj in prev_ss:
        obj.select = True

    print("\n... done in %.3f seconds\n" % (time.time() - start_time))


class AudioCarverPrepareForRender(bpy.types.Operator):
    '''Prepare the AudioCarver scene for render.'''
    bl_idname = "object.prepare_for_render"
    bl_label = "AudioCarver Prepare for Render"

    @classmethod
    def poll(cls, context):
        return True;

    def execute(self, context):
        prepare_for_render()
        return {'FINISHED'}

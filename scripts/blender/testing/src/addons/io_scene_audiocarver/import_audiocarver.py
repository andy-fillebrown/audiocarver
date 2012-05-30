
import bpy

import xml.dom as Dom
import xml.dom.minidom as Xml

import time

note_count = 1
note_layer = 18
note_parent_layer = 8
note_object_names = {"Note.Start",
                     "Note.Duration",
                     "Note.End",
                     "Note.Velocity",
                     "Note.Head",
                     "Note.Body",
                     "Note.Tail"}
note_template_objects = []
track_count = 1
timeline_count = 0
timeline_layer = 17
timeline_text_layer = 16
min_velocity = 0.01


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


def select_note_template_objects():
    global note_template_objects

    clear_ss()
    for obj in note_template_objects:
        obj.select = True


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
    global note_count

    if "Note" != note_node.nodeName:
        print("Xml node is not a note.")
        return

    note_name_suffix = to_zero_prefixed_string(note_count)

    # Select and duplicate the note template objects.
    select_note_template_objects()
    bpy.ops.object.duplicate()

    # Rename the new note objects.
    for note_object_name in note_object_names:
        obj = bpy.data.objects[note_object_name + ".001"]
        new_name = obj.name[0 : -3] + note_name_suffix
        obj.name = new_name

    # Get the note head, body, and tail mesh objects.
    head_obj = bpy.data.objects["Note.Head." + note_name_suffix]
    body_obj = bpy.data.objects["Note.Body." + note_name_suffix]
    tail_obj = bpy.data.objects["Note.Tail." + note_name_suffix]

    # Set the note mesh materials.
    head_obj.material_slots[0].material = note_material
    body_obj.material_slots[0].material = note_material
    tail_obj.material_slots[0].material = note_material

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
    note_root_object = bpy.data.objects["Note.Start." + note_name_suffix]
    note_root_object.location[0] = first_pt_x
    note_root_object.location[2] = first_pt_y

    # Scale the note duration object to the pitch curve length
    note_tail_scale_object = bpy.data.objects["Note.Duration." + note_name_suffix]
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
    note_volume_scale_object = bpy.data.objects["Note.Velocity." + note_name_suffix]
    note_volume_scale_object.scale[0] = velocity
    note_volume_scale_object.scale[1] = velocity
    note_volume_scale_object.scale[2] = velocity

    note_count += 1


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
    global layer_1_mask
    global layer_2_mask
    global note_layer
    global note_parent_layer
    global note_object_names
    global note_template_layer_mask
    global note_template_objects
    global track_count

    print("\nImporting AudioCarver file", file_name, "...")

    start_time = time.time()

    # Store the current selection set so it can be restored later.
    cur_ss = current_ss()

    # Turn on the note layers.
    bpy.context.scene.layers[note_layer] = True
    bpy.context.scene.layers[note_parent_layer] = True

    # Set the note template objects list.
    for note_object_name in note_object_names:
        note_template_objects.append(bpy.data.objects[note_object_name + ".0"])

    print("\nImporting tracks ...")
    track_count = 1

    # Parse the input file.
    dom = Xml.parse(file_name)
    for xml_node in dom.childNodes:
        import_node(xml_node)

    # Delete the note template objects.
    select_note_template_objects()
    bpy.ops.object.delete()

    # Restore the original selection set.
    clear_ss()
    for obj in cur_ss:
        obj.select = True

    print("\n... done in %.3f seconds" % (time.time() - start_time))

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


def prepare_for_render():
    # Turn on the note parent layer.
    bpy.context.scene.layers[note_parent_layer] = True

    # Calculate note pitch range.
    pitch_min = 128
    pitch_max = -1
    bpy.ops.object.select_pattern(pattern = "Note.Start.*", extend = False)
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


def simplify_scene():
    global min_velocity
    global pitchline_layer
    global pitchline_parent_layer
    global timeline_layer
    global timeline_parent_layer

    print("\nSimplifying scene for render ...")

    # Apply boolean modifier for note head and tail meshes.
    bpy.context.scene.layers[1] = True
    clear_ss()
    bpy.ops.object.select_by_layer(layers = 2)
    ss = current_ss()
    clear_ss()
    for obj in ss:
        bpy.context.scene.objects.active = obj
        bpy.ops.object.modifier_apply(modifier = "Boolean")

    # Delete unused pitch lines.
    bpy.context.scene.layers[pitchline_parent_layer] = True
    bpy.context.scene.layers[pitchline_layer] = True
    used_pitches = []
    for obj in ss:
        pitch = obj.parent.location[2]
        if 0 == used_pitches.count(pitch):
            used_pitches.append(pitch)
    clear_ss()
    i = 0
    while i < 128:
        if 0 == used_pitches.count(i):
            n = to_zero_prefixed_string(i)
            bpy.data.objects["PitchLine.Object." + n].select = True
            bpy.data.objects["PitchLine.Parent." + n].select = True
        i += 1
    bpy.ops.object.delete()
    bpy.context.scene.layers[pitchline_parent_layer] = False

    # Turn on the note helper objects layer.
    bpy.context.scene.layers[0] = True

    # Delete note tail scale objects and meshes.
    clear_ss()
    bpy.ops.object.select_pattern(pattern = "Note.Tail.*")
    bpy.ops.object.delete()

    # Apply velocity scales to note meshes.
    for obj in ss:
        constraint = obj.constraints["Copy Scale"]
        velocity_obj = constraint.target
        obj.scale = velocity_obj.scale
        obj.constraints.clear()
        if obj.scale[0] < min_velocity:
            obj.scale[0] = min_velocity
        if obj.scale[1] < min_velocity:
            obj.scale[1] = min_velocity
        if obj.scale[2] < min_velocity:
            obj.scale[2] = min_velocity

    # Delete velocity scale objects.
    clear_ss()
    bpy.ops.object.select_pattern(pattern = "Note.Velocity.Scale.Y.*")
    bpy.ops.object.delete()

    # Reparent note meshes from their note root object to the track root object.
    clear_ss()
    for obj in ss:
        obj.select = True
    bpy.ops.object.parent_clear(type = 'CLEAR_KEEP_TRANSFORM')
    bpy.context.scene.objects.active = bpy.data.objects["Track.Root.Empty"]
    bpy.ops.object.parent_set()

    # Delete the note root objects.
    clear_ss()
    bpy.ops.object.select_pattern(pattern = "Note.Root.Empty.*")
    bpy.ops.object.delete()

    # Turn off the note helper objects layer.
    bpy.context.scene.layers[0] = False

    # Join note meshes that use the same matrial.
    materials = []
    for material in bpy.data.materials:
        if material.name.startswith("Note.Material."):
            materials.append(material)
    for material in materials:
        clear_ss()
        obj_selected = False
        for obj in ss:
            if material == obj.active_material:
                obj.select = True
                obj_selected = True
        if obj_selected:
            cur_ss = current_ss()
            bpy.context.scene.objects.active = cur_ss[0]
            bpy.ops.object.join()
            bpy.ops.object.select_by_layer(layers = 2)
            ss = current_ss()
    clear_ss()

    # Turn on the time line parent objects layer.
    bpy.context.scene.layers[timeline_layer - 1] = True

    # Reparent time lines from their time line parent to the track root object.
    clear_ss()
    bpy.ops.object.select_pattern(pattern = "TimeLine.Object.*")
    ss = current_ss()
    for obj in ss:
        obj.parent.modifiers.clear()
    bpy.ops.object.parent_clear(type = 'CLEAR_KEEP_TRANSFORM')
    for obj in ss:
        obj.constraints.clear()
    bpy.context.scene.objects.active = bpy.data.objects["Track.Root.Empty"]
    bpy.ops.object.parent_set()

    # Add curve modifier to time line objects.
    for obj in ss:
        bpy.context.scene.objects.active = obj
        bpy.ops.object.modifier_add(type = 'CURVE')
        curve_modifier = obj.modifiers[0]
        curve_modifier.object = bpy.data.objects["Curve.X"]

    # Delete time line parent objects.
    bpy.context.scene.layers[timeline_parent_layer - 1] = True
    clear_ss()
    bpy.ops.object.select_pattern(pattern = "TimeLine.Parent.*")
    bpy.ops.object.delete()

    # Remove top and bottom pitch line object parents and constraints.
    clear_ss()
    bpy.ops.object.select_pattern(pattern = "PitchLine.Object.*")
    bpy.ops.object.parent_clear(type = 'CLEAR_KEEP_TRANSFORM')
    ss = current_ss()
    for obj in ss:
        obj.constraints.clear()

    # Delete pitch line parent objects.
    clear_ss()
    bpy.ops.object.select_pattern(pattern = "PitchLine.Parent.*")
    bpy.ops.object.delete()


class AudioCarverSimplifyScene(bpy.types.Operator):
    '''Simplify the AudioCarver scene for effecient rendering.'''
    bl_idname = "object.simplify_scene"
    bl_label = "AudioCarver Simplify Scene"

    @classmethod
    def poll(cls, context):
        return True;

    def execute(self, context):
        simplify_scene()
        return {'FINISHED'}

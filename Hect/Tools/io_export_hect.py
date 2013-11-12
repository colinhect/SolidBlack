#!BPY

bl_info = {
    "name": "Hect Mesh Format (.mesh)",
    "author": "Colin Hill",
    "version": (1, 0),
    "blender": (2, 5, 9),
    "api": 37702,
    "location": "File > Export > Hect (.mesh)",
    "description": "Export Hect Mesh Format (.mesh)",
    "warning": "",
    "wiki_url": "",
    "tracker_url": "",
    "category": "Import-Export"}

import os
import bpy

from bpy.props import StringProperty, EnumProperty, BoolProperty

class HectExporter(bpy.types.Operator):
    """Export to the Hect mesh format (.mesh)"""

    bl_idname = "export.hect"
    bl_label = "Export Hect"

    filepath = StringProperty(subtype='FILE_PATH')

    def execute(self, context):
        path = bpy.path.ensure_ext(self.filepath, ".mesh")
        out = open(path, 'w')
        out.write("{\n")
        out.write("    \"vertices\" :\n")
        out.write("    [\n")

        scene = bpy.context.scene

        for obj in bpy.context.selected_objects:
            if obj.type == 'MESH':
                mesh = obj.data
                if not mesh.tessfaces and mesh.polygons:
                    mesh.calc_tessface()
                for vertex in mesh.vertices:
                    out.write("        { \"semantic\" : \"Position\", \"data\" : [ %f, %f, %f ]\n" % (vertex.co[0], vertex.co[1], vertex.co[2]))
        out.write("    ]\n")
        out.write("}")
        out.close()
        return {"FINISHED"}

    def invoke(self, context, event):
        if not self.filepath:
            self.filepath = bpy.path.ensure_ext(bpy.data.filepath, ".mesh")
        WindowManager = context.window_manager
        WindowManager.fileselect_add(self)
        return {"RUNNING_MODAL"}

def menu_func(self, context):
    self.layout.operator(HectExporter.bl_idname, text="Hect (.mesh)")

def register():
    bpy.utils.register_module(__name__)
    bpy.types.INFO_MT_file_export.append(menu_func)

def unregister():
    bpy.utils.unregister_module(__name__)
    bpy.types.INFO_MT_file_export.remove(menu_func)

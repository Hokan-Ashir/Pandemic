/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'MeshGroup' to store a group of 'Mesh' objects.

/******************************************************************************/
struct MeshGroup // Mesh Group (array of Meshes)
{
   Box        box   ; // bounding box
   Mems<Mesh> meshes; // meshes

   // manage
   MeshGroup& del   (                                  ); // delete
   MeshGroup& create(C MeshGroup &src, UInt flag_and=~0); // create from 'src', 'flag_and'=MESH_BASE_FLAG

   MeshGroup& exclude (UInt flag); // exclude   elements specified with 'flag' MESH_BASE_FLAG
   MeshGroup& keepOnly(UInt flag); // keep only elements specified with 'flag' MESH_BASE_FLAG

   // get
   Bool is       ()C {return meshes.elms()>0;} // if has any meshes
   UInt flag     ()C; // get MESH_BASE_FLAG
   Int  vtxs     ()C; // get total number of vertexes
   Int  edges    ()C; // get total number of edges
   Int  tris     ()C; // get total number of triangles
   Int  quads    ()C; // get total number of quads
   Int  faces    ()C; // get total number of faces                    , faces    =(triangles + quads  )
   Int  trisTotal()C; // get total number of triangles including quads, trisTotal=(triangles + quads*2)

   // join
   MeshGroup& join   (Int i0, Int i1                                                               ); // join i0-th and i1-th Mesh together
   MeshGroup& joinAll(Bool test_material, Bool test_draw_group, Bool test_name, Bool weld_vtxs=true); // join all MeshPart's, 'test_material'=join only those MeshPart's which have the same material, 'test_draw_group'=join only those MeshPart's which have the same draw group, 'test_name'=join only those MeshPart's which have the same name, 'weld_vtxs'=if automatically weld vertexes after joining, this does not join 'meshes' together, this only joins MeshPart's within the 'meshes'

   // transform
   MeshGroup& move     (              C Vec &move); //           move MeshGroup
   MeshGroup& scale    (C Vec &scale             ); // scale          MeshGroup
   MeshGroup& scaleMove(C Vec &scale, C Vec &move); // scale and move MeshGroup

   // texture transform
   MeshGroup& texMove  (C Vec2 &move , Byte tex_index=0); // move   texture uv's
   MeshGroup& texScale (C Vec2 &scale, Byte tex_index=0); // scale  texture uv's
   MeshGroup& texRotate(  Flt   angle, Byte tex_index=0); // rotate texture uv's

   // set
   MeshGroup& delBase   (                                                ); // delete all software meshes (MeshBase  ) in this mesh
   MeshGroup& delRender (                                                ); // delete all hardware meshes (MeshRender) in this mesh
   MeshGroup& setRender (                                                ); // set rendering version, convert all MeshBase's to MeshRender's
   MeshGroup& setVtxDup (UInt flag=0, Flt pos_eps=EPS, Flt nrm_cos=0.999f); // set vertex duplicates (vtx.dup)
   MeshGroup& setNormals(Bool by_face_area=true                          ); // recalculate vertex 3D normals, 'by_face_area'=if use weight according to face surface area - default, (if false then face angle is used)
   MeshGroup& setShader (                                                ); // reset shader
   MeshGroup& material  (C MaterialPtr &material                         ); // set material, 'material' must point to object in constant memory address (mesh will store only the pointer to the material and later use it if needed)
   Bool       setBox    (Bool           set_mesh_boxes                   ); // recalculate bounding box

   // operations
   MeshGroup& weldVtx      (UInt flag=0, Flt pos_eps=EPS, Flt nrm_cos=0.999f, Bool remove_degenerate_faces=true); // weld 3D vertexes     , this function will weld vertexes together if they share the same position             , 'flag'=if selected elements aren't equal then don't weld (MESH_BASE_FLAG), 'remove_degenerate_faces'=if automatically remove degenerate faces which may occur after welding vertexes
   MeshGroup& weldVtxValues(UInt flag  , Flt pos_eps=EPS, Flt nrm_cos=0.999f, Bool remove_degenerate_faces=true); // weld    vertex values, this function will weld values of vertexes which  share the same position             , 'flag'=                                 elements to weld (MESH_BASE_FLAG), 'remove_degenerate_faces'=if automatically remove degenerate faces which may occur after welding vertexes

   MeshGroup& freeOpenGLESData(); // this method is used only under OpenGL ES (on other platforms it is ignored), the method frees the software copy of the GPU data which increases available memory, however after calling this method the data can no longer be accessed on the CPU (can no longer be locked or saved to file)

   // convert
   MeshGroup& triToQuad      (Flt cos=0.999f); // triangles to quads    , 'cos'=minimum cosine between 2      triangle normals to weld  them into 1 quad (0..1)
   MeshGroup& quadToTri      (Flt cos=2     ); // quads     to triangles, 'cos'=minimum cosine between 2 quad triangle normals to leave them as   1 quad (0..1, value >1 converts all quads into triangles)
   MeshGroup& toStencilShadow(              ); // convert   to stencil shadow mesh, mesh must be closed (have no holes) and can't be infinite

   // add / remove
   MeshGroup& remove(Int i, Bool set_box=true); // remove i-th mesh, 'set_box'=if recalculate bounding box

   // optimize
   MeshGroup& removeDegenerateFaces();

   MeshGroup& simplify(Flt intensity, Flt max_distance=1.0f, Flt max_uv=1.0f, Flt max_color=0.03f, Flt max_material=0.08f, Flt max_normal=PI, Bool keep_border=false, Flt border_priority=0.0f, MESH_SIMPLIFY mode=SIMPLIFY_DENSITY, MeshGroup *dest=NULL); // simplify mesh by removing vertexes/faces, 'intensity'=how much to simplify (0..1, 0=no simplification, 1=full simplification), 'max_distance'=max distance between elements to merge them (0..Inf), 'max_uv'=max allowed vertex texture UV deviations (0..1), 'max_color'=max allowed vertex color deviations (0..1), 'max_material'=max allowed vertex material deviations (0..1), 'max_normal'=max allowed vertex normal angle deviations (0..PI), 'keep_border'=if always keep border edges (edges that have faces only on one side), 'border_priority'=priority of border faces (-Inf..Inf, <0 decreases priority and makes border edges more likely to be removed, >0 increases priority and makes border edges less likely to be removed), 'dest'=destination MeshBase (if set to NULL then the mesh will simplify itself), returns dest

   // draw
      // default drawing, automatically uses Frustum Culling, this doesn't draw the mesh immediately, instead it adds the mesh to a draw list
      void draw(C Matrix &matrix, C Vec &vel=VecZero, C Vec &ang_vel=VecZero, Bool use_early_z=false)C; // add mesh to draw list using 'matrix' matrix, 'vel' velocity and 'ang_vel' angular velocity, this should be called only in RM_PREPARE, when used it will automatically draw meshes in following modes when needed: RM_EARLY_Z RM_SIMPLE RM_SOLID RM_SOLID_M RM_AMBIENT RM_BLEND

      void drawShadow(C Matrix &matrix)C; // add mesh to shadow draw list using 'matrix' matrix, this should be called only in RM_SHADOW

      // drawing as stencil shadow, automatically uses Frustum culling, this can be called only in RM_STENCIL_SHADOW
      void drawStencilShadow(                )C; // draw with  current matrix
      void drawStencilShadow(C Matrix &matrix)C; // draw with 'matrix' matrix

   // io
   void operator=(C Str &name) ; // load, Exit  on fail
   Bool save     (C Str &name)C; // save, false on fail
   Bool load     (C Str &name) ; // load, false on fail

   void save   (File &f, CChar *path=NULL)C; // save, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path)
   Bool load   (File &f, CChar *path=NULL) ; // load, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail
   Bool loadAdd(File &f, CChar *path=NULL) ; // load, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail, this method adds the data from file to self (not replaces it)

   MeshGroup();
};
/******************************************************************************/
inline Int Elms(C MeshGroup &mshg) {return mshg.meshes.elms();}
/******************************************************************************/

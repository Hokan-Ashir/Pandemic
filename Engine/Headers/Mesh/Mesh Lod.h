/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   'MeshLod' represents a single level of detail, by containing an array of 'MeshPart's.

/******************************************************************************/
struct MeshLod // Level of Detail, array of Mesh Part's
{
   Flt            dist2; // squared distance at which this level of detail should be rendered
   Mems<MeshPart> parts; // mesh parts

   // manage
   MeshLod& del   (                                ); // delete
   MeshLod& create(  Int      num                  ); // create with 'num' empty MeshPart's
   MeshLod& create(C MeshLod &src, UInt flag_and=~0); // create from 'src', 'flag_and'=MESH_BASE_FLAG

   MeshLod& exclude (UInt flag); // exclude   elements specified with 'flag' MESH_BASE_FLAG
   MeshLod& keepOnly(UInt flag); // keep only elements specified with 'flag' MESH_BASE_FLAG

   // get
   Bool is       (                )C {return parts.elms()>0;} // if has any parts
   UInt flag     (                )C;                         // get MESH_BASE_FLAG
   UInt memUsage (                )C;                         // get memory usage
   Int  vtxs     (                )C;                         // get total number of vertexes
   Int  edges    (                )C;                         // get total number of edges
   Int  tris     (                )C;                         // get total number of triangles
   Int  quads    (                )C;                         // get total number of quads
   Int  faces    (                )C;                         // get total number of faces                    , faces    =(triangles + quads  )
   Int  trisTotal(                )C;                         // get total number of triangles including quads, trisTotal=(triangles + quads*2)
   Bool getBox   (Box &box        )C;                         // get box   encapsulating the MeshLod, false on fail (if no vertexes are present)
   Flt  area     (Vec *center=NULL)C;                         // get surface area of all mesh faces, 'center'=if specified then it will be calculated as the average surface center

   // set
   MeshLod& setNormals   (Bool by_face_area=true); // recalculate vertex 3D normals, 'by_face_area'=if use weight according to face surface area - default, (if false then face angle is used)
   MeshLod& setTangents  (                      ); // recalculate vertex 3D tangents
   MeshLod& setBinormals (                      ); // recalculate vertex 3D binormals
   MeshLod& setAutoTanBin(                      ); // automatically calculate vertex tangents and binormals if needed, if they're not needed then they will be removed

   MeshLod& setVtxDup                             (UInt flag=0, Flt pos_eps=EPS, Flt nrm_cos=0.999f); // set vertex 3D duplicates (vtx.dup)
   MeshLod& setVtxColorAlphaAsTesselationIntensity(Bool tesselate_edges                            ); // set vertex color alpha   (vtx.color.a) as tesselation intensity, 'tesselate_edges'=if tesselate non continuous edges
   MeshLod& setAdjacencies                        (                                                ); // set all adjacencies      (edge.adj_face, tri.adj_edge, tri.adj_face, quad.adj_edge, quad.adj_face)

   MeshLod& delBase  (                                      ); // delete all software meshes (MeshBase  ) in this mesh
   MeshLod& delRender(                                      ); // delete all hardware meshes (MeshRender) in this mesh
   MeshLod& setBase  (Bool only_if_empty=true               ); // set software  version, convert 'MeshRender' to 'MeshBase', 'only_if_empty'=perform conversion only if the MeshBase is empty (if set to false then conversion is always performed)
   MeshLod& setRender(Bool optimize     =true               ); // set rendering version, convert 'MeshBase'   to 'MeshRender', 'optimize'=if optimize the mesh by re-ordering the vertexes/triangles for optimal processing on the GPU
   MeshLod& setShader(                         Int lod_index); // reset shader, 'lod_index'=index of the lod in the mesh (required in order to set appropriate quality of the shader)
   MeshLod& material (C MaterialPtr &material, Int lod_index); // set material, 'lod_index'=index of the lod in the mesh (required in order to set appropriate quality of the shader), 'material' must point to object in constant memory address (mesh will store only the pointer to the material and later use it if needed)

   // transform
   MeshLod& move     (                  C Vec &move); //           move MeshLod
   MeshLod& scale    (C Vec     &scale             ); // scale          MeshLod
   MeshLod& scaleMove(C Vec     &scale, C Vec &move); // scale and move MeshLod
   MeshLod& transform(C Matrix3 &matrix            ); // transform by matrix
   MeshLod& transform(C Matrix  &matrix            ); // transform by matrix
   MeshLod& mirrorX  (                             ); // mirror in X axis
   MeshLod& mirrorY  (                             ); // mirror in Y axis
   MeshLod& mirrorZ  (                             ); // mirror in Z axis
   MeshLod& reverse  (                             ); // reverse faces

   // texture transform
   MeshLod& texMove  (C Vec2 &move , Byte tex_index=0); // move   texture uv's
   MeshLod& texScale (C Vec2 &scale, Byte tex_index=0); // scale  texture uv's
   MeshLod& texRotate(  Flt   angle, Byte tex_index=0); // rotate texture uv's

   // join / split
   MeshLod& join   (Int i0, Int i1                                          , Bool weld_vtxs=true); // join i0-th and i1-th parts together, 'weld_vtxs'=if automatically weld vertexes after joining
   MeshLod& joinAll(Bool test_material, Bool test_draw_group, Bool test_name, Bool weld_vtxs=true); // join all parts, 'test_material'=join only those MeshPart's which have the same material, 'test_draw_group'=join only those MeshPart's which have the same draw group, 'test_name'=join only those MeshPart's which have the same name, 'weld_vtxs'=if automatically weld vertexes after joining

   MeshPart* splitVtxs (Int i, C Memp<Int> &vtxs                                        ); // split i-th part by given array of vertexes to a new MeshPart, pointer to that MeshPart is returned or NULL if it wasn't created
   MeshPart* splitFaces(Int i, C Memp<Int> &faces                                       ); // split i-th part by given array of faces    to a new MeshPart, pointer to that MeshPart is returned or NULL if it wasn't created, here 'faces' indexes can point to both triangles and quads, if face is a triangle then "face=triangle_index", if face is a quad then "face=quad_index^SIGN_BIT"
   MeshPart* splitFaces(Int i, C Memp<Int> &edges, C Memp<Int> &tris, C Memp<Int> &quads); // split i-th part by given array of faces    to a new MeshPart, pointer to that MeshPart is returned or NULL if it wasn't created

   // operations
   MeshLod& weldVtx      (UInt flag=0, Flt pos_eps=EPS, Flt nrm_cos=0.999f, Bool remove_degenerate_faces=true); // weld 3D vertexes     , this function will weld vertexes together if they share the same position             , 'flag'=if selected elements aren't equal then don't weld (MESH_BASE_FLAG), 'remove_degenerate_faces'=if automatically remove degenerate faces which may occur after welding vertexes
   MeshLod& weldVtxValues(UInt flag  , Flt pos_eps=EPS, Flt nrm_cos=0.999f, Bool remove_degenerate_faces=true); // weld    vertex values, this function will weld values of vertexes which  share the same position             , 'flag'=                                 elements to weld (MESH_BASE_FLAG), 'remove_degenerate_faces'=if automatically remove degenerate faces which may occur after welding vertexes

   MeshLod& boneRemap(C Memp<Byte> &old_to_new); // remap vertex bone/matrix indexes according to bone 'old_to_new' remap

   MeshLod& freeOpenGLESData(); // this method is used only under OpenGL ES (on other platforms it is ignored), the method frees the software copy of the GPU data which increases available memory, however after calling this method the data can no longer be accessed on the CPU (can no longer be locked or saved to file)

   // fix
   MeshLod& fixTexOffset  (Byte tex_index=0); // fix texture offset , this reduces big texture coordinates to small ones increasing texturing quality on low precision video cards
   MeshLod& fixTexWrapping(Byte tex_index=0); // fix texture wraping, fixes texture coordinates created by spherical/tube mapping (this can add new vertexes to the mesh)

   // convert
   MeshLod& edgeToDepth    (Bool tex_align =true  ); // edges to depth (extrude 2D edges to 3D faces)
   MeshLod& edgeToTri      (Bool set_id    =false ); // edges to triangles (triangulation)
   MeshLod& triToQuad      (Flt  cos       =0.999f); // triangles to quads    , 'cos'=minimum cosine between 2      triangle normals to weld  them into 1 quad (0..1)
   MeshLod& quadToTri      (Flt  cos       =2     ); // quads     to triangles, 'cos'=minimum cosine between 2 quad triangle normals to leave them as   1 quad (0..1, value >1 converts all quads into triangles)
   MeshLod& toStencilShadow(Bool join_parts=true  ); // convert   to stencil shadow mesh, mesh must be closed (have no holes) and can't be infinite, 'join_parts'=if automatically join MeshPart's (uses 'join()' for skinned and 'join(MESH_JOIN_NAME)' for non skinned mesh)

   // add / remove
   MeshLod& add(C MeshBase &src); // add MeshBase to self
   MeshLod& add(C MeshPart &src); // add MeshPart to self
   MeshLod& add(C MeshLod  &src); // add Mesh     to self

   // optimize
   MeshLod& removeDegenerateFaces();
   MeshLod& removeUnusedVtxs     (Bool include_edge_references=true); // remove vertexes which aren't used by any face or edge, if 'include_edge_references' is set to false then only face references are tested (without the edges)

   MeshLod& simplify(Flt intensity, Flt max_distance=1.0f, Flt max_uv=1.0f, Flt max_color=0.03f, Flt max_material=0.08f, Flt max_normal=PI, Bool keep_border=false, Flt border_priority=0.0f, MESH_SIMPLIFY mode=SIMPLIFY_DENSITY, MeshLod *dest=NULL); // simplify mesh by removing vertexes/faces, 'intensity'=how much to simplify (0..1, 0=no simplification, 1=full simplification), 'max_distance'=max distance between elements to merge them (0..Inf), 'max_uv'=max allowed vertex texture UV deviations (0..1), 'max_color'=max allowed vertex color deviations (0..1), 'max_material'=max allowed vertex material deviations (0..1), 'max_normal'=max allowed vertex normal angle deviations (0..PI), 'keep_border'=if always keep border edges (edges that have faces only on one side), 'border_priority'=priority of border faces (-Inf..Inf, <0 decreases priority and makes border edges more likely to be removed, >0 increases priority and makes border edges less likely to be removed), 'dest'=destination MeshBase (if set to NULL then the mesh will simplify itself), returns dest

   // draw
      // default drawing, doesn't use automatic Frustum Culling, this doesn't draw the mesh immediately, instead it adds the mesh to a draw list
      void draw(C Matrix           &matrix, C Vec &vel=VecZero, C Vec &ang_vel=VecZero, Bool use_early_z=false)C; // add mesh to draw list using 'matrix'    matrix, 'vel' velocity and 'ang_vel' angular velocity, this should be called only in RM_PREPARE, when used it will automatically draw meshes in following modes when needed: RM_EARLY_Z RM_SIMPLE RM_SOLID RM_SOLID_M RM_AMBIENT RM_BLEND
      void draw(C AnimatedSkeleton &anim_skel                                                                 )C; // add mesh to draw list using 'anim_skel' matrixes and  velocities                             , this should be called only in RM_PREPARE, when used it will automatically draw meshes in following modes when needed: RM_EARLY_Z RM_SIMPLE RM_SOLID RM_SOLID_M RM_AMBIENT RM_BLEND, 'anim_skel' must point to constant memory address (the pointer is stored through which the object can be accessed later during frame rendering)

      void drawShadow(C Matrix           &matrix   )C; // add mesh to shadow draw list using 'matrix'    matrix  , this should be called only in RM_SHADOW
      void drawShadow(C AnimatedSkeleton &anim_skel)C; // add mesh to shadow draw list using 'anim_skel' skeleton, this should be called only in RM_SHADOW, 'anim_skel' must point to constant memory address (the pointer is stored through which the object can be accessed later during frame rendering)

      // draw blended, this is an alternative to default 'draw' (typically 'draw' draws blended meshes automatically for materials with technique in blend mode), this method however draws the mesh immediately (which allows to set custom shader parameters per draw call), it always uses blend shaders regardless if the material has technique set in blend mode, and provides additional control over material color, this can be called only in RM_BLEND rendering mode, doesn't use automatic Frustum culling
      void drawBlend(C Vec4 *color=NULL)C; // draw with current matrix, 'color'=pointer to optional Material color multiplication

      // draw mesh outline, this can be optionally called in RM_OUTLINE in order to outline the mesh, doesn't use automatic Frustum culling
      void drawOutline(C Color &color)C; // draw with current matrix

      // draw using the "behind" effect, this can be optionally called in RM_BEHIND, doesn't use automatic Frustum culling
      void drawBehind(C Color &color_perp, C Color &color_parallel)C; // draw with current matrix, 'color_perp'=color to be used for normals perpendicular to camera, 'color_parallel'=color to be used for normals parallel to camera

   void operator*=(C Matrix3 &m) {transform(m);} // transform by matrix
   void operator*=(C Matrix  &m) {transform(m);} // transform by matrix

   MeshLod();
};
/******************************************************************************/
inline Int Elms(C MeshLod &mshl) {return mshl.parts.elms();}
/******************************************************************************/

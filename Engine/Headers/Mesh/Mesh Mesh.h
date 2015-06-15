/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   'Mesh' is a typical object mesh,
      it is an array of multiple level of details - 'MeshLods',
      it has a one bounding box.

   Every 'Mesh' object can be linked with custom 'Skeleton' file.
      Once a Mesh is being loaded, it automatically loads the linked Skeleton file,
      and adjusts vertex bone indexes to match the Skeleton bone indexes order (this is done according to bone names),
      making it possible to draw the mesh with Skeleton based matrixes.

   Use 'Meshes' cache for easy mesh accessing from files.

/******************************************************************************/
STRUCT(Mesh , MeshLod) // Mesh (array of Mesh Lod's)
//{
   Box box       ; // bounding box
   Vec lod_center; // mesh center position used for calculating lod level, usually equal to "box.center()"

   Int      lods(     )C {return     _lods.elms()+1                  ;} // get number of Level of Details including self
   MeshLod& lod (Int i)  {return i ? _lods[i-1] :                  T ;} // return  i-th  Level of Detail
 C MeshLod& lod (Int i)C {return i ? _lods[i-1] : SCAST(C MeshLod, T);} // return  i-th  Level of Detail

   Skeleton*  skeleton(                  )C {return _skeleton;} // get Skeleton linked with this Mesh
   Mesh&      skeleton(Skeleton *skeleton);                     // link Mesh with specified Skeleton file, avoid calling this realtime as it requires adjusting the vertex skinning information (bone indexes) and re-creating the hardware mesh version
   Mesh& clearSkeleton(                  );                     // clear Mesh link to skeleton and remove all information related to vertex bone mapping

   Enum* drawGroupEnum(                                       )C {return _draw_group_enum;} // get enum used for specifying draw groups in all parts for this Mesh, you should pass this value to 'MeshPart.drawGroup' method
   Mesh& drawGroupEnum(Enum *e, Bool reset_when_not_found=true);                            // set enum used for specifying draw groups in all parts for this Mesh, 'reset_when_not_found'=if existing mesh part draw groups are not found, then their draw masks will be reset for "reset_when_not_found==true" and kept for "reset_when_not_found==false"

   // manage
   Mesh& del   (                                          ); // delete manually
   Mesh& create(  Int        parts                        ); // create with 'parts' empty MeshPart's
   Mesh& create(C Mesh      &src        , UInt flag_and=~0); // create from 'src', 'flag_and'=MESH_BASE_FLAG
   Mesh& create(C MeshGroup &src        , UInt flag_and=~0); // create from 'src', 'flag_and'=MESH_BASE_FLAG
   Mesh& create(C Mesh *mesh, Int meshes, UInt flag_and=~0); // create from mesh array, 'flag_and'=MESH_BASE_FLAG

   Mesh& exclude (UInt flag); // exclude   elements specified with 'flag' MESH_BASE_FLAG
   Mesh& keepOnly(UInt flag); // keep only elements specified with 'flag' MESH_BASE_FLAG

   // get
   UInt memUsage()C; // get memory usage

 C MeshLod& getDrawLod (C Matrix &matrix)C; // get          Level of Detail which should be used for drawing with current camera and given object 'matrix'
   Int      getDrawLodI(C Matrix &matrix)C; // get index of Level of Detail which should be used for drawing with current camera and given object 'matrix'

   Flt lodQuality(Int i, Int base=0)C; // get quality of Level of Detail comparing i-th to base level, returning value in range of 0..1 where 1=full quality, 0=zero quality

   // set
   Mesh& setNormals   (Bool by_face_area=true); // recalculate vertex 3D normals, 'by_face_area'=if use weight according to face surface area - default, (if false then face angle is used)
   Mesh& setTangents  (                      ); // recalculate vertex 3D tangents
   Mesh& setBinormals (                      ); // recalculate vertex 3D binormals
   Mesh& setAutoTanBin(                      ); // automatically calculate vertex tangents and binormals if needed, if they're not needed then they will be removed
   Bool  setBox       (                      ); // recalculate bounding box, false on fail

   Mesh& setVtxDup                             (UInt flag=0, Flt pos_eps=EPS, Flt nrm_cos=0.999f); // set vertex 3D duplicates (vtx.dup)
   Mesh& setVtxColorAlphaAsTesselationIntensity(Bool tesselate_edges                            ); // set vertex color alpha   (vtx.color.a) as tesselation intensity, 'tesselate_edges'=if tesselate non continuous edges
   Mesh& setAdjacencies                        (                                                ); // set all adjacencies      (edge.adj_face, tri.adj_edge, tri.adj_face, quad.adj_edge, quad.adj_face)

   Mesh& delBase  (                       ); // delete all software meshes (MeshBase  ) in this mesh
   Mesh& delRender(                       ); // delete all hardware meshes (MeshRender) in this mesh
   Mesh& setBase  (Bool only_if_empty=true); // set software  version, convert 'MeshRender' to 'MeshBase', 'only_if_empty'=perform conversion only if the MeshBase is empty (if set to false then conversion is always performed)
   Mesh& setRender(Bool optimize     =true); // set rendering version, convert 'MeshBase'   to 'MeshRender', 'optimize'=if optimize the mesh by re-ordering the vertexes/triangles for optimal processing on the GPU
   Mesh& setShader(                       ); // reset shader
   Mesh& material (C MaterialPtr &material); // set material, 'material' must point to object in constant memory address (mesh will store only the pointer to the material and later use it if needed), avoid changing materials real-time during rendering, instead consider using material variations (set them once, and later select which one to use with 'SetVariation' function)

   // join / split
   Mesh& join   (Int i0, Int i1                                          , Bool weld_vtxs=true); // join i0-th and i1-th parts together, 'weld_vtxs'=if automatically weld vertexes after joining
   Mesh& joinAll(Bool test_material, Bool test_draw_group, Bool test_name, Bool weld_vtxs=true); // join all parts, 'test_material'=join only those MeshPart's which have the same material, 'test_draw_group'=join only those MeshPart's which have the same draw group, 'test_name'=join only those MeshPart's which have the same name, 'weld_vtxs'=if automatically weld vertexes after joining

   // transform
   Mesh& move     (                  C Vec &move); //           move Mesh
   Mesh& scale    (C Vec     &scale             ); // scale          Mesh
   Mesh& scaleMove(C Vec     &scale, C Vec &move); // scale and move Mesh
   Mesh& setSize  (C Box     &box               ); // scale and move Mesh to fit box
   Mesh& transform(C Matrix3 &matrix            ); // transform by matrix
   Mesh& transform(C Matrix  &matrix            ); // transform by matrix
   Mesh& mirrorX  (                             ); // mirror in X axis
   Mesh& mirrorY  (                             ); // mirror in Y axis
   Mesh& mirrorZ  (                             ); // mirror in Z axis
   Mesh& reverse  (                             ); // reverse faces

   // texture transform
   Mesh& texMove  (C Vec2 &move , Byte tex_index=0); // move   texture uv's
   Mesh& texScale (C Vec2 &scale, Byte tex_index=0); // scale  texture uv's
   Mesh& texRotate(  Flt   angle, Byte tex_index=0); // rotate texture uv's

   // operations
   Mesh& weldVtx      (UInt flag=0, Flt pos_eps=EPS, Flt nrm_cos=0.999f, Bool remove_degenerate_faces=true); // weld 3D vertexes     , this function will weld vertexes together if they share the same position             , 'flag'=if selected elements aren't equal then don't weld (MESH_BASE_FLAG), 'remove_degenerate_faces'=if automatically remove degenerate faces which may occur after welding vertexes
   Mesh& weldVtxValues(UInt flag  , Flt pos_eps=EPS, Flt nrm_cos=0.999f, Bool remove_degenerate_faces=true); // weld    vertex values, this function will weld values of vertexes which  share the same position             , 'flag'=                                 elements to weld (MESH_BASE_FLAG), 'remove_degenerate_faces'=if automatically remove degenerate faces which may occur after welding vertexes

   Mesh& subdivide(); // smooth subdivide faces

   Bool  boneRename(C Str8 &src, C Str8 &dest                      ); // rename 'src' bone to 'dest' bone, returns true if a bone has been renamed
   Mesh& boneRemap (C Memp<Byte> &old_to_new, Bool remap_names=true); // remap vertex bone/matrix indexes according to bone 'old_to_new' remap, 'remap_names'=if remap the bone names as well

   Mesh& freeOpenGLESData(); // this method is used only under OpenGL ES (on other platforms it is ignored), the method frees the software copy of the GPU data which increases available memory, however after calling this method the data can no longer be accessed on the CPU (can no longer be locked or saved to file)

   // variations
   Mesh& variations     (Int variations              );   Int     variations   (            )C; // set/get number of material variations (meshes always have at least 1 material variation)
   Mesh& variationName  (Int variation, C Str8 &name );   CChar8* variationName(Int     i   )C; // set/get           material variation name (first material variation always has name = NULL and it can't be changed)
                                                          UInt    variationID  (Int     i   )C; //     get           material variation ID   (first material variation always has ID   = 0    and it can't be changed)
                                                          Int     variationFind(CChar8 *name)C; //    find index  of material variation which name is equal to 'name', -1 is returned if variation was not found
                                                          Int     variationFind(UInt    id  )C; //    find index  of material variation which ID   is equal to 'id'  , -1 is returned if variation was not found
   Mesh& variationRemove(Int variation               );                                         //  remove specified 'variation'
   Mesh& variationKeep  (Int variation               );                                         //  keep   specified 'variation' and remove all others
   Mesh& variationMove  (Int variation, Int new_index);                                         //    move specified 'variation' to a 'new_index'

   // fix
   Mesh& fixTexOffset  (Byte tex_index=0); // fix texture offset , this reduces big texture coordinates to small ones increasing texturing quality on low precision video cards
   Mesh& fixTexWrapping(Byte tex_index=0); // fix texture wraping, fixes texture coordinates created by spherical/tube mapping (this can add new vertexes to the mesh)

   // convert
   Mesh& edgeToDepth    (Bool tex_align =true  ); // edges to depth (extrude 2D edges to 3D faces)
   Mesh& edgeToTri      (Bool set_id    =false ); // edges to triangles (triangulation)
   Mesh& triToQuad      (Flt  cos       =0.999f); // triangles to quads    , 'cos'=minimum cosine between 2      triangle normals to weld  them into 1 quad (0..1)
   Mesh& quadToTri      (Flt  cos       =2     ); // quads     to triangles, 'cos'=minimum cosine between 2 quad triangle normals to leave them as   1 quad (0..1, value >1 converts all quads into triangles)
   Mesh& toStencilShadow(Bool join_parts=true  ); // convert   to stencil shadow mesh, mesh must be closed (have no holes) and can't be infinite, 'join_parts'=if automatically join MeshPart's (uses 'join()' for skinned and 'join(MESH_JOIN_NAME)' for non skinned mesh)

   // add / remove
   Mesh& add   (C MeshBase &src         ); // add MeshBase to self
   Mesh& add   (C MeshPart &src         ); // add MeshPart to self
   Mesh& add   (C Mesh     &src         ); // add Mesh     to self
   Mesh& remove(Int i, Bool set_box=true); // remove i-th MeshPart, 'set_box'=if recalculate bounding box

   MeshLod&    newLod(     ); // add empty   MeshLod
   MeshLod&    newLod(Int i); // add empty   MeshLod at i lod index
   Mesh   & removeLod(Int i); // remove i-th MeshLod
   Mesh   &   setLods(Int n); // set n levels of MeshLod's, new lods will be empty

   // optimize
   Mesh& removeDegenerateFaces();
   Mesh& removeUnusedVtxs     (Bool include_edge_references=true); // remove vertexes which aren't used by any face or edge, if 'include_edge_references' is set to false then only face references are tested (without the edges)

   Mesh& simplify(Flt intensity, Flt max_distance=1.0f, Flt max_uv=1.0f, Flt max_color=0.03f, Flt max_material=0.08f, Flt max_normal=PI, Bool keep_border=false, Flt border_priority=0.0f, MESH_SIMPLIFY mode=SIMPLIFY_DENSITY, Mesh *dest=NULL); // simplify mesh by removing vertexes/faces, 'intensity'=how much to simplify (0..1, 0=no simplification, 1=full simplification), 'max_distance'=max distance between elements to merge them (0..Inf), 'max_uv'=max allowed vertex texture UV deviations (0..1), 'max_color'=max allowed vertex color deviations (0..1), 'max_material'=max allowed vertex material deviations (0..1), 'max_normal'=max allowed vertex normal angle deviations (0..PI), 'keep_border'=if always keep border edges (edges that have faces only on one side), 'border_priority'=priority of border faces (-Inf..Inf, <0 decreases priority and makes border edges more likely to be removed, >0 increases priority and makes border edges less likely to be removed), 'dest'=destination MeshBase (if set to NULL then the mesh will simplify itself), returns dest

   // draw
      // default drawing, doesn't use automatic Frustum Culling, this doesn't draw the mesh immediately, instead it adds the mesh to a draw list
      void draw(C Matrix           &matrix, C Vec &vel=VecZero, C Vec &ang_vel=VecZero, Bool use_early_z=false)C; // add mesh to draw list using 'matrix'    matrix, 'vel' velocity and 'ang_vel' angular velocity, this should be called only in RM_PREPARE, when used it will automatically draw meshes in following modes when needed: RM_EARLY_Z RM_SIMPLE RM_SOLID RM_SOLID_M RM_AMBIENT RM_BLEND
      void draw(C AnimatedSkeleton &anim_skel                                                                 )C; // add mesh to draw list using 'anim_skel' matrixes and  velocities                             , this should be called only in RM_PREPARE, when used it will automatically draw meshes in following modes when needed: RM_EARLY_Z RM_SIMPLE RM_SOLID RM_SOLID_M RM_AMBIENT RM_BLEND, 'anim_skel' must point to constant memory address (the pointer is stored through which the object can be accessed later during frame rendering)

      void drawShadow(C Matrix           &matrix   )C; // add mesh to shadow draw list using 'matrix'    matrix  , this should be called only in RM_SHADOW
      void drawShadow(C AnimatedSkeleton &anim_skel)C; // add mesh to shadow draw list using 'anim_skel' skeleton, this should be called only in RM_SHADOW, 'anim_skel' must point to constant memory address (the pointer is stored through which the object can be accessed later during frame rendering)

      // draw blended, this is an alternative to default 'draw' (typically 'draw' draws blended meshes automatically for materials with technique in blend mode), this method however draws the mesh immediately (which allows to set custom shader parameters per draw call), it always uses blend shaders regardless if the material has technique set in blend mode, and provides additional control over material color, this can be called only in RM_BLEND rendering mode, doesn't use automatic Frustum culling
      void drawBlend(                               C Vec4 *color=NULL)C; // draw with  current    matrix  , 'color'=pointer to optional Material color multiplication
      void drawBlend(C Matrix           &matrix   , C Vec4 *color=NULL)C; // draw with 'matrix'    matrix  , 'color'=pointer to optional Material color multiplication
      void drawBlend(C AnimatedSkeleton &anim_skel, C Vec4 *color=NULL)C; // draw with 'anim_skel' matrixes, 'color'=pointer to optional Material color multiplication

      // draw mesh outline, this can be optionally called in RM_OUTLINE in order to outline the mesh, doesn't use automatic Frustum culling
      void drawOutline(C Color &color                               )C; // draw with  current    matrix
      void drawOutline(C Color &color, C Matrix           &matrix   )C; // draw with 'matrix'    matrix
      void drawOutline(C Color &color, C AnimatedSkeleton &anim_skel)C; // draw with 'anim_skel' matrixes

      // draw using the "behind" effect, this can be optionally called in RM_BEHIND, doesn't use automatic Frustum culling, 'color_perp'=color to be used for normals perpendicular to camera, 'color_parallel'=color to be used for normals parallel to camera
      void drawBehind(C Color &color_perp, C Color &color_parallel                               )C; // draw with  current    matrix
      void drawBehind(C Color &color_perp, C Color &color_parallel, C Matrix           &matrix   )C; // draw with 'matrix'    matrix
      void drawBehind(C Color &color_perp, C Color &color_parallel, C AnimatedSkeleton &anim_skel)C; // draw with 'anim_skel' matrixes

      // draw as stencil shadow, automatically uses Frustum culling, this can be called only in RM_STENCIL_SHADOW
      void drawStencilShadow(                             )C; // draw with  current    matrix
      void drawStencilShadow(C Matrix           &matrix   )C; // draw with 'matrix'    matrix
      void drawStencilShadow(C AnimatedSkeleton &anim_skel)C; // draw with 'anim_skel' matrixes

   // io
   void operator=(C Str  &name) ; // load, Exit  on fail
   Bool save     (C Str  &name)C; // save, false on fail
   Bool load     (C Str  &name) ; // load, false on fail
   void save     (  File &f, CChar *path=NULL)C; // save, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path)
   Bool load     (  File &f, CChar *path=NULL) ; // load, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail

   void operator*=(C Matrix3  &m   ) {transform(m   );} // transform by matrix
   void operator*=(C Matrix   &m   ) {transform(m   );} // transform by matrix
   void operator+=(C MeshBase &mshb) {add      (mshb);} // add MeshBase
   void operator+=(C MeshPart &part) {add      (part);} // add MeshPart
   void operator+=(C Mesh     &mesh) {add      (mesh);} // add Mesh

  ~Mesh() {del();}
   Mesh();

private:
   struct Variations
   {
      void          del();
     ~Variations() {del();}
      Variations() {_variation=NULL; _variations=0;}

      Ptr _variation;
      Int _variations;
      Variations(C Variations &);
   };

   Skeleton     *_skeleton;
   Enum         *_draw_group_enum;
   Mems<MeshLod> _lods;
   BoneMap       _bone_map;
   Variations    _variations;

   NO_COPY_CONSTRUCTOR(Mesh);
};
/******************************************************************************/
DECLARE_CACHE(Mesh, Meshes, MeshPtr); // 'Meshes' cache storing 'Mesh' objects which can be accessed by 'MeshPtr' pointer

inline Int Elms(C Mesh &mesh) {return mesh.parts.elms();}
/******************************************************************************/

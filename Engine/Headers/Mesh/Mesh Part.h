/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   'MeshPart' is a single part of a mesh.
      Each part contains its vertex/face data in software 'MeshBase' and hardware version 'MeshRender'.
      Each part contains also a 'name' and a 'material'.

/******************************************************************************/
enum MSHP_FLAG // Mesh Part Flag
{
   MSHP_NO_PHYS_BODY=0x01, // if no physical body will be made out of this part (this flag is checked when creating a physical body from Mesh and ignoring all parts that have this flag enabled)
   MSHP_HIDDEN      =0x02, // if hidden (this flag is checked in 'Sweep' functions, it is not used however for rendering, for preventing mesh parts from being rendered please use 'MeshPart.drawGroup' and 'SetDrawMask')
};
struct MeshPart // Mesh Base + Mesh Render
{
   MeshBase   base     ; // software mesh version (on CPU)
   MeshRender render   ; // hardware mesh version (on GPU)
   Char8      name[32] ; // name
   Byte       part_flag; // MSHP_FLAG

   // manage
   MeshPart& del   (                                 ); // delete
   MeshPart& create(C MeshPart &src, UInt flag_and=~0); // create from 'src', 'flag_and'=MESH_BASE_FLAG

   MeshPart& exclude (UInt flag); // exclude   elements specified with 'flag' MESH_BASE_FLAG
   MeshPart& keepOnly(UInt flag); // keep only elements specified with 'flag' MESH_BASE_FLAG

   // get
   Bool is           (                )C {return base.is() || render.is();} // if  has any data
   UInt flag         (                )C;                                   // get MESH_BASE_FLAG
   UInt memUsage     (                )C;                                   // get memory usage
   Int  vtxs         (                )C;                                   // get total number of vertexes
   Int  edges        (                )C;                                   // get total number of edges
   Int  tris         (                )C;                                   // get total number of triangles
   Int  quads        (                )C;                                   // get total number of quads
   Int  faces        (                )C;                                   // get total number of faces                    , faces    =(triangles + quads  )
   Int  trisTotal    (                )C;                                   // get total number of triangles including quads, trisTotal=(triangles + quads*2)
   Bool getBox       (Box &box        )C;                                   // get box encapsulating the MeshPart, this method iterates through all vertexes, false on fail (if no vertexes are present)
   Flt  area         (Vec *center=NULL)C;                                   // get surface area of all mesh faces, 'center'=if specified then it will be calculated as the average surface center
   Bool sameMaterials(C MeshPart &part)C;                                   // if  has exactly the same materials as 'part' mesh part, this method compares materials, multi materials and material variations

   // set
   MeshPart& delBase      (                       ); // delete software mesh (MeshBase  )
   MeshPart& delRender    (                       ); // delete hardware mesh (MeshRender)
   MeshPart& setBase      (Bool only_if_empty=true); // set software  version, convert 'MeshRender' to 'MeshBase', 'only_if_empty'=perform conversion only if the MeshBase is empty (if set to false then conversion is always performed)
   MeshPart& setRender    (Bool optimize     =true); // set rendering version, convert 'MeshBase'   to 'MeshRender', 'optimize'=if optimize the mesh by re-ordering the vertexes/triangles for optimal processing on the GPU
   MeshPart& setShader    (Int  lod_index         ); // reset shader , 'lod_index'=index of the lod in the mesh (required in order to set appropriate quality of the shader)
   MeshPart& setAutoTanBin(                       ); // automatically calculate vertex tangents and binormals if needed, if they're not needed then they will be removed

   MeshPart& drawGroup(Int group, Enum *draw_group_enum=NULL) ; // set draw group         for this mesh part (default=0), 'group'=group index and at the same time it's an enum element index from 'draw_group_enum' (allowed ranges are 0..31, value of -1 will force the mesh part to never be drawn), 'draw_group_enum'=custom enum where each element represents a different group, specifying it is optional (draw group will be set either way) however recommended (it allows for setting correct draw group upon loading the Mesh even when the Enum and its elements were changed), this enum should be set to 'Mesh.drawGroupEnum' of the Mesh containing this MeshPart, this function should be used together with 'SetDrawMask' allowing to control which MeshPart's should be included in drawing
   Int       drawGroup(                                     )C; // get draw group assigned to this part (0..31, or -1 if invalid)

   // set / get
   MeshPart   & material(C MaterialPtr &material, Int lod_index=0);                               // set mesh part material, 'lod_index'=index of the lod in the mesh (required in order to set appropriate quality of the shader), 'material' must point to object in constant memory address (mesh will store only the pointer to the material and later use it if needed), avoid changing materials real-time during rendering, instead consider using material variations (set them once, and later select which one to use with 'SetVariation' function)
 C MaterialPtr& material(                                        )C {return _variation.material;} // get mesh part material

   MeshPart& variations(Int variations                        );   Int          variations(             )C; // set/get number of variations (mesh parts always have at least 1 variation), variations allow for specifying different materials for mesh parts, active variation for rendering can be specified using 'SetVariation' function
   MeshPart& variation (Int variation, C MaterialPtr &material); C MaterialPtr& variation (Int variation)C; // set/get material for specified variation (calling this method with index=0 is the same as calling 'material' methods)

   MeshPart&    multiMaterial(C MaterialPtr &m0, C MaterialPtr &m1, C MaterialPtr &m2, C MaterialPtr &m3, Int lod_index=0); // set multi materials, multi materials are used for terrain meshes allowing to blend triangles smoothly between multiple terrain materials, 'lod_index'=index of the lod in the mesh (required in order to set appropriate quality of the shader), materials must point to object in constant memory address (mesh will store only the pointer to the material and later use it if needed)
 C MaterialPtr& multiMaterial(Int i)C; // get i-th multi material

   // transform
   MeshPart& move     (                  C Vec &move); //           move MeshPart
   MeshPart& scale    (C Vec     &scale             ); // scale          MeshPart
   MeshPart& scaleMove(C Vec     &scale, C Vec &move); // scale and move MeshPart
   MeshPart& transform(C Matrix3 &matrix            ); // transform by matrix
   MeshPart& transform(C Matrix  &matrix            ); // transform by matrix

   // texture transform
   MeshPart& texMove  (C Vec2 &move , Byte tex_index=0); // move   texture uv's
   MeshPart& texScale (C Vec2 &scale, Byte tex_index=0); // scale  texture uv's
   MeshPart& texRotate(  Flt   angle, Byte tex_index=0); // rotate texture uv's

   // operations
   MeshPart& boneRemap(C Memp<Byte> &old_to_new); // remap vertex bone/matrix indexes according to bone 'old_to_new' remap

   MeshPart& freeOpenGLESData(); // this method is used only under OpenGL ES (on other platforms it is ignored), the method frees the software copy of the GPU data which increases available memory, however after calling this method the data can no longer be accessed on the CPU (can no longer be locked or saved to file)

   MeshPart& setLeafAttachment   (C Vec2 &tex       ); // this method will set    leaf attachment according to texture coordinates
   MeshPart& setRandomLeafColor  (Flt variation=0.3f); // this method will set    random colors  for different leafs (this will only affect mesh parts which have leaf-based material), 'variation'=how different the colors should be from each other (0..1)
   MeshPart& setRandomLeafBending(                  ); // this method will set    unique bending for different leafs (this will only affect mesh parts which have leaf-based material)
   MeshPart& delRandomLeafBending(                  ); // this method will remove unique bending for different leafs

   // draw
      // default drawing, doesn't use automatic Frustum Culling, this doesn't draw the mesh immediately, instead it adds the mesh to a draw list
      void draw(C Matrix           &matrix, C Vec &vel=VecZero, C Vec &ang_vel=VecZero, Bool use_early_z=false)C; // add mesh to draw list using 'matrix'    matrix, 'vel' velocity and 'ang_vel' angular velocity, this should be called only in RM_PREPARE, when used it will automatically draw meshes in following modes when needed: RM_EARLY_Z RM_SIMPLE RM_SOLID RM_SOLID_M RM_AMBIENT RM_BLEND
      void draw(C AnimatedSkeleton &anim_skel                                                                 )C; // add mesh to draw list using 'anim_skel' matrixes and  velocities                             , this should be called only in RM_PREPARE, when used it will automatically draw meshes in following modes when needed: RM_EARLY_Z RM_SIMPLE RM_SOLID RM_SOLID_M RM_AMBIENT RM_BLEND, 'anim_skel' must point to constant memory address (the pointer is stored through which the object can be accessed later during frame rendering)

      void drawShadow(C Matrix           &matrix   )C; // add mesh to shadow draw list using 'matrix'    matrix  , this should be called only in RM_SHADOW
      void drawShadow(C AnimatedSkeleton &anim_skel)C; // add mesh to shadow draw list using 'anim_skel' skeleton, this should be called only in RM_SHADOW, 'anim_skel' must point to constant memory address (the pointer is stored through which the object can be accessed later during frame rendering)

      // draw blended, this is an alternative to default 'draw' (typically 'draw' draws blended meshes automatically for materials with technique in blend mode), this method however draws the mesh immediately (which allows to set custom shader parameters per draw call) and provides additional control over material color, it always uses blend shaders regardless if the material has technique set in blend mode, this can be called only in RM_BLEND rendering mode, doesn't use automatic Frustum culling
      void drawBlend(C Vec4 *color=NULL)C; // draw with current matrix, 'color'=pointer to optional Material color multiplication

      // draw overlay
      void drawOverlay(C Image &image, C Color &color=WHITE)C; // draw as overlay using 'image' and 'color', this can be called only in RM_OVERLAY, doesn't use automatic Frustum culling

      // draw mesh outline, this can be optionally called in RM_OUTLINE in order to outline the mesh, doesn't use automatic Frustum culling
      void drawOutline(C Color &color)C; // draw with current matrix

      // draw using the "behind" effect, this can be optionally called in RM_BEHIND, doesn't use automatic Frustum culling
      void drawBehind(C Color &color_perp, C Color &color_parallel)C; // draw with current matrix, 'color_perp'=color to be used for normals perpendicular to camera, 'color_parallel'=color to be used for normals parallel to camera

      // draw by highlight bone in mesh skin, use this for debugging, this can be called only in RM_BLEND rendering mode, doesn't use automatic Frustum culling
      void drawBoneHighlight(Int bone)C; // draw with current matrix, 'bone'=bone index to highlight

   MeshPart& operator+=(C MeshPart &src); // add 'src'

  ~MeshPart() {del();}
   MeshPart();

private:
   struct Variation
   {
      MaterialPtr material;
      ShaderTech *shader[RM_SHADER_NUM];
      Variation();
      Ptr   frst, blst;
   };
   Flt             _vtx_heightmap;
   UInt            _draw_mask, _draw_mask_enum_id;
        Variation  _variation;
   Mems<Variation> _variations;
   MaterialPtr     _materials[3];
   Ptr             _umm;
   NO_COPY_CONSTRUCTOR(MeshPart);
};
/******************************************************************************/

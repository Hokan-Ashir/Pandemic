/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'MeshOverlay' for rendering semi transparent images on solid surfaces (like bullet holes).

/******************************************************************************/
struct MeshOverlay // Mesh Overlay - used for rendering semi transparent images on solid surfaces (like bullet holes), this is an alternative to 'Decal' which affects also nearby objects
{
   Bool createStatic  (Mesh &mesh, C MaterialPtr &material, C Matrix &overlay_matrix, C Matrix *mesh_matrix=NULL); // create from source 'mesh', 'material'=overlay material, 'overlay_matrix'=matrix of the overlay in world space (with 'overlay_matrix.x overlay_matrix.y' being the surface vectors and 'overlay_matrix.z' being the direction vector, length of all the vectors determines overlay size), 'mesh_matrix'=source mesh matrix at the moment of applying the overlay (if NULL 'MatrixIdentity' will be used), returns false when no mesh has been created
   Bool createAnimated(Mesh &mesh, C MaterialPtr &material, C Matrix &overlay_matrix, C Matrix *mesh_matrix=NULL); // create from source 'mesh', 'material'=overlay material, 'overlay_matrix'=matrix of the overlay in world space (with 'overlay_matrix.x overlay_matrix.y' being the surface vectors and 'overlay_matrix.z' being the direction vector, length of all the vectors determines overlay size), 'mesh_matrix'=source mesh matrix at the moment of applying the overlay (if NULL 'MatrixIdentity' will be used), returns false when no mesh has been created

   // get / set
   MeshOverlay& material(C MaterialPtr &material);   C MaterialPtr& material()C {return _material;} // set/get material

   // draw, 'MeshOverlay' should be drawn in each frame with the same 'Matrix' or 'AnimatedSkeleton' as the source 'mesh' from which 'MeshOverlay' has been created, drawing should be called only in RM_OVERLAY rendering mode, doesn't use automatic Frustum culling
   void draw(                               Flt alpha=1)C; // draw with  current    matrix  , 'alpha'=opacity
   void draw(C Matrix           &matrix   , Flt alpha=1)C; // draw with 'matrix'    matrix  , 'alpha'=opacity
   void draw(C AnimatedSkeleton &anim_skel, Flt alpha=1)C; // draw with 'anim_skel' matrixes, 'alpha'=opacity

   // io
   void save(File &f)C; // save
   Bool load(File &f) ; // load, false on fail

   MeshOverlay& del(); // delete manually
   MeshOverlay();

private:
   struct Lod
   {
      Flt        dist2;
      MeshRender mshr;
   };
   Vec         _lod_center;
   Box         _box;
   Matrix      _matrix;
   Mems<Lod>   _lods;
   MaterialPtr _material;
   ShaderTech *_shader;
   NO_COPY_CONSTRUCTOR(MeshOverlay);
};
/******************************************************************************/

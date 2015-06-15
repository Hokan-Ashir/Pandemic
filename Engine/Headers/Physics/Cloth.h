/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Cloth' to simulate realistic cloth behavior.

   'ClothMesh' may not be deleted manually if there's still at least one 'Cloth' using the mesh.
      This means that the 'ClothMesh' may be deleted only after deleting all 'Cloth' objects using the mesh.

/******************************************************************************/
const_mem_addr struct ClothMesh // Physical Cloth Mesh, it is created from MeshBase and is used to create Cloth !! must be stored in constant memory address !!
{
   // manage
   ClothMesh& del   (                                                                  ); // delete manually
   ClothMesh& create(C MeshBase &mesh, C MaterialPtr &material, Skeleton *skeleton=NULL); // create from 'mesh' with 'material', set 'skeleton' for a Skeleton file to automatically adjust ClothMesh vertex bone indexes when loading to match the skeleton bone order

   // get
   Int       vtxs()C {return _phys.vtxs();} // get physical cloth vertex number
 C MeshBase& mesh()C {return _phys       ;} // get physical cloth mesh

   Skeleton*  skeleton(                  )C {return _skeleton;} // get Skeleton linked with this ClothMesh
   ClothMesh& skeleton(Skeleton *skeleton);                     // link ClothMesh with specified Skeleton file, avoid calling this realtime as it requires adjusting the vertex skinning information (bone indexes) and re-creating the hardware mesh version

 C MaterialPtr& material()C {return _material;} // get ClothMesh material

   // operations
   Bool boneRename(C Str8 &src, C Str8 &dest                      ); // rename 'src' bone to 'dest' bone, returns true if a bone has been renamed
   void boneRemap (C Memp<Byte> &old_to_new, Bool remap_names=true); // remap vertex bone/matrix indexes according to bone 'old_to_new' remap, 'remap_names'=if remap the bone names as well

   // io
   Bool save(C Str &name)C; // save, false on fail
   Bool load(C Str &name) ; // load, false on fail
   void save(File &f, CChar *path=NULL)C; // save, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path)
   Bool load(File &f, CChar *path=NULL) ; // load, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail

  ~ClothMesh() {del();}
   ClothMesh();

private:
   struct Scale
   {
      Flt scale;
      Ptr mesh;
   };
   MeshBase    _phys;
   MeshRender  _skin;
   Memc<Scale> _scales;
   MaterialPtr _material;
   IndBuf      _ind_buf;
   ShaderTech *_skin_shader[RM_SHADER_NUM],
              *_phys_shader[RM_SHADER_NUM];
   Ptr         _skin_frst, _phys_frst;
   Skeleton   *_skeleton;
   BoneMap     _bone_map;
   NO_COPY_CONSTRUCTOR(ClothMesh);
};
/******************************************************************************/
struct Cloth // Physical Cloth
{
   // manage
   Cloth& del(); // delete manually

   // get / set
   ClothMesh* clothMesh()C {return _cloth_mesh;}               // get     original 'ClothMesh' from which the 'Cloth' has been created
   Flt        scale    ()C {return _scale     ;}               // get     the scale which was used during the cloth creation
   Int        vtxs     ()C;                                    // get     number of vertexes
   Vec        wind     ()C;   Cloth& wind  (C Vec     &accel); // get/set wind acceleration
   Game::Obj* obj      ()C;   Cloth& obj   (Game::Obj *obj  ); // get/set pointer to game object containing the cloth
   Bool       sleep    ()C;   Cloth& sleep (Bool       sleep); // get/set sleeping
   Box        box      ()C;                                    // get     world box containing the physical cloth

   Flt damping ()C;   Cloth& damping (Flt damping ); // get/set damping , 0..1
   Flt friction()C;   Cloth& friction(Flt friction); // get/set friction, 0..1
   Flt bending ()C;   Cloth& bending (Flt bending ); // get/set bending , 0..1

   // draw
   void drawSkinned        (C AnimatedSkeleton &anim_skel                      )C; // draw   normally skinned   cloth part using 'anim_skel', doesn't       use  Frustum culling, this can be called only in RM_PREPARE
   void drawSkinnedShadow  (C AnimatedSkeleton &anim_skel                      )C; // draw   normally skinned   cloth part using 'anim_skel', doesn't       use  Frustum culling, this can be called only in RM_SHADOW
   void drawSkinnedOutline (C AnimatedSkeleton &anim_skel, C Color &color      )C; // draw   normally skinned   cloth part using 'anim_skel', doesn't       use  Frustum culling, this can be called only in RM_OUTLINE in order to outline the mesh
   void drawPhysical       (                               C Vec   &vel=VecZero)C; // draw physically simulated cloth part                  , automatically uses Frustum culling, this can be called only in RM_PREPARE
   void drawPhysicalShadow (                                                   )C; // draw physically simulated cloth part                  , automatically uses Frustum culling, this can be called only in RM_SHADOW
   void drawPhysicalOutline(                               C Color &color      )C; // draw physically simulated cloth part                  , automatically uses Frustum culling, this can be called only in RM_OUTLINE in order to outline the mesh

   // methods for PhysX 3 only
      struct Particle
      {
         Vec pos         ; // position of a single particle
         Flt inverse_mass; // set 0 for static or 1 for dynamic particle (static will not move at all, dynamic will move according to physics simulation)
      };
      Bool create(ClothMesh &cloth_mesh, C Matrix &matrix); // create from 'cloth_mesh', 'matrix'=cloth matrix where its scale determines cloth scale, false on fail

      // get / set
      Bool ccd()C;   Cloth& ccd(Bool on); // get/set continuous collision detection
      Bool gpu()C;   Cloth& gpu(Bool on); // get/set cloth processing on the GPU

      Flt    drag        ()C;   Cloth&    drag        (Flt drag ); // get/set         drag coefficient, 0..1, default=0.0
      Flt angDrag        ()C;   Cloth& angDrag        (Flt drag ); // get/set angular drag coefficient, 0..1, default=0.0
      Flt    inertiaScale()C;   Cloth&    inertiaScale(Flt scale); // get/set         inertia scale   , 0..1, default=1.0
      Flt angInertiaScale()C;   Cloth& angInertiaScale(Flt scale); // get/set angular inertia scale   , 0..1, default=1.0

    C Particle* lockRead(); // access cloth particles for reading, length of returned array is equal to 'vtxs', after calling this method you need to call 'unlock'
      Cloth&  unlock    (); // unlock read access, this must be called after 'lockRead'
      Cloth&    set     (C Particle *particle, Int particles); // set custom particles for the cloth, length of this array must be at least as long as 'vtxs'

      Cloth& setCollisionBalls   (C Memp<Ball > &balls   ); // set balls    that collide with this Cloth (up to 32 balls    are supported)
      Cloth& setCollisionCapsules(C Memp<VecI2> &capsules); // set capsules that collide with this Cloth (up to 32 capsules are supported), they are specified using indexes for both ends of capsule balls from the 'balls' specified using 'setCollisionBalls' (they must be set prior to calling 'setCollisionCapsules')

   // methods for PhysX 2 only
      enum FLAG
      {
         DISABLE_COLLISIONS    =1<<0, // disable collisions between rigid bodies, increases performance
         DISABLE_SELF_COLLISION=1<<1, // disable collisions between cloth faces , increases performance
         CENTER_OF_MASS_DAMPING=1<<2, // set damping to 'center of mass mode'
         HARDWARE              =1<<3, // create the cloth in a hardware compartment, this will make cloth simulation much faster at the cost of worse synchronization with other objects, for this option to work - Physics must be created with hardware enabled, default=false
      };
      struct Param // Cloth Creation Parameters
      {
         UInt flag               ; // FLAG  , default=0
         Flt  thickness          , // 0..Inf, default=0.1
              density            , // 0..Inf, default=1
              bending            , // 0..1  , default=0
              stretching         , // 0..1  , default=0
              damping            , // 0..1  , default=0
              friction           , // 0..1  , default=0.5
              glue_vel           , // 0..Inf, default=0  , glue velocity, this feature is useful when the cloth is attached to a fast moving actor, used only when set to >0
              response           , // 0..Inf, default=0.2, 0 increases performance
              attachment_response, // 0..Inf, default=0.2, 0 increases performance
              pressure           ; // 0..Inf, default=0  , 0 increases performance

         Param();
      };
      struct Vtx // Cloth Vertex
      {
         Vec  pos, // position
              nrm; // normal
         Vec2 tex; // texture coordinates
      };
      Bool create(ClothMesh &cloth_mesh, C Matrix &matrix, C Param &param); // create from 'cloth_mesh', 'matrix'=cloth matrix where its scale determines cloth scale, false on fail

    C Vtx* vtx   (     )C {return _vtx;}                       // get     cloth's vertex array, this array is updated each frame containing the most recent vertex values
      Vec  vtxPos(Int i)C;   Cloth& vtxPos(Int i, C Vec &pos); // get/set i-th vertex position
      Vec  vtxVel(Int i)C;   Cloth& vtxVel(Int i, C Vec &vel); // get/set i-th vertex velocity
      Byte group (     )C;   Cloth& group (Byte group       ); // get/set collision group (0..31, default value is taken according to ACTOR_GROUP)

      // parameters
      Flt density           ()C;                                              // get     density            , 0..Inf, default=1
      Flt thickness         ()C;   Cloth& thickness         (Flt thickness ); // get/set thickness          , 0..Inf, default=0.1
      Flt stretching        ()C;   Cloth& stretching        (Flt stretching); // get/set stretching         , 0..1  , default=0
      Flt glueVel           ()C;   Cloth& glueVel           (Flt glue_vel  ); // get/set glue velocity      , 0..Inf, default=0  , glue velocity, this feature is useful when the cloth is attached to a fast moving actor, used only when set to >0
      Flt response          ()C;   Cloth& response          (Flt response  ); // get/set response           , 0..Inf, default=0.2, 0 increases performance
      Flt attachmentResponse()C;   Cloth& attachmentResponse(Flt response  ); // get/set attachment response, 0..Inf, default=0.2, 0 increases performance
      Flt pressure          ()C;   Cloth& pressure          (Flt pressure  ); // get/set volume pressure    , 0..Inf, default=0  , 0 increases performance

      // attach
      Cloth& attach   (                                      Bool response=false                      ); // attach cloth to   actors which cloth is colliding with
      Cloth& attach   (                   Actor &actor     , Bool response=false                      ); // attach cloth to   actor, cloth must collide with actor
      Cloth& detach   (                   Actor &actor                                                ); // detach cloth from actor
      Cloth& attachVtx(Int i, C Vec &pos, Actor *actor=NULL, Bool response=false, Bool local_pos=false); // attach i-th vertex at 'pos' global position (or local position if 'local_pos'=true) to 'actor' (or world if 'actor'=NULL)
      Cloth& detachVtx(Int i                                                                          ); // detach i-th vertex

      // testing
      Bool ray(C Vec &pos, C Vec &dir, Vec *hit_pos=NULL, Int *hit_vtx=NULL)C; // test if ray cuts through the cloth, 'pos'=starting ray position, 'dir'=normalized ray direction, 'hit_pos'=optional parameter to receive the hit position, 'hit_vtx'=optional parameter to receive the vertex index

  ~Cloth() {del();}
   Cloth();

private:
   UInt       _update_count;
   Flt        _scale;
   ClothMesh *_cloth_mesh;
   UInt      *_vtxs;
   Vtx       *_vtx;
   Ptr        _cloth, _lock;
   VtxBuf     _vtx_buf;
   NO_COPY_CONSTRUCTOR(Cloth);
};
/******************************************************************************/
extern Cache<ClothMesh> ClothMeshes; // ClothMesh Cache
/******************************************************************************/

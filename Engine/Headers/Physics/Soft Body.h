/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Soft Bodies are available only in PhysX 2.

   Use 'SoftBody' to simulate soft bodies.
      'SoftBody' is similar to 'Cloth' with the exception that 'Cloth' is a surface and 'SoftBody' is a volume.

   'SoftBodyMesh' may not be deleted manually if there are still 'SoftBody' using the mesh.
      This means that the 'SoftBodyMesh' must be deleted only after deleting all 'SoftBody' using the mesh.

/******************************************************************************/
const_mem_addr struct SoftBodyMesh // Physical Soft Body Mesh, it is created from Mesh and is used to create SoftBody, !! must be stored in constant memory address !!
{
   // manage
   SoftBodyMesh& del   ();
   SoftBodyMesh& create(Mesh &mesh, Flt quality=0.3f); // create from 'mesh', 'quality'=0..1, usage of this method requires "NxTetra.dll" file located in the PhysX dll's folder

   // draw
   void drawTetra(C Color &vtx_color=WHITE, C Color &edge_color=WHITE)C; // this can be optionally called outside of Render function

   // io
   Bool save(C Str &name); // save, false on fail
   Bool load(C Str &name); // load, false on fail

  ~SoftBodyMesh() {del();}
   SoftBodyMesh();

private:
   struct Scale
   {
      Flt scale;
      Ptr mesh;
   };
   Int         poss, tetras;
   Vec        *pos;
   VecI4      *tetra;
   Memc<Scale> scales;
   Ptr         lod;
   Int         lods;
   NO_COPY_CONSTRUCTOR(SoftBodyMesh);
};
/******************************************************************************/
struct SoftBody // Physical Soft Body
{
   // manage
   SoftBody& del   ();
   Bool      create(SoftBodyMesh &mesh, C Matrix &matrix); // create from 'mesh', 'matrix'=soft body matrix where its scale determines cloth scale

   // get / set
   Box        box   (     )C;                                          // get     world space box containing the soft body
   Int        vtxs  (     )C;                                          // get     number of vertexes
   Vec        vtxPos(Int i)C;   SoftBody& vtxPos(Int i, C Vec &pos  ); // get/set i-th vertex position
   Vec        vtxVel(Int i)C;   SoftBody& vtxVel(Int i, C Vec &vel  ); // get/set i-th vertex velocity
   Byte       group (     )C;   SoftBody& group (Byte          group); // get/set collision group (0..31, default value is taken according to ACTOR_GROUP)
   Bool       sleep (     )C;   SoftBody& sleep (Bool          sleep); // get/set sleeping
   Ptr        user  (     )C;   SoftBody& user  (Ptr           user ); // get/set custom user data
   Game::Obj* obj   (     )C;   SoftBody& obj   (Game::Obj    *obj  ); // get/set pointer to game object containing the soft body

   // parameters
   Flt thickness         ()C;   SoftBody& thickness         (Flt thickness ); // get/set thickness          , 0..Inf, default=0.2
   Flt density           ()C;                                                 // get     density            , 0..Inf, default=1
   Flt bending           ()C;   SoftBody& bending           (Flt bending   ); // get/set bending            , 0..1  , default=0
   Flt stretching        ()C;   SoftBody& stretching        (Flt stretching); // get/set stretching         , 0..1  , default=0
   Flt damping           ()C;   SoftBody& damping           (Flt damping   ); // get/set damping            , 0..1  , default=0.5
   Flt friction          ()C;   SoftBody& friction          (Flt friction  ); // get/set friction           , 0..1  , default=0.5
   Flt glueVel           ()C;   SoftBody& glueVel           (Flt glue_vel  ); // get/set glue velocity      , 0..Inf, default=0  , glue velocity, this feature is useful when the soft body is attached to a fast moving actor, used only when set to >0
   Flt response          ()C;   SoftBody& response          (Flt response  ); // get/set response           , 0..Inf, default=0.2, 0 increases performance
   Flt attachmentResponse()C;   SoftBody& attachmentResponse(Flt response  ); // get/set attachment response, 0..Inf, default=0.2, 0 increases performance
   Flt particleRadius    ()C;   SoftBody& particleRadius    (Flt radius    ); // get/set particle   radius  , 0..Inf, default=0.1

   // forces
   SoftBody& addVtxForce   (Int i, C Vec &force   ); // apply 'force'    to i-th vertex
   SoftBody& addVtxImpulse (Int i, C Vec &impulse ); // apply 'impulse'  to i-th vertex
   SoftBody& addVtxVelocity(Int i, C Vec &velocity); // apply 'velocity' to i-th vertex

   SoftBody& addForce   (C Vec &pos, Flt power, Flt radius); // apply a radial force    at 'pos' world position, all vertexes within the 'radius' are affected with quadratic falloff
   SoftBody& addImpulse (C Vec &pos, Flt power, Flt radius); // apply a radial impulse  at 'pos' world position, all vertexes within the 'radius' are affected with quadratic falloff
   SoftBody& addVelocity(C Vec &pos, Flt power, Flt radius); // apply a radial velocity at 'pos' world position, all vertexes within the 'radius' are affected with quadratic falloff

   SoftBody& addDirectedForce   (C Vec &pos, C Vec &force   , Flt radius); // apply a directed force    at 'pos' world position, all vertexes within the 'radius' are affected with quadratic falloff
   SoftBody& addDirectedImpulse (C Vec &pos, C Vec &impulse , Flt radius); // apply a directed impulse  at 'pos' world position, all vertexes within the 'radius' are affected with quadratic falloff
   SoftBody& addDirectedVelocity(C Vec &pos, C Vec &velocity, Flt radius); // apply a directed velocity at 'pos' world position, all vertexes within the 'radius' are affected with quadratic falloff

   // attach
   SoftBody& attach   (                                      Bool response=false                      ); // attach soft body to   actors which soft body is colliding with
   SoftBody& attach   (                   Actor &actor     , Bool response=false                      ); // attach soft body to   actor, soft body must collide with actor
   SoftBody& detach   (                   Actor &actor                                                ); // detach soft body from actor
   SoftBody& attachVtx(Int i, C Vec &pos, Actor *actor=NULL, Bool response=false, Bool local_pos=false); // attach i-th vertex at 'pos' global position (or local position if 'local_pos'=true) to 'actor' (or world if 'actor'=NULL)
   SoftBody& detachVtx(Int i                                                                          ); // detach i-th vertex

   // testing
   Bool ray(C Vec &pos, C Vec &dir, Vec *hit_pos=NULL, Int *hit_vtx=NULL)C; // test if ray cuts through the soft body, 'pos'=starting ray position, 'dir'=normalized ray direction, 'hit_pos'=optional parameter to receive the hit position, 'hit_vtx'=optional parameter to receive the vertex index

   // draw
   void drawTetra (C Color &vtx_color=WHITE, C Color &edge_color=WHITE)C; // this can be optionally called outside of Render function
   void draw      ()C; // automatically uses Frustum culling, this can be called only in RM_PREPARE
   void drawShadow()C; // automatically uses Frustum culling, this can be called only in RM_SHADOW

  ~SoftBody() {del ( );}
   SoftBody() {Zero(T);}

private:
   Ptr           soft_body;
   Flt           scale;
   UInt         *poss;
   Vec          *pos;
   SoftBodyMesh *mesh;
   Ptr           lod;
   NO_COPY_CONSTRUCTOR(SoftBody);
};
/******************************************************************************/
extern Cache<SoftBodyMesh> SoftBodyMeshes; // SoftBodyMesh Cache
/******************************************************************************/

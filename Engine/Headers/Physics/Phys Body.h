/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'PhysBody' as a physical body description, to create 'Actors' from it.

/******************************************************************************/
enum PHYS_TYPE // Physical Body Type
{
   PHYS_NONE  , // none
   PHYS_SHAPE , // shape
   PHYS_CONVEX, // convex
   PHYS_MESH  , // mesh, actor created from this type can be only static
};
/******************************************************************************/
struct PhysPart // Physical Body Part, contains a single Shape/Convex/Mesh, can be used to create actors from it
{
   Flt   density; // mass density multiplier, 0..Inf
   Shape shape  ; // geometric shape

   // manage
   PhysPart& del   (                                 );                                          // delete
   PhysPart& create(C Box     &box    , Flt density=1) {return create(Shape(box    ), density);} // create as box     with 'density'
   PhysPart& create(C OBox    &obox   , Flt density=1) {return create(Shape(obox   ), density);} // create as obox    with 'density'
   PhysPart& create(C Ball    &ball   , Flt density=1) {return create(Shape(ball   ), density);} // create as ball    with 'density'
   PhysPart& create(C Capsule &capsule, Flt density=1) {return create(Shape(capsule), density);} // create as capsule with 'density'
   PhysPart& create(C Tube    &tube   , Flt density=1) {return create(Shape(tube   ), density);} // create as tube    with 'density'
   PhysPart& create(C Shape   &shape  , Flt density=1);                                          // create as shape   with 'density'

   Bool      createConvexTry(MeshBase &mshb, Flt density=1, Bool mesh_is_already_convex=false); // create as convex body with 'density', false on fail, if 'mesh_is_already_convex' is set to true then the mesh is assumed to be already convex which will make the creation faster, this method can sometimes fail if the mesh is too complex, in that case you can create a temporary mesh using MeshBase::createConvex, specify vertex limit and use that mesh for phys body creation
   Bool      createConvexTry(MeshLod  &mshl, Flt density=1, Bool mesh_is_already_convex=false); // create as convex body with 'density', false on fail, if 'mesh_is_already_convex' is set to true then the mesh is assumed to be already convex which will make the creation faster, this method can sometimes fail if the mesh is too complex, in that case you can create a temporary mesh using MeshBase::createConvex, specify vertex limit and use that mesh for phys body creation
   PhysPart& createConvex   (MeshBase &mshb, Flt density=1, Bool mesh_is_already_convex=false); // create as convex body with 'density', Exit  on fail, if 'mesh_is_already_convex' is set to true then the mesh is assumed to be already convex which will make the creation faster, this method can sometimes fail if the mesh is too complex, in that case you can create a temporary mesh using MeshBase::createConvex, specify vertex limit and use that mesh for phys body creation
   PhysPart& createConvex   (MeshLod  &mshl, Flt density=1, Bool mesh_is_already_convex=false); // create as convex body with 'density', Exit  on fail, if 'mesh_is_already_convex' is set to true then the mesh is assumed to be already convex which will make the creation faster, this method can sometimes fail if the mesh is too complex, in that case you can create a temporary mesh using MeshBase::createConvex, specify vertex limit and use that mesh for phys body creation

   Bool      createMeshTry(MeshBase &mshb, Bool keep_face_indexes=false); // create as static mesh, 'keep_face_indexes'=if preserve original face indexes in the 'PhysHit.face' (when enabled this will use additional memory, when disabled the face index will point to the internal face of the physical body but not the original face of the source mesh), false on fail
   Bool      createMeshTry(MeshLod  &mshl, Bool keep_face_indexes=false); // create as static mesh, 'keep_face_indexes'=if preserve original face indexes in the 'PhysHit.face' (when enabled this will use additional memory, when disabled the face index will point to the internal face of the physical body but not the original face of the source mesh), false on fail
   PhysPart& createMesh   (MeshBase &mshb, Bool keep_face_indexes=false); // create as static mesh, 'keep_face_indexes'=if preserve original face indexes in the 'PhysHit.face' (when enabled this will use additional memory, when disabled the face index will point to the internal face of the physical body but not the original face of the source mesh), Exit  on fail
   PhysPart& createMesh   (MeshLod  &mshl, Bool keep_face_indexes=false); // create as static mesh, 'keep_face_indexes'=if preserve original face indexes in the 'PhysHit.face' (when enabled this will use additional memory, when disabled the face index will point to the internal face of the physical body but not the original face of the source mesh), Exit  on fail

   // get
   Bool      is    (        )C {return _type!=PHYS_NONE;} // if  part body has any data
   PHYS_TYPE type  (        )C {return _type           ;} // get part body type
   Flt       area  (        )C;                           // get surface area, this method works only for PHYS_SHAPE types
   Flt       volume(        )C;                           // get volume      , this method works only for PHYS_SHAPE types
   Flt       mass  (        )C {return density*volume();} // get mass        , this method works only for PHYS_SHAPE types
   Bool      getBox(Box &box)C;                           // get bounding box surrounding the body, false on fail

   // operations
   Bool      adjustStorage (Bool universal, Bool physx, Bool bullet, Bool *changed=NULL); // adjust the type of storage for the physical body, 'universal'=can be used for both PhysX and Bullet, 'physx'=can be used for PhysX (and when used there it is faster than 'universal'), 'bullet'=can be used for Bullet (and when used there it is faster than 'universal'), each storage uses additional space, for PhysX only games it is suggested to set 'physx' to true and others to false, for Bullet only games it is suggested to set 'bullet' to true and others to false, please note if you call this method under engine compiled with Bullet library, you won't be able to create PhysX data, 'changed'=pointer to custom bool which will be set to true if any change has been performed on the physical body (false otherwise), false on fail
   PhysPart& freeHelperData(                                                           ); // this free's up the helper data of the physical body, which increases available memory, however it disables saving the body to file, or converting it to 'MeshBase'

   PhysPart& transform (C Matrix3 &matrix);                            // transform by matrix
   PhysPart& transform (C Matrix  &matrix);                            // transform by matrix
   PhysPart& operator*=(C Matrix3 &matrix) {return transform(matrix);} // transform by matrix
   PhysPart& operator*=(C Matrix  &matrix) {return transform(matrix);} // transform by matrix

   // draw
   void draw(C Color &color)C; // this can be optionally called outside of Render function

   // io
   void operator=(C Str  &name) ; // load, Exit  on fail
   Bool save     (C Str  &name)C; // save, false on fail
   Bool load     (C Str  &name) ; // load, false on fail
   void save     (  File &f   )C; // save
   Bool load     (  File &f   ) ; // load, false on fail

            PhysPart& operator=(C PhysPart &src); // create from 'src'
           ~PhysPart() {del();}
            PhysPart();
   explicit PhysPart(C Box     &box    , Flt density=1); // create box
   explicit PhysPart(C OBox    &obox   , Flt density=1); // create obox
   explicit PhysPart(C Ball    &ball   , Flt density=1); // create ball
   explicit PhysPart(C Capsule &capsule, Flt density=1); // create capsule
   explicit PhysPart(C Tube    &tube   , Flt density=1); // create tube
   explicit PhysPart(C Shape   &shape  , Flt density=1); // create shape

private:
   PHYS_TYPE _type;
   Ptr       _pm;
   PhysPart(C PhysPart&);
};
/******************************************************************************/
struct PhysBody // Physical Body (array of PhysPart's), can be used to create actors from it
{
   Flt            density ; // mass density multiplier, 0..Inf, default=1
   Box            box     ; // bounding box surrounding the body
   PhysMtrl      *material; // physical material              , default=NULL
   Mems<PhysPart> parts   ; // physical body parts

   // manage
   PhysBody& del(); // delete

   // get
   Bool is          ()C {return parts.elms()>0;} // if has any data
   Flt  area        ()C; // get surface area of all parts, this method works only for PHYS_SHAPE types
   Flt  volume      ()C; // get volume       of all parts, this method works only for PHYS_SHAPE types
   Flt  mass        ()C; // get mass         of all parts, this method works only for PHYS_SHAPE types
   Flt  finalDensity()C; // get density of PhysBody including material -> "density * material.density"

   // operations
   Bool      adjustStorage (Bool universal, Bool physx, Bool bullet, Bool *changed=NULL); // adjust the type of storage for the physical body, 'universal'=can be used for both PhysX and Bullet, 'physx'=can be used for PhysX (and when used there it is faster than 'universal'), 'bullet'=can be used for Bullet (and when used there it is faster than 'universal'), each storage uses additional space, for PhysX only games it is suggested to set 'physx' to true and others to false, for Bullet only games it is suggested to set 'bullet' to true and others to false, please note if you call this method under engine compiled with Bullet library, you won't be able to use any PhysX information (which means converting from or to PhysX storage), 'changed'=pointer to custom bool which will be set to true if any change has been performed on the physical body (false otherwise), false on fail
   Bool      setBox        (                                                           ); // recalculate bounding box, false on fail
   PhysBody& freeHelperData(                                                           ); // this free's up the helper data of the physical body, which increases available memory, however it disables saving the body to file, or converting it to 'MeshBase'

   PhysBody& transform (C Matrix3 &matrix);                            // transform by matrix
   PhysBody& transform (C Matrix  &matrix);                            // transform by matrix
   PhysBody& operator*=(C Matrix3 &matrix) {return transform(matrix);} // transform by matrix
   PhysBody& operator*=(C Matrix  &matrix) {return transform(matrix);} // transform by matrix

   // draw
   void draw(C Color &color)C; // this can be optionally called outside of Render function

   // io
   void operator=(C Str  &name) ; // load, Exit  on fail
   Bool save     (C Str  &name)C; // save, false on fail
   Bool load     (C Str  &name) ; // load, false on fail

   void save     (File &f, CChar *path=NULL)C; // save, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path)
   Bool load     (File &f, CChar *path=NULL) ; // load, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail
   Bool loadAdd  (File &f, CChar *path=NULL) ; // load, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail, this method adds the data from file to self (not replaces it)

   PhysBody();
};
/******************************************************************************/
struct PhysGroup // Physical Body Group (array of PhysBodies)
{
   Mems<PhysBody> bodies; // physical bodies

   // manage
   PhysGroup& del   (               ); // delete
   PhysGroup& create(MeshLod   &mshl); // create from MeshLod
   PhysGroup& create(MeshGroup &mshg); // create from MeshGroup

   // io
   void operator=(C Str  &name) ; // load, Exit  on fail
   Bool save     (C Str  &name)C; // save, false on fail
   Bool load     (C Str  &name) ; // load, false on fail
   void save     (  File &f   )C; // save
   Bool load     (  File &f   ) ; // load, false on fail
};
/******************************************************************************/
DECLARE_CACHE(PhysBody, PhysBodies, PhysBodyPtr); // 'PhysBodies' cache storing 'PhysBody' objects which can be accessed by 'PhysBodyPtr' pointer

inline Int Elms(C PhysBody  &phys) {return phys.parts .elms();}
inline Int Elms(C PhysGroup &phsg) {return phsg.bodies.elms();}
/******************************************************************************/

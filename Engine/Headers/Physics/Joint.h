/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Joint' to link 2 actors together, or one actor to fixed position in world.

/******************************************************************************/
struct Spring
{
   Flt spring, damping;

   Spring(Flt spring=0, Flt damping=0) {T.spring=spring; T.damping=damping;}
};
/******************************************************************************/
struct Joint // a Joint between 2 actors, or one actor and fixed position in world
{
   // manage
   Joint& del            (                                                                                                                 ); // delete manually
   Joint& create         (Actor &a0, Actor *a1                                                                                             ); // create default   joint
   Joint& createHinge    (Actor &a0, Actor *a1, C Vec &anchor , C Vec &axis   ,                                        Bool collision=false); // create hinge     joint, 'anchor'=world space anchor position, 'axis'=world space joint axis, 'collision'=if allow for collisions between 'a0' and 'a1'
   Joint& createHinge    (Actor &a0, Actor *a1, C Vec &anchor , C Vec &axis   , Flt min_angle   , Flt max_angle      , Bool collision=false); // create hinge     joint, 'anchor'=world space anchor position, 'axis'=world space joint axis, 'collision'=if allow for collisions between 'a0' and 'a1'
   Joint& createSpherical(Actor &a0, Actor *a1, C Vec &anchor , C Vec &axis   , Flt *swing=NULL , Flt *twist=NULL    , Bool collision=false); // create spherical joint, 'anchor'=world space anchor position, 'axis'=world space joint axis, 'swing'=maximum allowed swing angle rotation (0..PI) NULL for no limits, 'twist'=maximum allowed twist angle rotation (0..PI) NULL for no limits
   Joint& createSliding  (Actor &a0, Actor *a1, C Vec &anchor , C Vec &dir    , Flt min, Flt max                     , Bool collision=false); // create sliding   joint, 'anchor'=world space anchor position, 'dir' =world space sliding direction, 'min'=minumum allowed distance along 'dir' (-Inf..'max'), 'max'=maximum allowed distance along 'dir' ('min'..Inf)
   Joint& createDist     (Actor &a0, Actor *a1, C Vec &anchor0, C Vec &anchor1, Flt min, Flt max, Spring *spring=NULL, Bool collision=false); // create distance based joint, here 'anchor0 anchor1' are in local spaces of actors

   Joint& createBodyHinge    (Actor &bone, Actor &parent, C Vec &anchor, C Vec &axis, Flt min_angle, Flt max_angle); // create body hinge     joint, 'anchor'=world space anchor position, 'axis'=world space joint axis, 'collision'=if allow for collisions between 'a0' and 'a1'
   Joint& createBodySpherical(Actor &bone, Actor &parent, C Vec &anchor, C Vec &axis, Flt swing    , Flt twist    ); // create body spherical joint, 'anchor'=world space anchor position, 'axis'=world space joint axis, 'swing'=maximum allowed swing angle rotation (0..PI), 'twist'=maximum allowed twist angle rotation (0..PI)

   // get / set
   Bool   is       (                             )C {return _joint!=NULL;} // if  created
   Bool   broken   (                             )C;                       // if  joint is broken
   Joint& breakable(Flt max_force, Flt max_torque) ;                       // set breakable parameters, if forces applied to the joint will exceed given parameters the joint will break (use <0 values for non-breakable joint)

   // io
   void save(File &f                      )C; // save, does not save information about which actors are joined
   Bool load(File &f, Actor &a0, Actor *a1) ; // load, 'a0' and 'a1' are actors which the joint should link, false on fail

  ~Joint() {del();}
   Joint() {_joint=NULL;}

private:
   Ptr _joint;
   NO_COPY_CONSTRUCTOR(Joint);
};
/******************************************************************************/

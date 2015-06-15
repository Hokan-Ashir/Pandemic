/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use         'Skeleton' as         a base static (non-animated) skeleton, that contain bones and points in their initial pose.
   Use 'AnimatedSkeleton' to animate a base static 'Skeleton', by applying 'Animation's on the 'AnimatedSkeleton'.

/******************************************************************************/
// STATIC SKELETON
/******************************************************************************/
enum BONE_FLAG
{
   BONE_RAGDOLL=1<<0, // if this option is enabled then the bone will be used to create an actor in the Ragdoll
};

typedef SkeletonBone SkelBone;
STRUCT( SkeletonBone , OrientP) // Skeleton Bone
//{
   Char8   name[32]       ; // name                                , default=""
   Byte    parent         , // bone parent index                   , default=0xFF, 0xFF=none
           children_offset, // offset of children on Skeleton.bones,
           children_num   , // number of children
           flag           ; // BONE_FLAG                           , default=0
   Flt     length         , // bone length                         , default=0.3
           width          , // bone width                          , default=0.2
           frac           ; // bone fraction                       , default=0.3
   Vec     offset         ; // bone offset applied to 'shape'      , default=(0, 0, 0)
   Capsule shape          ; // shape covering the bone, automatically set by 'Skeleton.setBoneShapes' method depending on bone position, orientation, length, width and being ragdoll bone

   // get
   Vec     to()C {return pos+dir* length      ;} // get bone ending position
   Vec center()C {return pos+dir*(length*0.5f);} // get bone center position

   // set
   SkeletonBone& setFromTo(C Vec &from, C Vec &to); // set bone position, direction and length according to 'from' and 'to' position parameters and adjust existing 'perp' to match the new settings

   SkeletonBone& operator+=(C Vec     &v);
   SkeletonBone& operator-=(C Vec     &v);
   SkeletonBone& operator*=(C Vec     &v);
   SkeletonBone& operator*=(C Matrix3 &m);
   SkeletonBone& operator/=(C Matrix3 &m);
   SkeletonBone& operator*=(C Matrix  &m);
   SkeletonBone& operator/=(C Matrix  &m);
   SkeletonBone  operator* (C Matrix  &m) {return SkeletonBone(T)*=m;}

   // draw
   void draw(C Color &color)C; // this can be optionally called outside of Render function

   // io
   void save(TextNode &node, C Skeleton *owner=NULL)C; // save as text

   SkeletonBone();
};

typedef SkeletonPoint SkelPoint;
STRUCT( SkeletonPoint , OrientP) // Skeleton Point
//{
   Char8 name[32]; // name
   Byte  bone    ; // bone index to which point belongs, 0xFF=none

   // io
   void save(TextNode &node, C Skeleton *owner=NULL)C; // save as text

   SkeletonPoint();
};
/******************************************************************************/
struct Skeleton // Animation Skeleton - base skeleton used by 'AnimatedSkeleton'
{
   Mems<SkelBone > bones ; // skeleton bones
   Mems<SkelPoint> points; // skeleton points

   // get
   Bool is()C {return bones.elms() || points.elms();} // if has any data

   Int        findBoneI (CChar8 *name)C; // find bone  index    , -1   on fail
   Int        findPointI(CChar8 *name)C; // find point index    , -1   on fail
   SkelBone * findBone  (CChar8 *name) ; // find bone  pointer  , NULL on fail
   SkelPoint* findPoint (CChar8 *name) ; // find point pointer  , NULL on fail
   Int         getBoneI (CChar8 *name)C; // get  bone  index    , Exit on fail
   Int         getPointI(CChar8 *name)C; // get  point index    , Exit on fail
   SkelBone &  getBone  (CChar8 *name) ; // get  bone  reference, Exit on fail
   SkelPoint&  getPoint (CChar8 *name) ; // get  point reference, Exit on fail

   Bool contains     (Int parent, Int child)C; // if 'parent' bone contains 'child' bone
   Int  ragdollParent(Int bone             )C; // get index of the first parent of 'bone' which has 'BONE_RAGDOLL' enabled, -1 is returned if none were found

   UInt memUsage()C; // get memory usage

   // transform
   Skeleton& move     (                           C Vec &move); // move
   Skeleton& scale    (C Vec              &scale             ); // scale
   Skeleton& scaleMove(C Vec              &scale, C Vec &move); // scale and move
   Skeleton& transform(C Matrix3          &matrix            ); // transform by matrix
   Skeleton& transform(C Matrix           &matrix            ); // transform by matrix
   Skeleton& animate  (C AnimatedSkeleton &anim_skel         ); // transform bones according to current 'anim_skel' skeleton pose

   // operations
   Skeleton& setBoneShapes(); // automatically set 'SkelBone.shape' for all bones in this Skeleton, this method should be called after making changes to skeleton bones
   Skeleton& setBoneParent(Int child, Int parent, Memp<Byte> old_to_new=NULL); // set 'parent' as the parent of 'child' bone, if 'old_to_new' is passed it will be set as bone remap "old_to_new[old_index]=new_index"
   Skeleton& removeBone   (Int i    ,             Memp<Byte> old_to_new=NULL); // remove i-th bone                          , if 'old_to_new' is passed it will be set as bone remap "old_to_new[old_index]=new_index"
   Skeleton& add          (C Skeleton &src      , Memp<Byte> old_to_new=NULL); // add bones and points from 'src' to self   , if 'old_to_new' is passed it will be set as bone remap "old_to_new[old_index]=new_index"

   Skeleton& operator+=(C Vec      &move  ) {return T.move     (move  );} // move
   Skeleton& operator*=(C Matrix3  &matrix) {return T.transform(matrix);} // transform by matrix
   Skeleton& operator*=(C Matrix   &matrix) {return T.transform(matrix);} // transform by matrix
   Skeleton& operator =(C Skeleton &src   ); // create from 'src'

   // draw
   void draw(C Color &bone_color, C Color &point_color=TRANSPARENT, Flt point_size=0.2f)C; // draw bones and points, this can be optionally called outside of Render function

   // io
   void operator=(C Str &name) ; // load, Exit  on fail
   Bool save     (C Str &name)C; // save, false on fail
   Bool load     (C Str &name) ; // load, false on fail

   void save(File &f)C; // save
   Bool load(File &f) ; // load, false on fail

   void save(Memp<TextNode> nodes)C; // save as text

   Skeleton& del(); // delete manually
   Skeleton();

private:
   Cache<SkelAnim> _skel_anim;
   Skeleton(C Skeleton&);
};
/******************************************************************************/
// ANIMATED SKELETON
/******************************************************************************/
typedef AnimatedSkeletonBone AnimSkelBone;
struct  AnimatedSkeletonBone // Bone of an Animated Skeleton
{
   // these parameters may be manually changed during animation process, they are in parent space:
   Orient   orn  ; // target   orientation
   AxisRoll rot  ; // relative rotation
   Vec      pos  , // offset   position
            scale; // scale    factor
   Vec4     color; // color

   // these parameters may be accessed after animation and matrix updates (using 'updateMatrix' method), they are in world space:
 C Vec   & center()C {return _center;} // bone center position, this parameter may be inaccurate for bones which don't have BONE_RAGDOLL flag enabled
 C Vec   & vel   ()C {return _vel   ;} // bone velocity       , this parameter may be inaccurate for bones which don't have BONE_RAGDOLL flag enabled
 C Matrix& matrix()C {return _matrix;} // this is the transformation matrix, which transforms source bone 'SkelBone' and source 'Mesh' into their final positions (source_data * matrix = final_world_space_position)

   // operations
   void clear(         ); //           clear 'orn rot pos scale color'
   void clear(Flt blend); // partially clear 'orn rot pos scale color', this method is similar to 'clear()' however it does not perform full reset of the bone. Instead, smooth reset is applied depending on 'blend' value (0=no reset, 1=full reset)

   void forceMatrix(C Matrix &matrix); // force usage of custom transformation 'matrix' for this bone, if used then the bone will ignore its transformations from the animations

private:
   Bool   _disabled, _disabled_children, _force_custom, _world_space_transform;
   Vec    _center, _vel, _fur_vel;
   Matrix _matrix, _force_custom_matrix, _world_space_transform_matrix;
};
/******************************************************************************/
typedef AnimatedSkeleton AnimSkel;
struct  AnimatedSkeleton // Animated Skeleton - used for animating meshes
{
   Flt                     fur_stiffness, // determines the speed of                fur velocities changing,    0..1  , default= 0.0001
                           fur_gravity  , // gravity which affects                  fur velocities         , -Inf..Inf, default=-1
                           fur_vel_scale; // how much does skeleton movement affect fur velocities         , -Inf..Inf, default=-0.75
             AnimSkelBone  root         ; // root transformed skeleton bone
   FixedMems<AnimSkelBone> bones        ; //      transformed skeleton bone  array
   FixedMems<OrientP     > points       ; //      transformed skeleton point array

   // manage
   AnimatedSkeleton& del   (                                                                                       ); // delete manually
   AnimatedSkeleton& create(const_mem_addr Skeleton *skeleton, Flt scale=1, C Matrix &initial_matrix=MatrixIdentity); // create from 'skeleton' object, 'scale'=skeleton scale, 'initial_matrix'=matrix set for the root bone (its scale is ignored)
   AnimatedSkeleton& create(       AnimatedSkeleton &src                                                           ); // create from 'src'

   // get
   Skeleton*     skeleton(     )C {return _skeleton                          ;} // get source   skeleton
   Flt           scale   (     )C {return _scale                             ;} // get animated skeleton scale
   AnimSkelBone& boneRoot(Int i)  {return InRange(i, bones) ? bones[i] : root;} // get i-th transformed bone or root if index is out of range
 C Vec   &       pos     (     )C {return root.matrix().pos                  ;} // get body position
 C Matrix&       matrix  (     )C {return root.matrix()                      ;} // get body matrix
 C Vec   &       vel     (     )C {return root.vel   ()                      ;} // get body velocity

   SkelAnim*     findSkelAnim(C Str  &name)C; // find skeleton    animation, NULL on fail
   SkelAnim*     findSkelAnim(C UID  &id  )C; // find skeleton    animation, NULL on fail
   Int           findBoneI   (CChar8 *name)C; // find bone        index    , -1   on fail
   Int           findPointI  (CChar8 *name)C; // find point       index    , -1   on fail
   AnimSkelBone* findBone    (CChar8 *name) ; // find bone                 , NULL on fail
   OrientP     * findPoint   (CChar8 *name) ; // find transformed point    , NULL on fail, point will have correct orientation after 'updateMatrix' has been called
   SkelAnim*      getSkelAnim(C Str  &name)C; // get  skeleton    animation, Exit on fail
   SkelAnim*      getSkelAnim(C UID  &id  )C; // get  skeleton    animation, Exit on fail
   Int            getBoneI   (CChar8 *name)C; // get  bone        index    , Exit on fail
   Int            getPointI  (CChar8 *name)C; // get  point       index    , Exit on fail
   AnimSkelBone*  getBone    (CChar8 *name) ; // get  bone                 , Exit on fail
   OrientP     *  getPoint   (CChar8 *name) ; // get  transformed point    , Exit on fail, point will have correct orientation after 'updateMatrix' has been called

   // set
   AnimatedSkeleton& disable        (Int i, Bool disable); // disables/enables animation of i-th bone
   AnimatedSkeleton& disableChildren(Int i, Bool disable); // disables/enables animation of i-th bone's children

   // animate
      // prepare
      AnimatedSkeleton& clear(         ); //           clear 'AnimSkelBone' bones 'orn rot pos scale color', call this method once before applying all animations to prepare for animating
      AnimatedSkeleton& clear(Flt blend); // partially clear 'AnimSkelBone' bones 'orn rot pos scale color',      this method is similar to 'clear()' however it does not perform full reset of the bones. Instead, smooth reset is applied depending on 'blend' value (0=no reset, 1=full reset)

      // modify using animations
      AnimatedSkeleton& animate(C SkelAnim &skel_anim, Flt time, Flt blend=1, Bool replace=false); // modify 'AnimSkelBone' bones 'orn rot pos scale color' according to animation object      , 'time'=time position of the animation, 'blend'=blending factor of animation (0..1), if 'replace'=true then previous animations applied to the skeleton will be multiplied by "1-blend" value making them less important
      AnimatedSkeleton& animate(C SkelAnim *skel_anim, Flt time, Flt blend=1, Bool replace=false); // modify 'AnimSkelBone' bones 'orn rot pos scale color' according to animation object      , 'time'=time position of the animation, 'blend'=blending factor of animation (0..1), if 'replace'=true then previous animations applied to the skeleton will be multiplied by "1-blend" value making them less important
      AnimatedSkeleton& animate(C Str      &anim_name, Flt time, Flt blend=1, Bool replace=false); // modify 'AnimSkelBone' bones 'orn rot pos scale color' according to animation file name   , 'time'=time position of the animation, 'blend'=blending factor of animation (0..1), if 'replace'=true then previous animations applied to the skeleton will be multiplied by "1-blend" value making them less important
      AnimatedSkeleton& animate(C UID      &anim_id  , Flt time, Flt blend=1, Bool replace=false); // modify 'AnimSkelBone' bones 'orn rot pos scale color' according to animation file name id, 'time'=time position of the animation, 'blend'=blending factor of animation (0..1), if 'replace'=true then previous animations applied to the skeleton will be multiplied by "1-blend" value making them less important
      AnimatedSkeleton& animate(C Motion   &motion   ,                        Bool replace      ); // modify 'AnimSkelBone' bones 'orn rot pos scale color' according to animation motion      ,                                                                                     if 'replace'=true then previous animations applied to the skeleton will be multiplied by "1-blend" value making them less important

      // build final transformation matrixes (this takes into account applied animations and custom modifications)
      AnimatedSkeleton& updateMatrix        (C Matrix &body_matrix          ); // update 'AnimSkelBone' bones 'matrix' according to bones 'orn rot pos scale' and 'body_matrix', this should be called after animating and applying manual modifications, 'body_matrix' must be normalized, this method also sets skeleton points according to bone matrixes
      AnimatedSkeleton& updateMatrixParents (C Matrix &body_matrix, Int bone); // update 'AnimSkelBone' bones 'matrix' according to bones 'orn rot pos scale' and 'body_matrix', update occurs only on 'bone' bone and its parents                      , 'body_matrix' must be normalized
      AnimatedSkeleton& updateMatrixChildren(                       Int bone); // update 'AnimSkelBone' bones 'matrix' according to bones 'orn rot pos scale'                  , update occurs only on 'bone' bone and its children

      // apply custom modifications (this can be called before or after 'updateMatrix' methods)
      AnimatedSkeleton&           forceMatrix(Int bone, C Matrix  &matrix, Bool auto_update_matrixes=true); // force usage of custom transformation 'matrix' for 'bone', if used then the bone will ignore its transformations from the animations, if 'auto_update_matrixes' is set to true then 'updateMatrixChildren(bone)' will be called automatically
      AnimatedSkeleton& transformInWorldSpace(Int bone, C Matrix3 &matrix, Bool auto_update_matrixes=true); // transform bone by world space 'matrix', if 'auto_update_matrixes' is set to true then 'updateMatrixChildren(bone)' will be called automatically
      AnimatedSkeleton& transformInWorldSpace(Int bone, C Matrix  &matrix, Bool auto_update_matrixes=true); // transform bone by world space 'matrix', if 'auto_update_matrixes' is set to true then 'updateMatrixChildren(bone)' will be called automatically

   // update
   void updateVelocities(Bool according_to_physics_step=true, Bool ragdoll_bones_only=true); // update velocities 'vel, bone.vel' and bone center positions 'bone.center' according to body and bone matrixes 'matrix bone[].matrix'. This needs to be called once per frame after all animations, modifications and matrix updates ('updateMatrix'). 'according_to_physics_step' if update the velocities according to the physics update time step in this frame, if it's set to false, then the velocities will always be calculated. 'ragdoll_bones_only'=if calculate precise velocities only for bones which have 'BONE_RAGDOLL' flag enabled

   // transform
   void move  (C Vec &delta); // move the whole skeleton                                                     , this method is to be used for distant      position modifications, it will not affect bone velocities, you can call this method optionally after matrix updates ('updateMatrix')
   void offset(C Vec &delta); // apply offset to body matrix, bone matrixes, and transformed points by vector, this method is to be used for smooth local position modifications, it will     affect bone velocities, you can call this method optionally after matrix updates ('updateMatrix')

   // draw
   void setMatrix()C; // set active rendering matrixes and velocities ('matrix, bone.matrix, vel, bone.vel') to the GPU shader data, call this right before drawing skinned meshes (when using mesh draw methods which don't accept matrix or skeleton parameter, if they do accept such parameters, then those methods will automatically set proper matrixes and you don't need to call 'setMatrix' manually)
   void draw     (C Color &bone_color, C Color &point_color=TRANSPARENT)C; // draw animated bones and points, this can be optionally called outside of Render function

   // io
   void save(File &f)C; // save, does not include current animation pose
   Bool load(File &f) ; // load, does not include current animation pose, false on fail

   AnimatedSkeleton();

private:
   Bool      _update_vel_temp;
   Flt       _scale;
   Skeleton *_skeleton;
   struct Instance
   {
      Int solid, ambient, blend, shadow;
      Instance() {solid=ambient=blend=shadow=-1;}
   }_instance;
};
/******************************************************************************/
struct BoneMap
{
   void       del();
  ~BoneMap() {del();}
   BoneMap() {_bone=NULL; _bones=0;}

private:
   Ptr _bone;
   Int _bones;
   BoneMap(C BoneMap &);
};
/******************************************************************************/
extern Cache<Skeleton> Skeletons; // Skeleton Cache
/******************************************************************************/

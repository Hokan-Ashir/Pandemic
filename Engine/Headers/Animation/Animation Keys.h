/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'AnimationKeys' to store animation keys:
      -target   orientation
      -relative rotation
      -offset   position
      -scale

/******************************************************************************/
typedef AnimationKeys AnimKeys;
struct  AnimationKeys // Animation Keys - set of animation keyframes for a single bone
{
   struct Orn // Target Orientation
   {
      Flt    time; // time position (seconds)
      Orient orn , // orientation
             tan ; // tangent
   };
   struct Rot // Relative Rotation
   {
      Flt      time; // time position (seconds)
      AxisRoll rot , // rotation
               tan ; // tangent
   };
   struct Pos // Offset Position
   {
      Flt time; // time position (seconds)
      Vec pos , // position offset
          tan ; // tangent
   };
   struct Scale // Scale
   {
      Flt time ; // time position (seconds)
      Vec scale, // scale factor
          tan  ; // scale tangent
   };
   struct Color // Color
   {
      Flt  time ; // time  position (seconds)
      Vec4 color, // color value
           tan  ; // color tangent
   };

   Mems<Orn  > orns;
   Mems<Rot  > rots;
   Mems<Pos  > poss;
   Mems<Scale> scales;
   Mems<Color> colors;

   // get
   Bool is()C {return orns.elms() || rots.elms() || poss.elms() || scales.elms() || colors.elms();} // if has any keys

   // convert
   AnimKeys& convertRotToOrn(C Skeleton &skeleton, Int skel_bone_index, Bool looped); // convert relative  rotations to target orientations according to given 'skeleton', 'skel_bone_index'=index of skeleton bone to which this keys belong to (-1=root bone), 'looped'=if animation is looped
   AnimKeys& convertOrnToRot(C Skeleton &skeleton, Int skel_bone_index, Bool looped); // convert target orientations to relative  rotations according to given 'skeleton', 'skel_bone_index'=index of skeleton bone to which this keys belong to (-1=root bone), 'looped'=if animation is looped

   // operations
   AnimKeys& scaleTime  (Flt  scale                                                                                                                     ); // scale time positions of keyframes "each frame time *= scale"
   AnimKeys& slideTime  (Flt  dt, Flt anim_length                                                                                                       ); // slide time positions of keyframes
   AnimKeys& reverse    (         Flt anim_length                                                                                                       ); // reverse animation
   AnimKeys& sortFrames (                                                                                                                               ); // sort frames in time order, this should be called after manually modifying the keyframes and changing their time positions
   AnimKeys& setTangents(Bool looped                                                                                                                    ); // recalculate tangents, 'looped'=if animation is looped
   AnimKeys& optimize   (Flt  angle_eps=EPSA, Flt pos_eps=EPSL, Flt scale_eps=EPSL, Flt color_eps=0.01f, C Orient *bone=NULL, C Orient *bone_parent=NULL); // optimize animation by removing similar keyframes, 'angle_eps'=angular epsilon 0..PI, 'pos_eps'=position epsilon 0..Inf, 'scale_eps'=scale epsilon 0..Inf, 'color_eps'=color epsilon 0..1, 'bone'=un-transformed orientation of skeleton bone (if specified then it will be used to check if orientation keyframe can be removed if there's only one), 'bone_parent'=un-transformed orientation of skeleton bone parent
   AnimKeys& clip       (Flt  start_time    , Flt end_time    , Bool looped       , Bool linear                                                         ); // clip animation to 'start_time' .. 'end_time', this will remove all keyframes which aren't located in selected range, 'looped'=if animation is looped, 'linear'=if animation is linear

   AnimKeys& del(); // delete manually
};
/******************************************************************************/

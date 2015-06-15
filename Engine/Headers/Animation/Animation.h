/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'AnimBone'  to store animation keys for a particular bone.
   Use 'AnimEvent' to store information about a custom event in the animation at a custom time moment.
   Use 'Animation' to store body animation keys, animation keys for multiple bones, and events.
   Use 'SkelAnim'  to handle the relation between a skeleton and an animation.

/******************************************************************************/
STRUCT(AnimBone , AnimKeys) // Animation Bone - set of animation keyframes for a particular bone
//{
   Char8 name[32]; // bone name

   void save(TextNode &node)C; // save as text

   AnimBone() {name[0]=0;}
};
/******************************************************************************/
struct AnimEvent // Animation Event - custom event which occurs at 'time' in 'Animation'
{
   Char8 name[32]; // name of the event
   Flt   time    ; // time position when the event occurs

   AnimEvent& set(C Str8 &name, Flt time) {Set(T.name, name); T.time=time; return T;}

   void save(TextNode &node)C; // save as text

   AnimEvent() {name[0]=0; time=0;}
};
/******************************************************************************/
enum ANIM_FLAG // Animation Flags
{
   ANIM_LINEAR=0x1, // linear (without smoothing)
   ANIM_LOOP  =0x2, // looped
};
/******************************************************************************/
struct Animation // set of animation keyframes used for animating 'AnimatedSkeleton'
{
   Mems<AnimBone>  bones ; // bone animations
   Mems<AnimEvent> events; // animation events
   AnimKeys        keys  ; // animation keys of the whole body

   // get / set
   Bool is()C {return bones.elms() || events.elms() || keys.is();} // if has any data

   Int       findBoneI(CChar8 *name)C; // find bone animation index, -1   on fail
   AnimBone* findBone (CChar8 *name) ; // find bone animation      , NULL on fail
   AnimBone&  getBone (CChar8 *name) ; // get  bone animation      , creates new bone animation if not found

   Animation& loop  (Bool loop                          );   Bool loop  ()C {return FlagTest(_flag, ANIM_LOOP  );} // set/get looping
   Animation& linear(Bool linear                        );   Bool linear()C {return FlagTest(_flag, ANIM_LINEAR);} // set/get linear smoothing (setting linear smoothing makes the animation look more mechanized)
   Animation& length(Flt  length, Bool rescale_keyframes);   Flt  length()C {return _length                     ;} // set/get animation length, 'rescale_keyframes'=if proportionally rescale keyframes from current length to new length

   Int eventCount(CChar8 *name)C; // get number of events with specified name in this animation

   Bool eventAfter   (CChar8 *name            , Flt cur_time        )C; // if after 'name' event               , 'cur_time'=current animation time position
   Bool eventOccured (CChar8 *name            , Flt cur_time, Flt dt)C; // if       'name' event occured       , 'cur_time'=current animation time position, 'dt'=animation time delta (should be set to "Time.d() * animation_speed")
   Bool eventBetween (CChar8 *from, CChar8 *to, Flt cur_time, Flt dt)C; // if between event 'from' and 'to'    , 'cur_time'=current animation time position, 'dt'=animation time delta (should be set to "Time.d() * animation_speed")
   Flt  eventProgress(CChar8 *from, CChar8 *to, Flt cur_time        )C; // get progress between 'from' and 'to', 'cur_time'=current animation time position, 0 on fail

   // transform
   Animation& transform(C Matrix3 &matrix, C Skeleton &source); // transform animation by 'matrix', basing on 'source' skeleton

   // operations
   Animation& clip(Flt start_time, Flt end_time, Bool remove_unused_bones=true); // clip animation to 'start_time' .. 'end_time', this will remove all keyframes which aren't located in selected range

   Animation& adjust(Skeleton &source, Skeleton &target); // adjust animation which has been created for 'source' skeleton to be used for 'target' skeleton

   Animation& optimize      (Flt angle_eps=EPSA, Flt pos_eps=EPSL, Flt scale_eps=EPSL, Flt color_eps=0.01f, Bool remove_unused_bones=true); // optimize animation by removing similar keyframes, 'angle_eps'=angular epsilon 0..PI, 'pos_eps'=position epsilon 0..Inf, 'scale_eps'=scale epsilon 0..Inf, 'color_eps'=color epsilon 0..1, 'remove_unused_bones'=if remove unused bones after performing key reduction
   Animation& setTangents   (); // recalculate tangents, this needs to be called after manually modifying the keyframes
   Animation& maximizeLength(); // maximize animation length based on maximum time value out of all keyframes and events
   Animation& clipAuto      (); // clip     animation range starting with first keyframe and ending with last keyframe

   // convert
   Animation& convertRotToOrn(C Skeleton &skeleton); // convert relative  rotations to target orientations according to given 'skeleton'
   Animation& convertOrnToRot(C Skeleton &skeleton); // convert target orientations to relative  rotations according to given 'skeleton'

   // io
   void operator=(C Str &name) ; // load, Exit  on fail
   Bool save     (C Str &name)C; // save, false on fail
   Bool load     (C Str &name) ; // load, false on fail

   void save(File &f)C; // save
   Bool load(File &f) ; // load, false on fail

   void save(Memp<TextNode> nodes)C; // save as text

   Animation& del(); // delete manually
   Animation();

private:
   Byte _flag;
   Flt  _length;
};
/******************************************************************************/
extern Cache<Animation> Animations; // Animation Cache
/******************************************************************************/
struct SkelAnim // helper class for 'Skeleton' <-> 'Animation' relation, 'SkelAnim' objects are by default obtained by 'AnimatedSkeleton.findSkelAnim' and 'AnimatedSkeleton.getSkelAnim'
{
   // manage
   SkelAnim& create(C Skeleton &skeleton, Animation &animation); // create object to be used for 'skeleton' and 'animation' pair, 'animation' must point to constant memory address (only pointer to it is stored through which the object can be later accessed)

   // get
   CChar*     name     ()C {return  Animations.name(_animation         );} // get animation name
   UID        id       ()C {return  Animations.id  (_animation         );} // get animation name id
   Animation* animation()C {return _animation                           ;} // get animation object
   Flt        length   ()C {return _animation ? _animation->length() : 0;} // get animation length

   Int eventCount(CChar8 *name)C {return _animation ? _animation->eventCount(name) : 0;} // get number of events with specified name in this animation

   Bool eventAfter   (CChar8 *name            , Flt cur_time        )C {return _animation ? _animation->eventAfter   (name    , cur_time    ) : false;} // if after 'name' event               , 'cur_time'=current animation time position
   Bool eventOccured (CChar8 *name            , Flt cur_time, Flt dt)C {return _animation ? _animation->eventOccured (name    , cur_time, dt) : false;} // if       'name' event occured       , 'cur_time'=current animation time position, 'dt'=animation time delta (should be set to "Time.d() * animation_speed")
   Bool eventBetween (CChar8 *from, CChar8 *to, Flt cur_time, Flt dt)C {return _animation ? _animation->eventBetween (from, to, cur_time, dt) : false;} // if between event 'from' and 'to'    , 'cur_time'=current animation time position, 'dt'=animation time delta (should be set to "Time.d() * animation_speed")
   Flt  eventProgress(CChar8 *from, CChar8 *to, Flt cur_time        )C {return _animation ? _animation->eventProgress(from, to, cur_time    ) :     0;} // get progress between 'from' and 'to', 'cur_time'=current animation time position, 0 on fail

   SkelAnim&   del(); // delete manually
  ~SkelAnim() {del();}
   SkelAnim();
   SkelAnim(C Skeleton &skeleton, Animation &animation);

private:
   Byte      *_bone;
   Animation *_animation;
   NO_COPY_CONSTRUCTOR(SkelAnim);
};
/******************************************************************************/

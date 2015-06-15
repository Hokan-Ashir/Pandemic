/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Camera' to handle setting the viewing camera,
      where you can use the default 'Cam' camera, or create your own 'Camera' objects.

   Use helper functions to convert shapes between 3D world space and 2D screen space.

/******************************************************************************/
enum CAMH_FLAG // Camera Handle flags
{
   CAMH_ZOOM         =0x01, // zoom  with mouse wheel
   CAMH_ROT          =0x02, // rotate  on mouse move
   CAMH_MOVE         =0x04, // move    on mouse move
   CAMH_MOVE_XZ      =0x08, // move.xz on mouse move
   CAMH_NO_VEL_UPDATE=0x10, // don't automatically update   the velocities
   CAMH_NO_SET       =0x20, // don't automatically activate the camera
};
enum CAM_ATTACHMENT // information about camera attachment
{
   CAM_ATTACH_FREE , // no attachment
   CAM_ATTACH_ACTOR, // camera is attached to a physical actor
   CAM_ATTACH_CTRL , // camera is attached to a character controller
};
/******************************************************************************/
struct Camera
{
   Flt    yaw   , // yaw   angle                                    , default=0
          pitch , // pitch angle                                    , default=0
          roll  , // roll  angle                                    , default=0
          dist  ; // distance between camera position and 'at' point, default=1
   Vec    at    ; // point where camera is looking at               , default=Vec(0,0,0)
   Matrix matrix; // camera object matrix                           , default=MatrixIdentity-Vec(0,0,1)

   Vec       vel, // camera         velocity (this gets modified when calling 'updateVelocities')
         ang_vel; // camera angular velocity (this gets modified when calling 'updateVelocities')

   Camera& operator+=(C Vec &offset) {at+=offset; matrix+=offset; return T;} // move camera by 'offset'
   Camera& operator-=(C Vec &offset) {at-=offset; matrix-=offset; return T;} // move camera by 'offset'

   // set
   Camera& set         (C Matrix &matrix                                           ); // set from matrix
   Camera& setAngle    (C Vec    &pos , Flt yaw, Flt pitch, Flt roll=0             ); // set from position and angles
   Camera& setSpherical(C Vec    &at  , Flt yaw, Flt pitch, Flt roll, Flt dist     ); // set spherical from 'look at' position, angles and distance
   Camera& setSpherical(                                                           ); // set 'matrix' member as a spherical camera from current 'at dist yaw pitch roll' member values
   Camera& setFromAt   (C Vec    &from, C Vec &at            ,   Flt roll=0        ); // set from "look from" position, "look at" position and 'roll' angle
   Camera& setPosDir   (C Vec    &pos , C Vec &dir=Vec(0,0,1), C Vec &up=Vec(0,1,0)); // set from look directions

   // operations
   Camera& updateVelocities(CAM_ATTACHMENT attachment=CAM_ATTACH_CTRL) ; // update camera velocities 'vel ang_vel' according to current 'matrix' and the one from previous frame, this needs to be called exactly once per frame, 'attachment'=specifies to what the camera is attached to (this affects only Motion Blur effect)
   void    set             (                                         )C; // set as active camera - sets rendering matrixes, sets frustum, copies self to 'Cam'

   Camera& transformByMouse(Flt dist_min, Flt dist_max, UInt flag); // this is a helper method that transforms the camera basing on mouse input, 'dist_min'=minimum zoom distance, 'dist_max'=maximum zoom distance, 'flag'=CAMH_FLAG

   // io
   void save(File &f)C; // save binary
   Bool load(File &f) ; // load binary, false on fail

   Camera();

private:
   Matrix _matrix_prev;
};extern Camera
   Cam; // Active Camera
/******************************************************************************/
//
// Following functions work on active viewport and camera:
//
Vec2 PosToScreen (C Vec &pos              ); // convert 3D position to 2D screen position
Vec2 PosToScreenM(C Vec &pos              ); // convert 3D position to 2D screen position (transformed by current object matrix)
Bool PosToScreen (C Vec &pos, Vec2 &screen); // convert 3D position to 2D screen position                                       , false on fail (point is behind the camera)
Bool PosToScreenM(C Vec &pos, Vec2 &screen); // convert 3D position to 2D screen position (transformed by current object matrix), false on fail (point is behind the camera)

Vec  ScreenToPosD (C Vec2 &screen_d, Flt z=Cam.dist); // convert screen delta    to 3D delta
Vec  ScreenToPos  (C Vec2 &screen  , Flt z=Cam.dist); // convert screen position to 3D position
Vec  ScreenToPosDM(C Vec2 &screen_d, Flt z=Cam.dist); // convert screen delta    to 3D delta    (transformed by current object drawing matrix which is set by 'SetMatrix')
Vec  ScreenToPosM (C Vec2 &screen  , Flt z=Cam.dist); // convert screen position to 3D position (transformed by current object drawing matrix which is set by 'SetMatrix')

Vec  ScreenToDir   (C Vec2 &screen                    ); // convert screen position to world space                       3D direction
void ScreenToPosDir(C Vec2 &screen, Vec &pos, Vec &dir); // convert screen position to world space 3D position start and 3D direction

Bool ToScreenRect(C Box     &box    ,             Rect &rect); // project 3D box     to 2D on-screen rectangle, false on fail (shape is behind the camera)
Bool ToScreenRect(C OBox    &obox   ,             Rect &rect); // project 3D obox    to 2D on-screen rectangle, false on fail (shape is behind the camera)
Bool ToScreenRect(C Ball    &ball   ,             Rect &rect); // project 3D ball    to 2D on-screen rectangle, false on fail (shape is behind the camera)
Bool ToScreenRect(C Capsule &capsule,             Rect &rect); // project 3D capsule to 2D on-screen rectangle, false on fail (shape is behind the camera)
Bool ToScreenRect(C Pyramid &pyramid,             Rect &rect); // project 3D pyramid to 2D on-screen rectangle, false on fail (shape is behind the camera)
Bool ToScreenRect(C Shape   &shape  ,             Rect &rect); // project 3D shape   to 2D on-screen rectangle, false on fail (shape is behind the camera)
Bool ToScreenRect(C Shape   *shape  , Int shapes, Rect &rect); // project 3D shapes  to 2D on-screen rectangle, false on fail (shape is behind the camera)

Int CompareTransparencyOrder(C Vec &pos_a, C Vec &pos_b); // return comparing value -1/0/+1 determining the order of transparent objects rendering
/******************************************************************************/

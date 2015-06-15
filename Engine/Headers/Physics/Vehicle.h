/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'SimpleVehicle' to create vehicle type physical actor (like car).

   Use 'Vehicle' to create vehicle type physical actor (like car) - available only in PhysX 3

/******************************************************************************/
enum WHEEL_TYPE
{
   WHEEL_LEFT_FRONT , //  left front wheel
   WHEEL_RIGHT_FRONT, // right front wheel
   WHEEL_LEFT_REAR  , //  left rear  wheel
   WHEEL_RIGHT_REAR , // right rear  wheel
   WHEEL_NUM        , // number of   wheels
};
inline Bool IsFront(WHEEL_TYPE wheel) {return   wheel<=WHEEL_RIGHT_FRONT;} // if wheel type is front wheel
inline Bool IsRear (WHEEL_TYPE wheel) {return   wheel>=WHEEL_LEFT_REAR  ;} // if wheel type is rear  wheel
inline Bool IsLeft (WHEEL_TYPE wheel) {return !(wheel&1)                ;} // if wheel type is left  wheel
inline Bool IsRight(WHEEL_TYPE wheel) {return  (wheel&1)                ;} // if wheel type is right wheel
/******************************************************************************/
const_mem_addr struct SimpleVehicle // Physical actor of vehicle type !! must be stored in constant memory address !!
{
   enum WHEEL_DRIVE
   {
      AWD, // all   wheel drive (also known as 4WD four wheel drive)
      FWD, // front wheel drive
      RWD, // rear  wheel drive
   };
   struct Wheel
   {
      Flt radius, // wheel radius, default=0.35 m
          width ; // wheel width , default=0.25 m
      Vec pos   ; // wheel position in vehicle

      void set(Flt radius, Flt width, C Vec &pos) {T.radius=radius; T.width=width; T.pos=pos;}

      Wheel() {set(0.35f, 0.25f, VecZero);}
   };
   struct Params // all of these parameters (except masses) will be scaled according to 'scale' during vehicle creation
   {
      Wheel wheel[WHEEL_NUM]; // parameters for each wheel
   };

   // manage
   SimpleVehicle& del      ();                                                               // manually delete
   Bool           createTry(C PhysBody &body, C Params &params, Flt density=1, Flt scale=1); // create from 'body' physical body, 'params' parameters, 'density' density and 'scale' scaling, false on fail
   SimpleVehicle& create   (C PhysBody &body, C Params &params, Flt density=1, Flt scale=1); // create from 'body' physical body, 'params' parameters, 'density' density and 'scale' scaling, Exit  on fail

   // get / set
   Bool is()C; // if created

   Int        onGroundNum()C;                                                  // get     number  of weels on ground
   Bool       onGroundAny()C;                                                  // if      vehicle is       on ground (at least one wheel  on ground)
   Bool       onGroundAll()C;                                                  // if      vehicle is       on ground (all          wheels on ground)
   Bool          onGround(WHEEL_TYPE wheel)C;                                  // if      wheel   is       on ground
   Matrix   wheelMatrix  (WHEEL_TYPE wheel, Int flip_side=-1)C;                // get     wheel   matrix           in world space, 'flip_side'=if flip/mirror the wheel matrix (-1=flip left wheels only, 0=don't flip, 1=flip right wheels only)
   Vec      wheelVel     (WHEEL_TYPE wheel)C;                                  // get     wheel           velocity in world space
   Vec      wheelAngVel  (WHEEL_TYPE wheel)C;                                  // get     wheel   angular velocity in world space
   Vec      wheelContact (WHEEL_TYPE wheel)C;                                  // get     wheel   last contact point        with the ground, Vec(0,0,0) if never was on ground
   Vec      wheelContactN(WHEEL_TYPE wheel)C;                                  // get     wheel   last contact point normal with the ground, Vec(0,1,0) if never was on ground
   Flt      wheelRadius  (WHEEL_TYPE wheel)C;                                  // get     wheel   radius
   Flt      wheelCompress(WHEEL_TYPE wheel)C;                                  // get     wheel   compression, value <0 means wheel is loose in air, value 0 means wheel is at rest, value 1 means wheel is fully compressed
   Flt              speed()C;                                                  // get     vehicle forward  speed (this value is positive when moving forward and negative when moving backwards)
   Flt          sideSpeed()C;                                                  // get     vehicle side     speed (this value is positive when moving right   and negative when moving left     )
   Flt              accel()C;   SimpleVehicle&          accel(Flt   accel   ); // get/set           acceleration      , -1..1
   Flt              brake()C;   SimpleVehicle&          brake(Flt   brake   ); // get/set current         brake       ,  0..1
   Flt              angle()C;   SimpleVehicle&          angle(Flt   angle   ); // get/set current   steer angle       , -1..1
   Flt           maxAccel()C;   SimpleVehicle&       maxAccel(Flt   accel   ); // get/set max       acceleration force,  0..Inf , default=10
   Flt       maxBackAccel()C;   SimpleVehicle&   maxBackAccel(Flt   accel   ); // get/set max back  acceleration force,  0..Inf , default=4.5
   Flt           maxBrake()C;   SimpleVehicle&       maxBrake(Flt   brake   ); // get/set max             brake  force,  0..Inf , default=12
   Flt         brakeRatio()C;   SimpleVehicle&     brakeRatio(Flt   ratio   ); // get/set      front/rear brake  ratio,  0..1   , default=0.43, this parameter specifies how much of the braking goes into front wheels, rear wheels will have a value "1-ratio" (for example if front has 0.6, then rear will have 0.4)
   Flt           maxAngle()C;   SimpleVehicle&       maxAngle(Flt   angle   ); // get/set max       steer angle       ,  0..PI_2, default=PI_3
   Flt     frictionLinear()C;   SimpleVehicle& frictionLinear(Flt   friction); // get/set         wheel linear fricion,  0..Inf , default=13  , this parameter specifies the linear portion of the friction when moving sideways, side velocity will be decreased by this value by    subtraction
   Flt     frictionScalar()C;   SimpleVehicle& frictionScalar(Flt   friction); // get/set         wheel scalar fricion,  0..1   , default=0.3 , this parameter specifies the scalar portion of the friction when moving sideways, side velocity will be decreased by this value by multiplication
   Flt       suspSpring  ()C;   SimpleVehicle&   suspSpring  (Flt   spring  ); // get/set   suspension spring strength,  0..Inf , default=20  , this parameter specifies bounciness strength of the suspension
   Flt       suspDamping ()C;   SimpleVehicle&   suspDamping (Flt   damping ); // get/set   suspension spring damping ,  0..Inf , default=0.7 , this parameter specifies how quickly does the suspension stabilize
   Flt       suspCompress()C;   SimpleVehicle&   suspCompress(Flt   compress); // get/set   suspension max compression,  0..1   , default=0.75 (1.0 means full wheel radius)
   WHEEL_DRIVE wheelDrive()C;   SimpleVehicle&     wheelDrive(WHEEL_DRIVE wd); // get/set wheel drive                           , default=WHEEL_AWD

   Flt      energy    (          )C;                                                   // get     kinetic energy , 0..Inf
   Flt      damping   (          )C;   SimpleVehicle&  damping   (  Flt      damping); // get/set linear  damping, 0..Inf, default=0.05
   Flt     adamping   (          )C;   SimpleVehicle& adamping   (  Flt      damping); // get/set angular damping, 0..Inf, default=0.05
   Flt     mass       (          )C;   SimpleVehicle& mass       (  Flt      mass   ); // get/set mass           , 0..Inf
   Vec     massCenterL(          )C;   SimpleVehicle& massCenterL(C Vec     &center ); // get/set mass center in actor local space
   Vec     massCenterW(          )C;   SimpleVehicle& massCenterW(C Vec     &center ); // get/set mass center in world       space
   Vec     inertia    (          )C;   SimpleVehicle& inertia    (C Vec     &inertia); // get/set inertia tensor
   Vec     pos        (          )C;   SimpleVehicle& pos        (C Vec     &pos    ); // get/set position
   Matrix3 orn        (          )C;   SimpleVehicle& orn        (C Matrix3 &orn    ); // get/set orientation, 'orn'    must be normalized
   Matrix  matrix     (          )C;   SimpleVehicle& matrix     (C Matrix  &matrix ); // get/set matrix     , 'matrix' must be normalized
   Vec          vel   (          )C;   SimpleVehicle&    vel     (C Vec     &vel    ); // get/set         velocity
   Vec       angVel   (          )C;   SimpleVehicle& angVel     (C Vec     &vel    ); // get/set angular velocity
   Vec     pointVelL  (C Vec &pos)C;                                                   // get     point   velocity ('pos' is in actor local space)
   Vec     pointVelW  (C Vec &pos)C;                                                   // get     point   velocity ('pos' is in world       space)
   Box     box        (          )C;                                                   // get     bounding box in world space
   Flt     scale      (          )C {return _scale;}                                   // get     scale that was used during vehicle creation

   SimpleVehicle& addTorque (C Vec &torque             ); // add torque                              , unit = mass * rotation / time^2
   SimpleVehicle& addAngVel (C Vec &ang_vel            ); // add angular velocity                    , unit =        rotation / time
   SimpleVehicle& addForce  (C Vec &force              ); // add force                               , unit = mass * distance / time^2
   SimpleVehicle& addForce  (C Vec &force  , C Vec &pos); // add force        at world 'pos' position, unit = mass * distance / time^2
   SimpleVehicle& addImpulse(C Vec &impulse            ); // add impulse                             , unit = mass * distance / time
   SimpleVehicle& addImpulse(C Vec &impulse, C Vec &pos); // add impulse      at world 'pos' position, unit = mass * distance / time
   SimpleVehicle& addVel    (C Vec &vel                ); // add velocity                            , unit =        distance / time
   SimpleVehicle& addVel    (C Vec &vel    , C Vec &pos); // add velocity     at world 'pos' position, unit =        distance / time
   SimpleVehicle& addAccel  (C Vec &accel              ); // add acceleration                        , unit =        distance / time^2
   SimpleVehicle& addAccel  (C Vec &accel  , C Vec &pos); // add acceleration at world 'pos' position, unit =        distance / time^2

   Bool       gravity    ()C;   SimpleVehicle& gravity    (Bool       on       ); // get/set if gravity is enabled for this vehicle
   Bool       ray        ()C;   SimpleVehicle& ray        (Bool       on       ); // get/set if this actor should be included when performing ray tests
   Bool       collision  ()C;   SimpleVehicle& collision  (Bool       on       ); // get/set if this actor should collide with other actors in the world
   Bool       sleep      ()C;   SimpleVehicle& sleep      (Bool       sleep    ); // get/set sleeping
   Flt        sleepEnergy()C;   SimpleVehicle& sleepEnergy(Flt        energy   ); // get/set the amount of energy below the actor is put to sleep, default=0.005
   Bool       ccd        ()C;   SimpleVehicle& ccd        (Bool       on       ); // get/set continuous collision detection
   Ptr        user       ()C;   SimpleVehicle& user       (Ptr        user     ); // get/set custom user data
   Game::Obj* obj        ()C;   SimpleVehicle& obj        (Game::Obj *obj      ); // get/set pointer to game object containing the actor
   Byte       group      ()C;   SimpleVehicle& group      (Byte       group    ); // get/set collision group (0..31, default value is taken according to ACTOR_GROUP)
   Byte       dominance  ()C;   SimpleVehicle& dominance  (Byte       dominance); // get/set dominance index (0..31, default=0), for more information about dominance please check comments on 'Physics.dominance' method
   PhysMtrl*  material   ()C;   SimpleVehicle& material   (PhysMtrl  *material ); // get/set physics material for vehicle (use 'NULL' for default material)

   // io
   void saveState(File &f)C; // save vehicle state (following data is not  saved: physical body, mass, density, scale, damping, max ang vel, mass center, inertia, material)
   Bool loadState(File &f) ; // load vehicle state (following data is not loaded: physical body, mass, density, scale, damping, max ang vel, mass center, inertia, material), typically you should first create a vehicle from a physical body and then call this method to set its state according to data from the file, false on fail

  ~SimpleVehicle() {del();}
   SimpleVehicle();

private:
   struct _Wheel
   {
      Flt   radius, compress, angle, angle_vel;
      Vec   pos;
      Plane contact;
   };
   Enum1<WHEEL_DRIVE> _wd;
   Flt                _accel, _brake, _angle, _max_accel, _max_back_accel, _max_brake, _brake_ratio, _max_angle, _fric_linear, _fric_scalar, _susp_spring, _susp_damping, _susp_compress, _scale, _avg_wheel_dist;
  _Wheel              _wheel[WHEEL_NUM];
   Actor              _actor;
};
/******************************************************************************/
struct Vehicle // Physical actor of vehicle type (this class is available only in PhysX 3)
{
   enum DIFF_TYPE
   {
      DIFF_LS_4WD  , // limited slip differential for car with four  wheel drive
      DIFF_LS_FWD  , // limited slip differential for car with front wheel drive
      DIFF_LS_RWD  , // limited slip differential for car with rear  wheel drive
      DIFF_OPEN_4WD, // open         differential for car with four  wheel drive
      DIFF_OPEN_FWD, // open         differential for car with front wheel drive
      DIFF_OPEN_RWD, // open         differential for car with rear  wheel drive
   };
   struct Wheel
   {
      Flt radius, // wheel radius, default=0.35 m
          width ; // wheel width , default=0.25 m
      Vec pos   ; // wheel position in vehicle

      void set(Flt radius, Flt width, C Vec &pos) {T.radius=radius; T.width=width; T.pos=pos;}

      Wheel() {set(0.35f, 0.25f, VecZero);}
   };
   struct Params // all of these parameters (except masses) will be scaled according to 'scale' during vehicle creation
   {
      Flt   mass              , // vehicle mass, default=1500 kg
            wheel_mass        ; // wheel   mass, default=  20 kg
      Vec   mass_center_offset; // offset to center of mass in vehicle actor, default=(0, -0.1, 0) (slightly below)
      Wheel wheel[WHEEL_NUM]  ; // parameters for each wheel

      Params() {mass=1500; wheel_mass=20; mass_center_offset.set(0, -0.1f, 0);}
   };

   // manage
   Vehicle& del      ();                                                // manually delete
   Bool     createTry(C PhysBody &body, C Params &params, Flt scale=1); // create from 'body' physical body, 'params' parameters, and 'scale' scaling, false on fail
   Vehicle& create   (C PhysBody &body, C Params &params, Flt scale=1); // create from 'body' physical body, 'params' parameters, and 'scale' scaling, Exit  on fail

   // get / set
   Bool is()C {return _vehicle!=NULL;} // if created

   Bool        onGround()C;                                              // if      vehicle is on ground (at least one wheel on ground)
   Bool        onGround(WHEEL_TYPE wheel)C;                              // if      wheel   is on ground
   Matrix wheelMatrix  (WHEEL_TYPE wheel)C;                              // get     wheel   matrix           in world space
   Vec    wheelVel     (WHEEL_TYPE wheel)C;                              // get     wheel           velocity in world space
   Vec    wheelAngVel  (WHEEL_TYPE wheel)C;                              // get     wheel   angular velocity in world space
   Vec    wheelContact (WHEEL_TYPE wheel)C;                              // get     wheel   contact point with the ground, Vec(0,0,0) if not on ground
   Flt    wheelRadius  (WHEEL_TYPE wheel)C;                              // get     wheel   radius
   Flt    wheelCompress(WHEEL_TYPE wheel)C;                              // get     wheel   compression, value <0 means wheel is loose in air, value 0 means wheel is at rest, value 1 means wheel is fully compressed
   Flt    wheelLongSlip(WHEEL_TYPE wheel)C;                              // get     wheel   longitudinal slip (how much does the wheel slip on ground in "forward" direction)
   Flt    wheelLatSlip (WHEEL_TYPE wheel)C;                              // get     wheel   lateral      slip (how much does the wheel slip on ground in "side   " direction)
   Flt            speed()C;                                              // get     vehicle forward  speed (this value is positive when moving forward and negative when moving backwards)
   Flt        sideSpeed()C;                                              // get     vehicle side     speed (this value is positive when moving right   and negative when moving left     )
   Flt      engineSpeed()C;                                              // get     engine  rotation speed (in radians per second)
   Flt      engineFrac ()C {return engineSpeed()/engineMaxSpeed();}      // get     engine  rotation speed fraction (0..1) this can be useful information when changing gears manually (for example: for fraction < 0.5 you can gear down, for fraction > 0.65 you can gear up)
   Int            gears()C;                                              // get     number of gears
   Int             gear()C;   Vehicle&             gear(Int   gear    ); // get/set current   gear (-1=reverse, 0=neutral, 1..=normal gear)
   Bool        autoGear()C;   Vehicle&         autoGear(Bool  on      ); // get/set automatic gear changing     , true/false, default=true
   Flt            accel()C;   Vehicle&            accel(Flt   accel   ); // get/set           acceleration      ,  0..1
   Flt            brake()C;   Vehicle&            brake(Flt   brake   ); // get/set current         brake       ,  0..1
   Flt        handBrake()C;   Vehicle&        handBrake(Flt   brake   ); // get/set current   hand  brake       ,  0..1
   Flt            angle()C;   Vehicle&            angle(Flt   angle   ); // get/set current   steer angle       , -1..1
   Flt         maxBrake()C;   Vehicle&         maxBrake(Flt   brake   ); // get/set max             brake torque,  0..Inf   , default=1500
   Flt     maxHandBrake()C;   Vehicle&     maxHandBrake(Flt   brake   ); // get/set max       hand  brake torque,  0..Inf   , default=4000
   Flt         maxAngle()C;   Vehicle&         maxAngle(Flt   angle   ); // get/set max       steer angle       ,  0..PI_2  , default=PI_3
   Flt     wheelDamping()C;   Vehicle&     wheelDamping(Flt   damping ); // get/set           wheel damping     ,  0..Inf   , default=0.05
   Flt     suspSpring  ()C;   Vehicle&     suspSpring  (Flt   spring  ); // get/set   suspension spring strength,  0..Inf   , default=35000
   Flt     suspDamping ()C;   Vehicle&     suspDamping (Flt   damping ); // get/set   suspension spring damping ,  0..Inf   , default= 4500
   Flt     suspCompress()C;   Vehicle&     suspCompress(Flt   compress); // get/set   suspension max compression,  0..1     , default=0.75 (1.0 means full wheel radius)
   Flt     suspElongate()C;   Vehicle&     suspElongate(Flt   elongate); // get/set   suspension max elongation ,  0..1     , default=0.25 (1.0 means full wheel radius)
   Flt enginePeakTorque()C;   Vehicle& enginePeakTorque(Flt   peak    ); // get/set   engine peak torque        ,  0..Inf   , default= 500, maximum acceleration applied to engine rotation
   Flt engineMaxSpeed  ()C;   Vehicle& engineMaxSpeed  (Flt   omega   ); // get/set   engine max rotation spead ,  0..Inf   , default= 600 (in radians per second)
   DIFF_TYPE   diffType()C;   Vehicle&         diffType(DIFF_TYPE diff); // get/set   differential type         ,  DIFF_TYPE, default=DIFF_LS_4WD
   Flt  tireLongStiff  ()C;   Vehicle&  tireLongStiff  (Flt   f       ); // get/set longitudinal stiffness per unit longitudinal slip per unit gravity, specified in N per radian per unit gravitational acceleration. Longitudinal stiffness of the tire per unit longitudinal slip is calculated as "gravity*tireLongStiff", 0..Inf, default=1000
   Flt  tireLatStiffX  ()C;   Vehicle&  tireLatStiffX  (Flt   f       ); // get/set the minimum normalised load (load/restLoad) that gives a flat lateral stiffness response        (Tire lateral stiffness is typically a graph of tire load that has linear behaviour near zero load and flattens at large loads)          , 0..Inf, default=2
   Flt  tireLatStiffY  ()C;   Vehicle&  tireLatStiffY  (Flt   f       ); // get/set the maximum possible lateral stiffness divided by the rest tire load, specified in "per radian" (Tire lateral stiffness is typically a graph of tire load that has linear behaviour near zero load and flattens at large loads)          , 0..Inf, default=17.9
   Flt  tireCamberStiff()C;   Vehicle&  tireCamberStiff(Flt   f       ); // get/set Camber stiffness, specified in kilograms per radian                                                                                                                                                                                      , 0..Inf, default=5.73

      // function of friction vs longitudinal slip with 3 points, these values define a function "wheelFriction=Func(wheelLongSlip)", like "y=f(x)" and you define control points of the "x" (slip) and "y" (friction)
    //Flt tireFuncPoint0Slip()C;   Vehicle& tireFuncPoint0Slip(Flt f); // get/set slip     value at point 0, this value is always zero
      Flt tireFuncPoint0Fric()C;   Vehicle& tireFuncPoint0Fric(Flt f); // get/set friction value at point 0, 0..Inf, default=1
      Flt tireFuncPoint1Slip()C;   Vehicle& tireFuncPoint1Slip(Flt f); // get/set slip     value at point 1, 0..Inf, default=0.1
      Flt tireFuncPoint1Fric()C;   Vehicle& tireFuncPoint1Fric(Flt f); // get/set friction value at point 1, 0..Inf, default=1
      Flt tireFuncPoint2Slip()C;   Vehicle& tireFuncPoint2Slip(Flt f); // get/set slip     value at point 2, 0..Inf, default=1
      Flt tireFuncPoint2Fric()C;   Vehicle& tireFuncPoint2Fric(Flt f); // get/set friction value at point 2, 0..Inf, default=1

   Vehicle& precision(Flt thresholdLongitudinalSpeed, UInt lowForwardSpeedSubStepCount, UInt highForwardSpeedSubStepCount); // Set the number of vehicle sub-steps that will be performed when the vehicle's longitudinal speed is below and above a threshold longitudinal speed. More sub-steps provides better stability but with greater computational cost. Typically, vehicles require more sub-steps at very low forward speeds. The threshold longitudinal speed has a default value of 5 metres per second. The sub-step count below the threshold longitudinal speed has a default of 3. The sub-step count above the threshold longitudinal speed has a default of 1. Each sub-step has time advancement equal to the time-step passed to 'Physics.startSimulation' divided by the number of required sub-steps. The contact planes of the most recent suspension line raycast are reused across all sub-steps. Each sub-step computes tire and suspension forces and then advances a velocity, angular velocity and transform. At the end of all sub-steps the vehicle actor is given the velocity and angular velocity that would move the actor from its start transform prior to the first sub-step to the transform computed at the end of the last substep, assuming it doesn't collide with anything along the way in the next PhysX SDK update. The global pose of the actor is left unchanged throughout the sub-steps. 'thresholdLongitudinalSpeed'=threshold speed that is used to categorize vehicle speed as low speed or high speed. 'lowForwardSpeedSubStepCount'=number of sub-steps performed in PxVehicleUpates for vehicles that have longitudinal speed lower than thresholdLongitudinalSpeed. 'highForwardSpeedSubStepCount'=number of sub-steps performed in PxVehicleUpdates for vehicles that have longitudinal speed graeter than thresholdLongitudinalSpeed.

   Flt      energy    (          )C;                                          // get     kinetic energy , 0..Inf
   Flt      damping   (          )C;   Vehicle&  damping(  Flt      damping); // get/set linear  damping, 0..Inf, default=0.05
   Flt     adamping   (          )C;   Vehicle& adamping(  Flt      damping); // get/set angular damping, 0..Inf, default=0.05
   Flt     mass       (          )C;                                          // get     mass           , 0..Inf
   Vec     massCenterL(          )C;                                          // get     mass center in actor local space
   Vec     massCenterW(          )C;                                          // get     mass center in world       space
   Vec     inertia    (          )C;   Vehicle& inertia (C Vec     &inertia); // get/set inertia tensor
   Vec     pos        (          )C;   Vehicle& pos     (C Vec     &pos    ); // get/set position
   Matrix3 orn        (          )C;   Vehicle& orn     (C Matrix3 &orn    ); // get/set orientation, 'orn'    must be normalized
   Matrix  matrix     (          )C;   Vehicle& matrix  (C Matrix  &matrix ); // get/set matrix     , 'matrix' must be normalized
   Vec          vel   (          )C;   Vehicle&    vel  (C Vec     &vel    ); // get/set         velocity
   Vec       angVel   (          )C;   Vehicle& angVel  (C Vec     &vel    ); // get/set angular velocity
   Vec     pointVelL  (C Vec &pos)C;                                          // get     point   velocity ('pos' is in actor local space)
   Vec     pointVelW  (C Vec &pos)C;                                          // get     point   velocity ('pos' is in world       space)
   Box     box        (          )C;                                          // get     bounding box in world space
   Flt     scale      (          )C {return _scale;}                          // get     scale that was used during vehicle creation

   Vehicle& addTorque (C Vec &torque             ); // add torque                              , unit = mass * rotation / time^2
   Vehicle& addAngVel (C Vec &ang_vel            ); // add angular velocity                    , unit =        rotation / time
   Vehicle& addForce  (C Vec &force              ); // add force                               , unit = mass * distance / time^2
   Vehicle& addForce  (C Vec &force  , C Vec &pos); // add force        at world 'pos' position, unit = mass * distance / time^2
   Vehicle& addImpulse(C Vec &impulse            ); // add impulse                             , unit = mass * distance / time
   Vehicle& addImpulse(C Vec &impulse, C Vec &pos); // add impulse      at world 'pos' position, unit = mass * distance / time
   Vehicle& addVel    (C Vec &vel                ); // add velocity                            , unit =        distance / time
   Vehicle& addVel    (C Vec &vel    , C Vec &pos); // add velocity     at world 'pos' position, unit =        distance / time
   Vehicle& addAccel  (C Vec &accel              ); // add acceleration                        , unit =        distance / time^2
   Vehicle& addAccel  (C Vec &accel  , C Vec &pos); // add acceleration at world 'pos' position, unit =        distance / time^2

   Bool       ray        ()C;   Vehicle& ray        (Bool       on       ); // get/set if this actor should be included when performing ray tests
   Bool       collision  ()C;   Vehicle& collision  (Bool       on       ); // get/set if this actor should collide with other actors in the world
   Bool       sleep      ()C;   Vehicle& sleep      (Bool       sleep    ); // get/set sleeping
   Flt        sleepEnergy()C;   Vehicle& sleepEnergy(Flt        energy   ); // get/set the amount of energy below the actor is put to sleep, default=0.005
   Bool       ccd        ()C;   Vehicle& ccd        (Bool       on       ); // get/set continuous collision detection
   Ptr        user       ()C;   Vehicle& user       (Ptr        user     ); // get/set custom user data
   Game::Obj* obj        ()C;   Vehicle& obj        (Game::Obj *obj      ); // get/set pointer to game object containing the actor
   Byte       group      ()C;   Vehicle& group      (Byte       group    ); // get/set collision group (0..31, default value is taken according to ACTOR_GROUP)
   Byte       dominance  ()C;   Vehicle& dominance  (Byte       dominance); // get/set dominance index (0..31, default=0), for more information about dominance please check comments on 'Physics.dominance' method

   PhysMtrl*  bodyMaterial()C;   Vehicle&  bodyMaterial(PhysMtrl *material); // get/set physics material for vehicle body   (use 'NULL' for default material)
   PhysMtrl* wheelMaterial()C;   Vehicle& wheelMaterial(PhysMtrl *material); // get/set physics material for vehicle wheels (use 'NULL' for default material)

   // operations
   Vehicle& reset(); // this method will reset the engine, wheel and control state (acceleration, torque, forces, gear, etc.)

   Vehicle& gearUp  () {Int g=gear(); return gear((g<=0) ?  1 : g+1);} // set gear up   (avoiding neutral gear)
   Vehicle& gearDown() {Int g=gear(); return gear((g<=1) ? -1 : g-1);} // set gear down (avoiding neutral gear)

  ~Vehicle() {del();}
   Vehicle();

private:
   Ptr   _vehicle;
   UInt  _vehicle_id;
   Flt   _scale;
   Actor _actor;
   NO_COPY_CONSTRUCTOR(Vehicle);
};
/******************************************************************************/
struct WheelPx2 // Physical Wheel (this class is available only in PhysX 2), use it to create additional wheel shapes in a vehicle 'Actor'
{
   struct Param // wheel parameters
   {
      Flt mass        , // mass              , 0..Inf, default=10
          radius      , // radius            , 0..Inf, default=0.4
          susp        , // suspension        , 0..Inf, default=0.15
          susp_spring , // suspension spring , 0..Inf, default=100
          susp_damping; // suspension damping, 0..Inf, default=1

      Param();
   };
   struct Func // wheel force function parameters
   {
      Flt extremumSlip   , // extremal point of curve                                             , 0..Inf, default=1.0
          extremumValue  , // extremal point of curve                                             , 0..Inf, default=0.02
          asymptoteSlip  , // point on curve at which for all x>minumumX, function equals minimumY, 0..Inf, default=2.0
          asymptoteValue , // point on curve at which for all x>minumumX, function equals minimumY, 0..Inf, default=0.01
          stiffnessFactor; // scaling factor for tire force                                       , 0..Inf, default=1000000

      Func();
   };

   // manage
   WheelPx2& del    (                                              ); // delete manually
   WheelPx2& create (Actor &vehicle, C Matrix &matrix, Param &param); // create, 'vehicle'=vehicle actor to attach the wheel to, 'matrix'=wheel matrix in world       space (must be normalized), 'param'=wheel parameters
   WheelPx2& createL(Actor &vehicle, C Matrix &matrix, Param &param); // create, 'vehicle'=vehicle actor to attach the wheel to, 'matrix'=wheel matrix in actor local space (must be normalized), 'param'=wheel parameters

   // params
   WheelPx2& longForceFunction(Func &func); // set cubic hermite spline coefficients describing the longitudinal tire force curve
   WheelPx2&  latForceFunction(Func &func); // set cubic hermite spline coefficients describing the lateral      tire force curve

   // get / set
   Bool   contact()C;                                 // if      wheel is in contact with some actor
   Matrix matrix (Flt *force_angle=NULL)C;            // get     wheel matrix, 'force_angle'=optional parameter if not NULL then matrix will be returned as if wheel had 'force_angle' rotation angle, if NULL then 'angle' will be used
   Vec    vel    ()C;                                 // get     wheel linear  velocity
   Vec    angVel ()C;                                 // get     wheel angular velocity
   Flt    roll   ()C;                                 // get     wheel roll angle
   Flt    speed  ()C;                                 // get     wheel roll speed
   Flt    angle  ()C;   WheelPx2& angle (Flt angle ); // get/set angle
   Flt    accel  ()C;   WheelPx2& accel (Flt accel ); // get/set acceleration
   Flt    brake  ()C;   WheelPx2& brake (Flt brake ); // get/set brakes
   Flt    radius ()C;   WheelPx2& radius(Flt radius); // get/set wheel radius
   Ptr    user   ()C;   WheelPx2& user  (Ptr user  ); // get/set user  data

  ~WheelPx2() {del ( );}
   WheelPx2() {Zero(T);}

private:
   Ptr _data;
   NO_COPY_CONSTRUCTOR(WheelPx2);
};
/******************************************************************************/

/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
const_mem_addr struct PhysMtrl // Physics Material !! must be stored in constant memory address !!
{
   enum MODE
   {
      MODE_AVG, // average        of materials values
      MODE_MUL, // multiplication of materials values
      MODE_MIN, // minimum        of materials values
      MODE_MAX, // maximum        of materials values
   };

   PhysMtrl& create(); // create material

   // get / set
   Flt  bounciness      ()C;   PhysMtrl& bounciness      (  Flt   x   ); // get/set                     bounciness        , 0..1             , default=0
   Flt  frictionStatic  ()C;   PhysMtrl& frictionStatic  (  Flt   x   ); // get/set static              friction          , 0..Inf           , default=0
   Flt  frictionDynamic ()C;   PhysMtrl& frictionDynamic (  Flt   x   ); // get/set dynamic             friction          , 0..Inf           , default=0
   Flt  frictionStaticA ()C;   PhysMtrl& frictionStaticA (  Flt   x   ); // get/set static  anisotropic friction          , 0..Inf           , default=0
   Flt  frictionDynamicA()C;   PhysMtrl& frictionDynamicA(  Flt   x   ); // get/set dynamic anisotropic friction          , 0..Inf           , default=0
   Flt  density         ()C;   PhysMtrl& density         (  Flt   x   ); // get/set                     density           , 0..Inf           , default=1
   Flt   damping        ()C;   PhysMtrl&  damping        (  Flt   x   ); // get/set                     damping           , 0..Inf           , default=0.05
   Flt  adamping        ()C;   PhysMtrl& adamping        (  Flt   x   ); // get/set             angular damping           , 0..Inf           , default=0.05
   Bool anisotropic     ()C;   PhysMtrl& anisotropic     (  Bool  on  ); // get/set enable  anisotropic friction          , true/false       , default=false
   Vec  anisotropicDir  ()C;   PhysMtrl& anisotropicDir  (C Vec  &dir ); // get/set         anisotropic friction direction, normalized vector
   MODE bouncinessMode  ()C;   PhysMtrl& bouncinessMode  (  MODE  mode); // get/set                     bounciness mode   , MODE             , default=MODE_AVG
   MODE frictionMode    ()C;   PhysMtrl& frictionMode    (  MODE  mode); // get/set                     friction   mode   , MODE             , default=MODE_AVG

   // io
   Bool save(C Str  &name)C; // save to   file
   Bool load(C Str  &name) ; // load from file
   void save(  File &f   )C; // save to   file
   Bool load(  File &f   ) ; // load from file

   void        del();
  ~PhysMtrl() {del();}
   PhysMtrl();

private:
   Flt  _bounciness, _friction_static, _friction_dynamic, _density, _damping, _adamping;
   MODE _bounciness_mode, _friction_mode;
   Ptr  _m;
   NO_COPY_CONSTRUCTOR(PhysMtrl);
};
/******************************************************************************/
extern Cache<PhysMtrl> PhysMtrls; // Physics Material Cache
/******************************************************************************/

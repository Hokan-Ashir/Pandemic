/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Sun' to set the main sun object.

   Use 'Astros' container to create custom astronomical objects.

/******************************************************************************/
enum SUN_RAYS_MODE
{
   SUN_RAYS_OFF , // disabled
   SUN_RAYS_LOW , // enabled with object        occlusion detection
   SUN_RAYS_HIGH, // enabled with object+clouds occlusion detection
   SUN_RAYS_NUM , // number of sun ray modes
};
/******************************************************************************/
struct Astro // Astronomical Object (Star/Planet/Moon)
{
   Bool draw; // if use this object in drawing, true/false, default=true

   Bool     blend      ; // if use blending for image,        true/false              , default=true, if true then 'image' will be applied using alpha blending, if false then 'image' will be added onto the screen
   Byte     glow       ; // glow amount              ,           0..255               , default=0   , total glow amount is equal to ('image' alpha channel * 'image_color' alpha component * 'glow')
   Flt      size       ; // image      size          ,           0..1                 , default=0.15
   Vec      pos        ; // normalized position      , position on sky sphere radius=1, default=!Vec(-1,1,-1)
   Color    image_color; // image      color         ,                                , default=WHITE
   ImagePtr image      ; // image                                                     , default=NULL

   Vec light_color    ; // light      color   , (0,0,0)..(1,1,1), default=(0,0,0), value of (0,0,0) disables light casting
   Flt light_vol      , // volumetric amount  ,       0..Inf    , default=0.0
       light_vol_exp  , // volumetric exponent,       0..Inf    , default=1.0
       light_vol_steam; // volumetric steam   ,       0..1      , default=0.5

   Astro();
};
/******************************************************************************/
STRUCT(SunClass , Astro) // Sun objects have default member values: 'glow'=128, 'light_color'=(0.7, 0.7, 0.7)
//{
   Flt highlight_front, // amount of highlight applied on atmospheric sky, 0..Inf, default=0.10
       highlight_back ; // amount of highlight applied on atmospheric sky, 0..Inf, default=0.07

   SUN_RAYS_MODE rays_mode ; // rays mode      ,   SUN_RAYS_MODE , default=SUN_RAYS_HIGH
   Bool          rays_soft ; // rays softing   ,    true/false   , default=false
   Byte          rays_res  ; // rays resolution,       0..2      , default=2            , lower value means bigger resolution and slower performance, resolution #0 can't be softened
   Vec           rays_color; // rays color     , (0,0,0)..(1,1,1), default=(0.1,0.1,0.1)

   SunClass();

private:
   SUN_RAYS_MODE _actual_rays_mode;
   Vec2          _pos2;
}extern
   Sun; // Main Sun
/******************************************************************************/
extern Bool        AstrosDraw; // if draw      astronomical objects, default=true
extern Memc<Astro> Astros    ; // container of astronomical objects
/******************************************************************************/

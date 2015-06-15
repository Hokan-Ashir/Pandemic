/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Sky' to set custom sky.

/******************************************************************************/
struct SkyClass
{
   // manage
   SkyClass& clear(        );                               // disable sky rendering
   SkyClass& frac (Flt frac);   Flt frac()C {return _frac;} // set/get sky fraction (fraction of the Viewport range where the sky starts), 0..1, default=0.8, (1 is the fastest)

   // atmospheric sky
   SkyClass& atmospheric                (                     );                                                                   // enable  drawing sky as atmospheric sky
   SkyClass& atmosphericDensityExponent (  Flt       exp      );   Flt         atmosphericDensityExponent ()C {return _dns_exp  ;} // set/get density exponent        ,            0..1                   , default=1, (1 is the fastest)
   SkyClass& atmosphericHorizonExponent (  Flt       exp      );   Flt         atmosphericHorizonExponent ()C {return _hor_exp  ;} // set/get horizon exponent        ,            0..Inf                 , default=4, (this affects at what height the horizon color will be selected instead of the sky color)
   SkyClass& atmosphericHorizonColor    (C Vec4     &color    );   Vec4        atmosphericHorizonColor    ()C {return _hor_col  ;} // set/get horizon color           ,    (0,0,0,0)..(1,1,1,1)           , default=(0.40, 0.48, 0.64, 1.0) here alpha specifies opacity to combine with star map when used
   SkyClass& atmosphericSkyColor        (C Vec4     &color    );   Vec4        atmosphericSkyColor        ()C {return _sky_col  ;} // set/get sky     color           ,    (0,0,0,0)..(1,1,1,1)           , default=(0.27, 0.34, 0.49, 0.9) here alpha specifies opacity to combine with star map when used
   SkyClass& atmosphericStars           (C ImagePtr &cube     );   C ImagePtr& atmosphericStars           ()C {return _stars    ;} // set/get sky     star map        , image must be in IMAGE_CUBE format, default=NULL
   SkyClass& atmosphericStarsOrientation(C Matrix3  &orn      );   Matrix3     atmosphericStarsOrientation()C {return _stars_m  ;} // set/get sky     star orientation, 'orn' must be normalized          , default=MatrixIdentity3
   SkyClass& atmosphericPrecision       (  Bool      per_pixel);   Bool        atmosphericPrecision       ()C {return _precision;} // set/get sky     precision       ,          true/false               , default=true (false for OpenGL ES), if false is set then sky calculations are done per-vertex with lower quality

   SkyClass& atmosphericColor(C Vec4 &horizon_color, C Vec4 &sky_color) {return atmosphericHorizonColor(horizon_color).atmosphericSkyColor(sky_color);} // set atmospheric horizon and sky color

   // sky from skybox
   SkyClass& skybox     (C ImagePtr &image           );   C ImagePtr &skybox     ()C {return _image[0] ;} // enable drawing sky as skybox
   SkyClass& skybox     (C ImagePtr &a, C ImagePtr &b);   C ImagePtr &skybox2    ()C {return _image[1] ;} // enable drawing sky as blend between 2 skyboxes
   SkyClass& skyboxBlend(  Flt       blend           );   Flt         skyboxBlend()C {return _box_blend;} // set/get blend factor between 2 skyboxes, 0..1, default=0.5

   SkyClass();

private:
   Bool       _is, _precision;
   Flt        _frac, _dns_exp, _hor_exp, _box_blend;
   Vec4       _hor_col, _sky_col;
   Matrix3    _stars_m;
   MeshRender _mshr;
   ImagePtr   _image[2], _stars;
};extern SkyClass
   Sky; // Main Sky
/******************************************************************************/

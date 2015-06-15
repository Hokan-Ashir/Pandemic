/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
struct LayeredClouds
{
   struct Layer // Cloud Layer
   {
      Color    color   ; // texture color   ,          , default=WHITE
      Flt      scale   ; // texture scale   ,    0..Inf, default={0.35, 0.41, 0.50, 0.62}
      Vec2     position, // texture position, -Inf..Inf,
               velocity; // texture velocity, -Inf..Inf, default={0.010, 0.008, 0.006, 0.004}
      ImagePtr image   ; // texture
   };

   Bool  merge_with_sky; // if draw clouds together with the sky, this can result in better performance, but supports only up to 1 layer of clouds and Sky.frac() must be set to 1, this also results in drawing astronomical objects on top of clouds, default=false (true for OpenGL ES)
   Layer layer[4]      ; // layer array

   // set / get
   LayeredClouds& set            (Byte active_layers, C ImagePtr &image=NULL);   Int  layers         ()C {return _layers ;} // set/get number of active layers 0..4, if 'image'!=NULL layers will have 'image' set as their texture
   LayeredClouds& blend          (Bool blend                                );   Bool blend          ()C {return _blend  ;} // set/get blending mode, true for smooth blend, false for fast blend, default=true
   LayeredClouds& scaleY         (Flt  scale                                );   Flt  scaleY         ()C {return _scale_y;} // set/get y scaling                , 1..2  , default=1.05, setting this value higher than 1 helps covering the empty gap between flat ground and the clouds
   LayeredClouds& rayMaskContrast(Flt  contrast                             );   Flt  rayMaskContrast()C {return _rmc    ;} // set/get sun rays masking contrast, 1..Inf, default=4   , this is used when "Sun.rays_mode==SUN_RAYS_HIGH"

   void update(); // update layers, this needs to be called once per frame to update the cloud texture animation movement (move the layer texture positions according to velocities)

private:
   Bool       _blend;
   Byte       _layers;
   Flt        _scale_y, _rmc;
   MeshRender _mshr;
};
/******************************************************************************/
struct VolumetricPoint // Single Volumetric Point parameters
{
   Int  range; // range                        1..Inf
   VecI pos  ; // position on cloud grid (0,0,0)..(255,31,255)
};
struct VolumetricClouds
{
   // non saveable
   Byte     res   ; // resolution           , 0..2, default=1   , 0=full size, 1=half size, 2=quarter size
   ImagePtr cloud , // clouds image         ,       default=NULL
            detail; // clouds detail texture,       default=NULL

   // saveable
   Flt  density     , // density      ,           0..Inf      , default=3.0
        shadow      , // shadow amount,           0..1        , default=0.5
        scale       , // scale        ,           0..Inf      , default=0.25
        curve       , // curviness    ,           0..1        , default=0.03
        height      ; // height       ,           0..Inf      , default=0.77
   Vec2 pos         ; // position     , (-Inf,-Inf)..(Inf,Inf), default=(0,0)
   Vec    dark_color, // dark   color ,     (0,0,0)..(1,1,1)  , default=(0.38,0.38,0.38)
        bright_color; // bright color ,     (0,0,0)..(1,1,1)  , default=(0.70,0.70,0.70)

   // manage
   void set(C ImagePtr &cloud, C ImagePtr &detail) {T.cloud=cloud; T.detail=detail;} // set images

   // update
   void update(C Vec2 &vel); // update, 'vel'=clouds velocity

   // io
   Bool save(C Str &name); // save, false on fail
   Bool load(C Str &name); // load, false on fail

   VolumetricClouds();
};
/******************************************************************************/
struct AllClouds
{
      LayeredClouds layered   ;
   VolumetricClouds volumetric;
}extern
   Clouds;
/******************************************************************************/
void CreateVolumetricDetail(              Image &detail, Int x,Int y,Int z                                                                    ); // create volumetric detail image, x*y*z sized (sizes will be rounded to the nearest power of 2)
void CreateVolumetricCloud (Image &image, Image *detail, Int x,Int y,Int z, Byte blurs, Bool clamp_xz, Int points, VolumetricPoint *point=NULL); // create volumetric cloud  image, x*y*z sized (sizes will be rounded to the nearest power of 2), 'detail'=additional image data to adjust the cloud image, image will be blurred 'blur' number of times, 'clamp_xz'=if the cloud image should be clamped in XZ dimensions, 'points'=number of control points where the cloud should be most dense, 'point'=array of control points (if this is set to NULL, random points will be used)
/******************************************************************************/

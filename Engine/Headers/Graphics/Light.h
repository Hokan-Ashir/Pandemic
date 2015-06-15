/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'LightDir'   to add a directional light onto the scene
   Use 'LightPoint' to add a point       light onto the scene
   Use 'LightSqr'   to add a point       light onto the scene (with small range)
   Use 'LightCone'  to add a cone        light onto the scene

   Access 'CurrentLight' to gain informations about the current light which is being applied.

/******************************************************************************/
enum LIGHT_TYPE // Light Type
{
   LIGHT_NONE , // none
   LIGHT_DIR  , // directional
   LIGHT_POINT, // point
   LIGHT_SQR  , // point with small range
   LIGHT_CONE , // cone
};
/******************************************************************************/
struct LightDir // Directional Light
{
   Vec dir         , // direction          , normalized vector
       color       ; // color              , (0,0,0) .. (1,1,1)
   Flt vol         , // volumetric amount  , (0..1  )
       vol_exponent, // volumetric exponent, (0..Inf)
       vol_steam   ; // volumetric steam   , (0..1  )

   void add(Bool shadows=true, CPtr light_src=NULL); // add light to scene, this needs to be called only in RM_PREPARE mode, 'shadows'=if shadowing enabled, 'light_src'=custom pointer to light source (which can be later accessed from "CurrentLight.src")
   void set(                                      ); // use only outside Renderer rendering, before drawing any shade'able meshes

   LightDir() {}
   LightDir(C Vec &dir, C Vec &color=Vec(1, 1, 1), Flt vol=0, Flt vol_exponent=1, Flt vol_steam=0.5f) {T.dir=dir; T.color=color; T.vol=vol; T.vol_exponent=vol_exponent; T.vol_steam=vol_steam;}
};
/******************************************************************************/
struct LightPoint // Point Light
{
   Flt power  , // power             , (0..Inf), determines light range
       vol    , // volumetric amount , (0..Inf)
       vol_max; // volumetric maximum, (0..1  )
   Vec pos    , // position          ,
       color  ; // color             , (0,0,0) .. (1,1,1)

   Flt  range(                                             )C; // get affected range according to light's 'power'
   void add  (Flt shadows_opacity=1.0f, CPtr light_src=NULL) ; // add light to scene, this needs to be called only in RM_PREPARE mode, 'shadows_opacity'=opacity of shadows (0..1) where value 0 disables shadowing, value 1 sets full shadows, and values between allow for manual blending the shadows, 'light_src'=custom pointer to light source (which can be later accessed from "CurrentLight.src")

   LightPoint() {}
   LightPoint(Flt power, C Vec &pos, C Vec &color=Vec(1, 1, 1), Flt vol=0, Flt vol_max=0.5f) {T.power=power; T.pos=pos; T.color=color; T.vol=vol; T.vol_max=vol_max;}
};
/******************************************************************************/
struct LightSqr // Point Light with small range
{
   Flt range  , // range             , (0..Inf)
       vol    , // volumetric amount , (0..Inf)
       vol_max; // volumetric maximum, (0..1  )
   Vec pos    , // position          ,
       color  ; // color             , (0,0,0) .. (1,1,1)

   void add(Flt shadows_opacity=1.0f, CPtr light_src=NULL); // add light to scene, this needs to be called only in RM_PREPARE mode, 'shadows_opacity'=opacity of shadows (0..1) where value 0 disables shadowing, value 1 sets full shadows, and values between allow for manual blending the shadows, 'light_src'=custom pointer to light source (which can be later accessed from "CurrentLight.src")

   LightSqr() {}
   LightSqr(Flt range, C Vec &pos, C Vec &color=Vec(1, 1, 1), Flt vol=0, Flt vol_max=0.5f) {T.range=range; T.pos=pos; T.color=color; T.vol=vol; T.vol_max=vol_max;}
};
/******************************************************************************/
struct LightCone // Cone Light
{
   Flt     falloff, // light falloff     , (0..1  ), default=0.5
           vol    , // volumetric amount , (0..Inf)
           vol_max; // volumetric maximum, (0..1  )
   Vec     color  ; // color             , (0,0,0) .. (1,1,1)
   Pyramid pyramid; // pyramid           , determines orientation of the light

   void add(Flt shadows_opacity=1.0f, CPtr light_src=NULL, Image *image=NULL, Flt image_scale=1, C Color &image_add=TRANSPARENT, Flt image_specular=0); // add light to scene, this needs to be called only in RM_PREPARE mode, 'shadows_opacity'=opacity of shadows (0..1) where value 0 disables shadowing, value 1 sets full shadows, and values between allow for manual blending the shadows, 'light_src'=custom pointer to light source (which can be later accessed from "CurrentLight.src"), 'image'=dynamic lightmap, 'image_add'=add color to dynamic lightmap, 'image_scale'=scale dynamic lightmap, 'image_specular'=specular of dynamic lightmap

   LightCone() {}
   LightCone(Flt length, C Vec &pos, C Vec &dir, C Vec &color=Vec(1, 1, 1), Flt vol=0, Flt vol_max=0.5f);
};
/******************************************************************************/
struct Light
{
   LIGHT_TYPE type           ; // light type
   Bool       shadows        ; // if shadowing enabled
   Flt        shadows_opacity; // opacity of shadows
   Color      image_add      ; // dynamic lightmap color add
   Flt        image_specular , // dynamic lightmap specular
              image_scale    ; // dynamic lightmap scale
   Rect       rect           ; // on screen rectangle affected by light
   CPtr       src            ; // custom pointer to light source
   Image     *image          ; // dynamic lightmap
   UNION
   (
      UNION_ELM(LightDir   dir  ;) // directional light, valid when "type==LIGHT_DIR  "
      UNION_ELM(LightPoint point;) // point       light, valid when "type==LIGHT_POINT"
      UNION_ELM(LightSqr   sqr  ;) // point       light, valid when "type==LIGHT_SQR  "
      UNION_ELM(LightCone  cone ;) // cone        light, valid when "type==LIGHT_CONE "
   )

   // get / set
   Flt range()C; // get light range    (this is equal to 0       for directional lights)
   Flt vol  ()C; // get light volumetric amount
   Vec pos  ()C; // get light position (this is equal to (0,0,0) for directional lights)
}extern
   CurrentLight; // this contains information about the light which is currently rendered
/******************************************************************************/

/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   4-Byte Colors helper functions.

/******************************************************************************/
struct Color // 4-Byte Color
{
   union
   {
      struct{Byte r, g, b, a;}; // red, green, blue, alpha
      struct{Byte c[4]      ;}; // component
   };

   Color& zero(                                               ) {r=g=b=a=0; return T;}
   Color& set (Byte red, Byte green, Byte blue, Byte alpha=255) {T.r=red; T.g=green; T.b=blue; T.a=alpha; return T;}
   Color& set (Byte lum,                        Byte alpha=255) {T.r=     T.g=       T.b=lum ; T.a=alpha; return T;}

   Bool any()C {return r || g || b || a;} // if any component is non-zero
   Int  lum()C {return Max(r, g, b)    ;} // get luminance

   Vec   asVec  ()C; // return as Color in Vec   format (x=red, y=green, z=blue         )
   Vec4  asVec4 ()C; // return as Color in Vec4  format (x=red, y=green, z=blue, w=alpha)
   VecB4 asVecB4()C; // return as Color in VecB4 format (x=red, y=green, z=blue, w=alpha)

   Str asText()C; // return as text in following format "r, g, b, a" (using     decimal numbers)
   Str asHex ()C; // return as text in following format "rrggbbaa"   (using hexadecimal numbers)

   Bool fromHex(C Str &t); // set from "rrggbbaa" text format (using hexadecimal numbers), false on fail

   Bool operator==(C Color &c)C {return r==c.r && g==c.g && b==c.b && a==c.a;}
   Bool operator!=(C Color &c)C {return r!=c.r || g!=c.g || b!=c.b || a!=c.a;}

   Color() {}
   Color(Byte red, Byte green, Byte blue, Byte alpha=255) {set(red, green, blue, alpha);}
   Color(Byte lum,                        Byte alpha=255) {set(lum,              alpha);}
   Color(C Vec   &color); // initialize from RGB  color in 0.0 .. 1.0 scale (alpha will be set to full)
   Color(C Vec4  &color); // initialize from RGBA color in 0.0 .. 1.0 scale
   Color(C VecB4 &color); // initialize from RGBA color taken from XYZW
};
const Color
   BLACK (  0,   0,   0),
   GREY  (128, 128, 128),
   WHITE (255, 255, 255),
   RED   (255,   0,   0),
   GREEN (  0, 255,   0),
   BLUE  (  0,   0, 255),
   YELLOW(255, 255,   0),
   CYAN  (  0, 255, 255),
   PURPLE(255,   0, 255),
   ORANGE(255, 128,   0),
   TURQ  (  0, 128, 255),
   PINK  (255, 128, 255),
   BROWN (128,  64,   0),
   TRANSPARENT(0, 0, 0, 0);
/******************************************************************************/
Color ColorI(Int i); // get one of the few major colors based on 'i' index, for example: ColorI(0)->RED, ColorI(1)->GREEN, ColorI(2)->BLUE, ...

Color ColorInverse   (C Color &color                              ); // get inversed color                               , (1-r         , 1-g         , 1-b         , a       )
Color ColorBrightness(                Flt brightness              ); // get color from        brightness             0..1, (  brightness,   brightness,   brightness, 1       )
Color ColorBrightness(C Color &color, Flt brightness              ); // get color modified by brightness             0..1, (r*brightness, g*brightness, b*brightness, a       )
Color ColorAlpha     (                                Flt alpha   ); // get color from                       opacity 0..1, (1           , 1           , 1           ,   alpha )
Color ColorAlpha     (C Color &color,                 Flt alpha   ); // get color modified by                opacity 0..1, (r           , g           , b           , a*alpha )
Color ColorBA        (                Flt brightness, Flt alpha   ); // get color from        brightness and opacity 0..1, (  brightness,   brightness,   brightness,   alpha )
Color ColorBA        (C Color &color, Flt brightness, Flt alpha   ); // get color modified by brightness and opacity 0..1, (r*brightness, g*brightness, b*brightness, a*alpha )
Color ColorMul       (                Flt mul                     ); // get                                              , (  mul       ,   mul       ,   mul       ,   mul   )
Color ColorMul       (C Color &color, Flt mul                     ); // get                                              , (r*mul       , g*mul       , b*mul       , a*mul   )
Color ColorMul       (C Color &col0 , C Color &col1               ); // get                                              , (r0*r1       , g0*g1       , b0*b1       , a0*a1   )
Color ColorMul       (C Color &col0 , C Color &col1, C Color &col2); // get                                              , (r0*r1*r2    , g0*g1*g2    , b0*b1*b2    , a0*a1*a2)
Color ColorAdd       (C Color &col0 , C Color &col1               ); // get                                              , (r0+r1       , g0+g1       , b0+b1       , a0+a1   )
Color ColorAdd       (C Color &col0 , C Color &col1, C Color &col2); // get                                              , (r0+r1+r2    , g0+g1+g2    , b0+b1+b2    , a0+a1+a2)

Color Avg (C Color &c0, C Color &c1                           ); // get average color of c0, c1
Color Avg (C Color &c0, C Color &c1, C Color &c2              ); // get average color of c0, c1, c2
Color Avg (C Color &c0, C Color &c1, C Color &c2, C Color &c3 ); // get average color of c0, c1, c2, c3
Color Lerp(C Color &c0, C Color &c1,              Flt    step ); // linear interpolation between colors, returns Lerp(c0, c1, step)
Color Lerp(C Color &c0, C Color &c1, C Color &c2, C Vec &blend); // linear interpolation between colors, returns c0*blend.x + c1*blend.y + c2*blend.z

Color ColorHue(                Flt hue); // get color from        hue (0..1) = red->yellow->green->cyan->blue->purple->red
Color ColorHue(C Color &color, Flt hue); // get color modified by hue offset
Color ColorHSB(Flt h, Flt s, Flt b    ); // get color from hue, saturation, brightness (all in range 0..1)
Vec   RgbToHsb(C Vec &rgb             ); // convert from RGB to HSB
Vec   HsbToRgb(C Vec &hsb             ); // convert from HSB to RGB

Int ColorDiffSum(C Color &x, C Color &y); // get difference between colors as a sum of all channel absolute differences
Int ColorDiffMax(C Color &x, C Color &y); // get difference between colors as a max of all channel absolute differences

Color        Blend(C Color &base, C Color &color); // return 'color'            blended on top of 'base'
Vec4         Blend(C Vec4  &base, C Vec4  &color); // return 'color'            blended on top of 'base'
Vec4 AdditiveBlend(C Vec4  &base, C Vec4  &color); // return 'color' additively blended on top of 'base'
/******************************************************************************/

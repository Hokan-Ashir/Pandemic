/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
enum DIST_TYPE // Distance Type
{
   DIST_NONE  , // none
   DIST_POINT0, // 0th point
   DIST_POINT1, // 1st point
   DIST_POINT2, // 2nd point
   DIST_POINT3, // 3rd point
   DIST_EDGE0 , // 0th edge
   DIST_EDGE1 , // 1st edge
   DIST_EDGE2 , // 2nd edge
   DIST_EDGE3 , // 3rd edge
   DIST_PLANE , // plane
   DIST_TRI   , // triangle
   DIST_QUAD  , // quad

   DIST_POINT=DIST_POINT0, // point
   DIST_EDGE =DIST_EDGE0 , // edge
};
/******************************************************************************/
Bool Special(C Flt &r); // if 'r' is a special type float  (NaN, -Inf, +Inf)
Bool Special(C Dbl &r); // if 'r' is a special type double (NaN, -Inf, +Inf)
Bool NaN    (C Flt &r); // if 'r' is Not a Number
Bool NaN    (C Dbl &r); // if 'r' is Not a Number
Bool Inf    (C Flt &r); // if 'r' is Infinite
Bool Inf    (C Dbl &r); // if 'r' is Infinite

// change sign
inline void CHS(Int  &x) {x=-x;}
inline void CHS(Long &x) {x=-x;}
inline void CHS(Flt  &x) {((U32&) x)   ^=SIGN_BIT;} // equal to "x=-x;" but faster
inline void CHS(Dbl  &x) {((U32*)&x)[1]^=SIGN_BIT;} // equal to "x=-x;" but faster

// get absolute value
inline Int   Abs(  Int    x) {return (x>=0) ? x : -x;}
inline Long  Abs(  Long   x) {return (x>=0) ? x : -x;}
inline Flt   Abs(  Flt    x) {return (x>=0) ? x : -x;}
inline Dbl   Abs(  Dbl    x) {return (x>=0) ? x : -x;}
inline Vec2  Abs(C Vec2  &v) {return Vec2 (Abs(v.x), Abs(v.y)                    );}
inline VecD2 Abs(C VecD2 &v) {return VecD2(Abs(v.x), Abs(v.y)                    );}
inline VecI2 Abs(C VecI2 &v) {return VecI2(Abs(v.x), Abs(v.y)                    );}
inline Vec   Abs(C Vec   &v) {return Vec  (Abs(v.x), Abs(v.y), Abs(v.z)          );}
inline VecD  Abs(C VecD  &v) {return VecD (Abs(v.x), Abs(v.y), Abs(v.z)          );}
inline VecI  Abs(C VecI  &v) {return VecI (Abs(v.x), Abs(v.y), Abs(v.z)          );}
inline Vec4  Abs(C Vec4  &v) {return Vec4 (Abs(v.x), Abs(v.y), Abs(v.z), Abs(v.w));}
inline VecD4 Abs(C VecD4 &v) {return VecD4(Abs(v.x), Abs(v.y), Abs(v.z), Abs(v.w));}
inline VecI4 Abs(C VecI4 &v) {return VecI4(Abs(v.x), Abs(v.y), Abs(v.z), Abs(v.w));}

// make absolute value
inline void ABS(Int  &x) {if(x<0)x=-x;}              // equal to "x=Abs(x);"
inline void ABS(Long &x) {if(x<0)x=-x;}              // equal to "x=Abs(x);"
inline void ABS(Flt  &x) {((U32&) x)   &=~SIGN_BIT;} // equal to "x=Abs(x);"
inline void ABS(Dbl  &x) {((U32*)&x)[1]&=~SIGN_BIT;} // equal to "x=Abs(x);"

// get middle value
inline Int  Mid(  Int   x,   Int   min,   Int   max) {return (x>=max) ? max : (x<=min) ? min : x;}
inline Long Mid(  Long  x,   Long  min,   Long  max) {return (x>=max) ? max : (x<=min) ? min : x;}
inline Flt  Mid(  Flt   x,   Flt   min,   Flt   max) {return (x>=max) ? max : (x<=min) ? min : x;}
inline Dbl  Mid(  Dbl   x,   Dbl   min,   Dbl   max) {return (x>=max) ? max : (x<=min) ? min : x;}
inline Vec2 Mid(C Vec2 &v, C Vec2 &min, C Vec2 &max) {return Vec2(Mid(v.x, min.x, max.x), Mid(v.y, min.y, max.y)                                                );}
inline Vec  Mid(C Vec  &v, C Vec  &min, C Vec  &max) {return Vec (Mid(v.x, min.x, max.x), Mid(v.y, min.y, max.y), Mid(v.z, min.z, max.z)                        );}
inline Vec4 Mid(C Vec4 &v, C Vec4 &min, C Vec4 &max) {return Vec4(Mid(v.x, min.x, max.x), Mid(v.y, min.y, max.y), Mid(v.z, min.z, max.z), Mid(v.w, min.w, max.w));}

// get saturated (clamped to 0..1)
inline Int   Sat(  Int    x) {return Mid(x, 0   , 1   );}
inline Long  Sat(  Long   x) {return Mid(x, 0LL , 1LL );}
inline Flt   Sat(  Flt    x) {return Mid(x, 0.0f, 1.0f);}
inline Dbl   Sat(  Dbl    x) {return Mid(x, 0.0 , 1.0 );}
inline Vec2  Sat(C Vec2  &v) {return Vec2 (Sat(v.x), Sat(v.y)                    );}
inline VecD2 Sat(C VecD2 &v) {return VecD2(Sat(v.x), Sat(v.y)                    );}
inline Vec   Sat(C Vec   &v) {return Vec  (Sat(v.x), Sat(v.y), Sat(v.z)          );}
inline VecD  Sat(C VecD  &v) {return VecD (Sat(v.x), Sat(v.y), Sat(v.z)          );}
inline Vec4  Sat(C Vec4  &v) {return Vec4 (Sat(v.x), Sat(v.y), Sat(v.z), Sat(v.w));}
inline VecD4 Sat(C VecD4 &v) {return VecD4(Sat(v.x), Sat(v.y), Sat(v.z), Sat(v.w));}

// make saturated (clamp to 0..1)
inline Int & SAT(Int  &x) {return x=Sat(x);}
inline Long& SAT(Long &x) {return x=Sat(x);}
inline Flt & SAT(Flt  &x) {return x=Sat(x);}
inline Dbl & SAT(Dbl  &x) {return x=Sat(x);}

// sign
inline Int   SignBool(  Bool   x              ) {return  x      ? 1 :            -1    ;} // sign from Bool
inline Int   Sign    (  Int    x              ) {return (x>  0) ? 1 : (x<   0) ? -1 : 0;} // sign
inline Int   Sign    (  Long   x              ) {return (x>  0) ? 1 : (x<   0) ? -1 : 0;} // sign
inline Int   Sign    (  Flt    x              ) {return (x>  0) ? 1 : (x<   0) ? -1 : 0;} // sign
inline Int   Sign    (  Dbl    x              ) {return (x>  0) ? 1 : (x<   0) ? -1 : 0;} // sign
inline VecI2 Sign    (C VecI2 &v              ) {return VecI2(Sign(v.x), Sign(v.y)                      );}
inline VecI  Sign    (C VecI  &v              ) {return VecI (Sign(v.x), Sign(v.y), Sign(v.z)           );}
inline VecI4 Sign    (C VecI4 &v              ) {return VecI4(Sign(v.x), Sign(v.y), Sign(v.z), Sign(v.w));}
inline VecI2 Sign    (C Vec2  &v              ) {return VecI2(Sign(v.x), Sign(v.y)                      );}
inline VecI  Sign    (C Vec   &v              ) {return VecI (Sign(v.x), Sign(v.y), Sign(v.z)           );}
inline VecI4 Sign    (C Vec4  &v              ) {return VecI4(Sign(v.x), Sign(v.y), Sign(v.z), Sign(v.w));}
inline Int   SignEps (  Flt    x, Flt eps=EPS ) {return (x>eps) ? 1 : (x<-eps) ? -1 : 0;} // sign using epsilon
inline Int   SignEps (  Dbl    x, Dbl eps=EPSD) {return (x>eps) ? 1 : (x<-eps) ? -1 : 0;} // sign using epsilon

inline Flt ScaleFactor (Flt x) {return (x>=0) ? (1+x) : (1/(1-x));} // get scaling factor from linear  value
inline Flt ScaleFactorR(Flt s) {return (s>=1) ? (s-1) : (1-(1/s));} // get linear  value  from scaling factor

Vec2 ScaleFactor(C Vec2 &vec);
Vec  ScaleFactor(C Vec  &vec);
Vec4 ScaleFactor(C Vec4 &vec);

inline Int  Sqr  (  Int   x) {return x*x  ;} // square
inline Flt  Sqr  (  Flt   x) {return x*x  ;} // square
inline Dbl  Sqr  (  Dbl   x) {return x*x  ;} // square
inline Vec2 Sqr  (C Vec2 &x) {return x*x  ;} // square
inline Vec  Sqr  (C Vec  &x) {return x*x  ;} // square
inline Vec4 Sqr  (C Vec4 &x) {return x*x  ;} // square
inline Int  Cube (  Int   x) {return x*x*x;} // cube
inline Flt  Cube (  Flt   x) {return x*x*x;} // cube
inline Dbl  Cube (  Dbl   x) {return x*x*x;} // cube
       Flt Sqrt (Int x);                // square root, 0 on fail
       Flt Sqrt (Flt x);                // square root, 0 on fail
       Dbl Sqrt (Dbl x);                // square root, 0 on fail
       Flt Cbrt (Int x);                // cube   root
       Flt Cbrt (Flt x);                // cube   root
       Dbl Cbrt (Dbl x);                // cube   root
       Flt Pow  (Flt x, Flt y);         // power x^y
       Dbl Pow  (Dbl x, Dbl y);         // power x^y
       Flt Ln   (Flt x);                // e-base logarithm
       Dbl Ln   (Dbl x);                // e-base logarithm
       Flt Log2 (Flt x);                // 2-base logarithm
       Dbl Log2 (Dbl x);                // 2-base logarithm
       Flt Log  (Flt x, Flt base );     //        logarithm
       Dbl Log  (Dbl x, Dbl base );     //        logarithm
       Flt Pinch(Flt x, Flt pinch);     // pinch, 'x'=0..1, 'pinch'=0..Inf (<1 makes the curve start slow and accelerate, 1 makes the curve linear, >1 makes the curve start fast and deccelerate)

// calculate squared distance of coordinates from point zero
inline Int Dist2(Int x, Int y              ) {return x*x + y*y            ;}
inline Flt Dist2(Flt x, Flt y              ) {return x*x + y*y            ;}
inline Dbl Dist2(Dbl x, Dbl y              ) {return x*x + y*y            ;}
inline Int Dist2(Int x, Int y, Int z       ) {return x*x + y*y + z*z      ;}
inline Flt Dist2(Flt x, Flt y, Flt z       ) {return x*x + y*y + z*z      ;}
inline Dbl Dist2(Dbl x, Dbl y, Dbl z       ) {return x*x + y*y + z*z      ;}
inline Flt Dist2(Flt x, Flt y, Flt z, Flt w) {return x*x + y*y + z*z + w*w;}

// calculate distance of coordinates from point zero
inline Flt Dist(Int x, Int y       ) {return Sqrt(Dist2(x, y   ));}
inline Flt Dist(Flt x, Flt y       ) {return Sqrt(Dist2(x, y   ));}
inline Dbl Dist(Dbl x, Dbl y       ) {return Sqrt(Dist2(x, y   ));}
inline Flt Dist(Int x, Int y, Int z) {return Sqrt(Dist2(x, y, z));}
inline Flt Dist(Flt x, Flt y, Flt z) {return Sqrt(Dist2(x, y, z));}
inline Dbl Dist(Dbl x, Dbl y, Dbl z) {return Sqrt(Dist2(x, y, z));}

// density
Flt       SplitAlpha  (Flt alpha  , Int steps); // calculate alpha to be used for drawing graphics using 'steps' amount of steps to generate the same results as when drawing with 'alpha' using only 1 step
Flt     VisibleOpacity(Flt density, Flt range); // calculate visible     opacity (0..1) having 'density' environment density (0..1), and 'range' (0..Inf)
Flt AccumulatedDensity(Flt density, Flt range); // calculate accumulated density (0..1) having 'density' environment density (0..1), and 'range' (0..Inf)
/******************************************************************************/
// ANGLES
/******************************************************************************/
       Flt  Sin    (Flt angle); // get   sine of angle, -1..1
       Dbl  Sin    (Dbl angle); // get   sine of angle, -1..1
       Flt  Cos    (Flt angle); // get cosine of angle, -1..1
       Dbl  Cos    (Dbl angle); // get cosine of angle, -1..1
       void SinCos (Flt &sin, Flt &cos, Flt angle); // get sine and cosine of angle, sin=Sin(angle), cos=Cos(angle)
       void SinCos (Dbl &sin, Dbl &cos, Dbl angle); // get sine and cosine of angle, sin=Sin(angle), cos=Cos(angle)
       Flt  Tan    (Flt angle); // get   tangent "sin/cos" of angle, -Inf..Inf
       Dbl  Tan    (Dbl angle); // get   tangent "sin/cos" of angle, -Inf..Inf
       Flt  Ctg    (Flt angle); // get cotangent "cos/sin" of angle, -Inf..Inf
       Dbl  Ctg    (Dbl angle); // get cotangent "cos/sin" of angle, -Inf..Inf
       Flt  Acos   (Flt cos  ); // get arc  cosine (angle which has specified  cosine),     0..PI
       Dbl  Acos   (Dbl cos  ); // get arc  cosine (angle which has specified  cosine),     0..PI
       Flt  Asin   (Flt sin  ); // get arc    sine (angle which has specified    sine), -PI_2..PI_2
       Dbl  Asin   (Dbl sin  ); // get arc    sine (angle which has specified    sine), -PI_2..PI_2
       Flt  Atan   (Flt tan  ); // get arc tangent (angle which has specified tangent), -PI_2..PI_2
       Dbl  Atan   (Dbl tan  ); // get arc tangent (angle which has specified tangent), -PI_2..PI_2
       Flt  Angle  (C Vec2  &v, Bool fast=false); // get point angle (-PI..PI), when 'fast' is enabled - the result is an approximation which is calculated faster, use it mainly for comparing angles
       Dbl  Angle  (C VecD2 &v                 ); // get point angle (-PI..PI)
       Flt  Angle  (C Vec   &v,                 C Vec &x, C Vec &y, Bool fast=false);                                                         // get point angle according to given axes            (-PI..PI)
inline Flt  Angle  (C Vec   &v, C Vec     &pos, C Vec &x, C Vec &y, Bool fast=false) {return Angle(v-pos,                x,        y, fast);} // get point angle according to given axes and center (-PI..PI)
inline Flt  Angle  (C Vec   &v, C Matrix3 &matrix                 , Bool fast=false) {return Angle(v            , matrix.x, matrix.y, fast);} // get point angle according to given matrix          (-PI..PI)
inline Flt  AngleXZ(C Vec   &v, C Matrix3 &matrix                 , Bool fast=false) {return Angle(v            , matrix.x, matrix.z, fast);} // get point angle according to given matrix          (-PI..PI)
inline Flt  Angle  (C Vec   &v, C Matrix  &matrix                 , Bool fast=false) {return Angle(v, matrix.pos, matrix.x, matrix.y, fast);} // get point angle according to given matrix          (-PI..PI)
inline Flt  AngleXZ(C Vec   &v, C Matrix  &matrix                 , Bool fast=false) {return Angle(v, matrix.pos, matrix.x, matrix.z, fast);} // get point angle according to given matrix          (-PI..PI)

inline Flt AngleFull     (Flt angle       ) {return Frac(angle, PI2 );}       // normalize angle to   0..PI2 (wrap angle to   0..PI2 range)
inline Dbl AngleFull     (Dbl angle       ) {return Frac(angle, PID2);}       // normalize angle to   0..PI2 (wrap angle to   0..PI2 range)
       Flt AngleNormalize(Flt angle       );                                  // normalize angle to -PI..PI  (wrap angle to -PI..PI  range)
       Dbl AngleNormalize(Dbl angle       );                                  // normalize angle to -PI..PI  (wrap angle to -PI..PI  range)
inline Flt AngleDelta    (Flt from, Flt to) {return AngleNormalize(to-from);} // get angle delta    -PI..PI  (difference between angles wrapped to -PI..PI range)
inline Dbl AngleDelta    (Dbl from, Dbl to) {return AngleNormalize(to-from);} // get angle delta    -PI..PI  (difference between angles wrapped to -PI..PI range)

inline Flt SinCos(Flt sin_cos) {return Sqrt(1-sin_cos*sin_cos);} // convert sin<->cos, this function converts sine value to cosine value (of the same angle), and cosine value to sine value (of the same angle) at the same time
inline Dbl SinCos(Dbl sin_cos) {return Sqrt(1-sin_cos*sin_cos);} // convert sin<->cos, this function converts sine value to cosine value (of the same angle), and cosine value to sine value (of the same angle) at the same time

// angle between vectors
       Flt    AngleBetween(C Vec2  &a, C Vec2  &b);                                  // -PI..PI, 'a b'=direction vectors (they don't need to be normalized)
       Dbl    AngleBetween(C VecD2 &a, C VecD2 &b);                                  // -PI..PI, 'a b'=direction vectors (they don't need to be normalized)
inline Flt AbsAngleBetween(C Vec2  &a, C Vec2  &b) {return Abs(AngleBetween(a, b));} //   0..PI, 'a b'=direction vectors (they don't need to be normalized)
inline Dbl AbsAngleBetween(C VecD2 &a, C VecD2 &b) {return Abs(AngleBetween(a, b));} //   0..PI, 'a b'=direction vectors (they don't need to be normalized)
       Flt AbsAngleBetween(C Vec   &a, C Vec   &b);                                  //   0..PI, 'a b'=direction vectors (they don't need to be normalized)
       Dbl AbsAngleBetween(C VecD  &a, C VecD  &b);                                  //   0..PI, 'a b'=direction vectors (they don't need to be normalized)
       Flt    AngleBetween(C Vec   &a, C Vec   &b, C Vec  &z);                       // -PI..PI, 'a b'=direction vectors (they don't need to be normalized), 'z'=forward axis orientation (it doesn't need to be normalized)
       Dbl    AngleBetween(C VecD  &a, C VecD  &b, C VecD &z);                       // -PI..PI, 'a b'=direction vectors (they don't need to be normalized), 'z'=forward axis orientation (it doesn't need to be normalized)

// cos of angle between vectors
Flt CosBetween(C Vec2  &a, C Vec2  &b); // -1..1
Dbl CosBetween(C VecD2 &a, C VecD2 &b); // -1..1
Flt CosBetween(C Vec   &a, C Vec   &b); // -1..1
Dbl CosBetween(C VecD  &a, C VecD  &b); // -1..1

// sin of angle between vectors
Flt    SinBetween(C Vec2  &a, C Vec2  &b); // -1..1
Dbl    SinBetween(C VecD2 &a, C VecD2 &b); // -1..1
Flt AbsSinBetween(C Vec   &a, C Vec   &b); //  0..1
Dbl AbsSinBetween(C VecD  &a, C VecD  &b); //  0..1
/******************************************************************************/
// BLENDING
/******************************************************************************/
// get smooth curves that start slowly from 0, accelerate, and slow down to 1
Flt SmoothSqr   (Flt x           );
Flt SmoothCube  (Flt x           );
Flt SmoothCube2 (Flt x           );
Flt SmoothSextic(Flt x           );
Flt SmoothSin   (Flt x           );
Flt SmoothPow   (Flt x, Flt pow  );
Flt SmoothPinch (Flt x, Flt pinch);

Flt BlendSqr         (Flt x); // get        square blend value (0..1), basing on the 'x' distance (-1..1), this function returns blend intensity depending on 'x' distance, where highest intensity '1' is returned for "x==0" which smoothly drops to zero when 'x' becoming more away from the '0' position and reaches '-1' or '+1' or greater distances
Flt BlendSmoothCube  (Flt x); // get smooth cubic  blend value (0..1), basing on the 'x' distance (-1..1), this function returns blend intensity depending on 'x' distance, where highest intensity '1' is returned for "x==0" which smoothly drops to zero when 'x' becoming more away from the '0' position and reaches '-1' or '+1' or greater distances
Flt BlendSmoothSextic(Flt x); // get smooth sextic blend value (0..1), basing on the 'x' distance (-1..1), this function returns blend intensity depending on 'x' distance, where highest intensity '1' is returned for "x==0" which smoothly drops to zero when 'x' becoming more away from the '0' position and reaches '-1' or '+1' or greater distances

Flt  SmoothOffset(Flt  &offset, Flt max_length);
Vec2 SmoothOffset(Vec2 &offset, Flt max_length);
Vec  SmoothOffset(Vec  &offset, Flt max_length);
/******************************************************************************/
// INTERPOLATION
/******************************************************************************/
// get tangent, based on previous and next value
Flt  GetTangent   (  Flt   prev,   Flt   next);
Vec2 GetTangent   (C Vec2 &prev, C Vec2 &next);
Vec  GetTangent   (C Vec  &prev, C Vec  &next);
Vec4 GetTangent   (C Vec4 &prev, C Vec4 &next);
Vec2 GetTangentDir(C Vec2 &prev, C Vec2 &next); // get tangent for direction vectors
Vec  GetTangentDir(C Vec  &prev, C Vec  &next); // get tangent for direction vectors

// linear interpolation, 'step'=0..1
inline Flt   Lerp(  Int    from,   Int    to, Flt step) {return from+step*(to-from);}
inline Flt   Lerp(  Flt    from,   Flt    to, Flt step) {return from+step*(to-from);}
inline Dbl   Lerp(  Dbl    from,   Dbl    to, Dbl step) {return from+step*(to-from);}
inline Vec2  Lerp(C Vec2  &from, C Vec2  &to, Flt step) {return from+step*(to-from);}
inline VecD2 Lerp(C VecD2 &from, C VecD2 &to, Dbl step) {return from+step*(to-from);}
inline Vec   Lerp(C Vec   &from, C Vec   &to, Flt step) {return from+step*(to-from);}
inline VecD  Lerp(C VecD  &from, C VecD  &to, Dbl step) {return from+step*(to-from);}
inline Vec4  Lerp(C Vec4  &from, C Vec4  &to, Flt step) {return from+step*(to-from);}
inline VecD4 Lerp(C VecD4 &from, C VecD4 &to, Dbl step) {return from+step*(to-from);}

// linear interpolation reverse, get interpolation step from value, these functions return 0 if "value==from" and 1 if "value==to", in other cases returned value is interpolated between 0..1
inline Flt LerpR(  Int    from,   Int    to,   Int    value) {return Flt(value-from)/(to-from);}
inline Flt LerpR(  Flt    from,   Flt    to,   Flt    value) {return    (value-from)/(to-from);}
inline Dbl LerpR(  Dbl    from,   Dbl    to,   Dbl    value) {return    (value-from)/(to-from);}
       Flt LerpR(C Vec2  &from, C Vec2  &to, C Vec2  &value);
       Dbl LerpR(C VecD2 &from, C VecD2 &to, C VecD2 &value);
       Flt LerpR(C Vec   &from, C Vec   &to, C Vec   &value);
       Dbl LerpR(C VecD  &from, C VecD  &to, C VecD  &value);
       Flt LerpR(C Vec4  &from, C Vec4  &to, C Vec4  &value);
       Dbl LerpR(C VecD4 &from, C VecD4 &to, C VecD4 &value);

// linear interpolation reverse saturated, get saturated interpolation step from value, these functions return 0 if "value==from" and 1 if "value==to", in other cases returned value is interpolated between 0..1 and clamped to 0..1 range
inline Flt LerpRS(  Int    from,   Int    to,   Int    value) {return Sat(LerpR(from, to, value));}
inline Flt LerpRS(  Flt    from,   Flt    to,   Flt    value) {return Sat(LerpR(from, to, value));}
inline Dbl LerpRS(  Dbl    from,   Dbl    to,   Dbl    value) {return Sat(LerpR(from, to, value));}
inline Flt LerpRS(C Vec2  &from, C Vec2  &to, C Vec2  &value) {return Sat(LerpR(from, to, value));}
inline Dbl LerpRS(C VecD2 &from, C VecD2 &to, C VecD2 &value) {return Sat(LerpR(from, to, value));}
inline Flt LerpRS(C Vec   &from, C Vec   &to, C Vec   &value) {return Sat(LerpR(from, to, value));}
inline Dbl LerpRS(C VecD  &from, C VecD  &to, C VecD  &value) {return Sat(LerpR(from, to, value));}
inline Flt LerpRS(C Vec4  &from, C Vec4  &to, C Vec4  &value) {return Sat(LerpR(from, to, value));}
inline Dbl LerpRS(C VecD4 &from, C VecD4 &to, C VecD4 &value) {return Sat(LerpR(from, to, value));}

Flt LerpAngle(Flt from, Flt to, Flt step); // angle based interpolation, 'step'=0..1

void Lerp4Weights(Vec4 &weights, Flt step); // get weights used for 'Lerp4' function, 'step'=0..1

Flt  Lerp4(  Flt   v0,   Flt   v1,   Flt   v2,   Flt   v3, Flt step); // 4 values based interpolation (hermite spline), smoothly interpolate between v1..v2, 'step'=0..1
Vec2 Lerp4(C Vec2 &v0, C Vec2 &v1, C Vec2 &v2, C Vec2 &v3, Flt step); // 4 values based interpolation (hermite spline), smoothly interpolate between v1..v2, 'step'=0..1
Vec  Lerp4(C Vec  &v0, C Vec  &v1, C Vec  &v2, C Vec  &v3, Flt step); // 4 values based interpolation (hermite spline), smoothly interpolate between v1..v2, 'step'=0..1
Vec4 Lerp4(C Vec4 &v0, C Vec4 &v1, C Vec4 &v2, C Vec4 &v3, Flt step); // 4 values based interpolation (hermite spline), smoothly interpolate between v1..v2, 'step'=0..1

Flt  LerpTan(  Flt   from,   Flt   to, Flt step,   Flt   tan0,   Flt   tan1); // tangent based interpolation (hermite spline), 'step'=0..1
Vec2 LerpTan(C Vec2 &from, C Vec2 &to, Flt step, C Vec2 &tan0, C Vec2 &tan1); // tangent based interpolation (hermite spline), 'step'=0..1
Vec  LerpTan(C Vec  &from, C Vec  &to, Flt step, C Vec  &tan0, C Vec  &tan1); // tangent based interpolation (hermite spline), 'step'=0..1
Vec4 LerpTan(C Vec4 &from, C Vec4 &to, Flt step, C Vec4 &tan0, C Vec4 &tan1); // tangent based interpolation (hermite spline), 'step'=0..1

inline Flt LerpSmoothSqr   (Flt from, Flt to, Flt step           ) {return Lerp(from, to, SmoothSqr   (step       ));}
inline Flt LerpSmoothCube  (Flt from, Flt to, Flt step           ) {return Lerp(from, to, SmoothCube  (step       ));}
inline Flt LerpSmoothCube2 (Flt from, Flt to, Flt step           ) {return Lerp(from, to, SmoothCube2 (step       ));}
inline Flt LerpSmoothSextic(Flt from, Flt to, Flt step           ) {return Lerp(from, to, SmoothSextic(step       ));}
inline Flt LerpSmoothSin   (Flt from, Flt to, Flt step           ) {return Lerp(from, to, SmoothSin   (step       ));}
inline Flt LerpSmoothPow   (Flt from, Flt to, Flt step, Flt pow  ) {return Lerp(from, to, SmoothPow   (step, pow  ));}
inline Flt LerpSmoothPinch (Flt from, Flt to, Flt step, Flt pinch) {return Lerp(from, to, SmoothPinch (step, pinch));}
/******************************************************************************/
// ADJUST VALUE
/******************************************************************************/
void AdjustValDir    (Flt  &value,   Int      dir,           Flt dv                       ); // adjust value by direction, move 'value' according to 'dir' directon * 'dv'     and clamps it to -1..1, if 'dir'==0 then moves 'value' towards 0 by 'dv'
void AdjustValDir    (Flt  &value,   Int      dir,           Flt change  , Flt reset      ); // adjust value by direction, move 'value' according to 'dir' directon * 'change' and clamps it to -1..1, if 'dir'==0 then moves 'value' towards 0 by 'reset'
void AdjustValBool   (Flt  &value,   Bool      on,           Flt dv                       ); // adjust value by Bool     , increases/decreases 'value' and clamps it to 0..1, "value=Sat(on ? value+dv : value-dv)"
void AdjustValBool   (Flt  &value,   Bool      on,           Flt inc     , Flt dec        ); // adjust value by Bool     , increases/decreases 'value' and clamps it to 0..1, "value=Sat(on ? value+dv : value-dv)"
void AdjustValBoolSet(Flt  &value,   Bool      on, Bool set, Flt dv                       ); // adjust value by Bool or immediate set, "if(set)value=on;else AdjustValBool(value,on,dv     );"
void AdjustValBoolSet(Flt  &value,   Bool      on, Bool set, Flt inc     , Flt dec        ); // adjust value by Bool or immediate set, "if(set)value=on;else AdjustValBool(value,on,inc,dec);"
void AdjustValTime   (Flt  &value,   Flt   target,           Flt exponent, Flt dt=Time.d()); // adjust value to target by smooth time interpolation, 'exponent'=0..1
void AdjustValTime   (Vec2 &value, C Vec2 &target,           Flt exponent, Flt dt=Time.d()); // adjust value to target by smooth time interpolation, 'exponent'=0..1
void AdjustValTime   (Vec  &value, C Vec  &target,           Flt exponent, Flt dt=Time.d()); // adjust value to target by smooth time interpolation, 'exponent'=0..1
void AdjustValTarget (Flt  &value,   Flt   target,           Flt dv                       ); // adjust value to target, move     'value' towards 'target' by 'dv'
void AdjustValTarget (Vec2 &value, C Vec2 &target,           Flt dv                       ); // adjust value to target, move     'value' towards 'target' by 'dv'
void AdjustValTarget (Vec  &value, C Vec  &target,           Flt dv                       ); // adjust value to target, move     'value' towards 'target' by 'dv'
void AdjustValTarget (Flt  &value,   Flt   target,           Flt inc     , Flt dec        ); // adjust value to target, increase 'value' towards 'target' by 'inc' or decrease 'value' towards 'target' by 'dec'
/******************************************************************************/
// EQUATIONS
/******************************************************************************/
// solve equations of given formula
// return number of solutions (-1=infinite, 0=none, 1=one, 2=two, 3=three), set 'x' as solutions

// polynominals
inline Int Polynominal0(Flt a) {return a ? 0 : -1;}                             // a                       = 0
inline Int Polynominal0(Dbl a) {return a ? 0 : -1;}                             // a                       = 0
       Int Polynominal1(Flt a, Flt b,               Flt &x                   ); // a*x   + b               = 0
       Int Polynominal1(Dbl a, Dbl b,               Dbl &x                   ); // a*x   + b               = 0
       Int Polynominal2(Flt a, Flt b, Flt c,        Flt &x0, Flt &x1         ); // a*x^2 + b*x   + c       = 0
       Int Polynominal2(Dbl a, Dbl b, Dbl c,        Dbl &x0, Dbl &x1         ); // a*x^2 + b*x   + c       = 0
       Int Polynominal3(Flt a, Flt b, Flt c, Flt d, Flt &x0, Flt &x1, Flt &x2); // a*x^3 + b*x^2 + c*x + d = 0
       Int Polynominal3(Dbl a, Dbl b, Dbl c, Dbl d, Dbl &x0, Dbl &x1, Dbl &x2); // a*x^3 + b*x^2 + c*x + d = 0

// simultaneous equations
Int Solve(Flt a1, Flt a2, Flt b1, Flt b2, Flt c1, Flt c2, Flt &x, Flt &y);
Int Solve(Dbl a1, Dbl a2, Dbl b1, Dbl b2, Dbl c1, Dbl c2, Dbl &x, Dbl &y);
// x*a1 + y*b1 = c1
// x*a2 + y*b2 = c2
/******************************************************************************/
// CONVERT UNITS
/******************************************************************************/
inline Flt  DegToRad(  Int   deg) {return deg*(PID/180);} // convert Degrees to Radians
inline Flt  DegToRad(  Flt   deg) {return deg*(PID/180);} // convert Degrees to Radians
inline Dbl  DegToRad(  Dbl   deg) {return deg*(PID/180);} // convert Degrees to Radians
inline Vec2 DegToRad(C Vec2 &deg) {return deg*(PI /180);} // convert Degrees to Radians
inline Vec  DegToRad(C Vec  &deg) {return deg*(PI /180);} // convert Degrees to Radians
inline Vec4 DegToRad(C Vec4 &deg) {return deg*(PI /180);} // convert Degrees to Radians

inline Flt  RadToDeg(  Flt   rad) {return rad*(180/PID);} // convert Radians to Degrees
inline Dbl  RadToDeg(  Dbl   rad) {return rad*(180/PID);} // convert Radians to Degrees
inline Vec2 RadToDeg(C Vec2 &rad) {return rad*(180/PI );} // convert Radians to Degrees
inline Vec  RadToDeg(C Vec  &rad) {return rad*(180/PI );} // convert Radians to Degrees
inline Vec4 RadToDeg(C Vec4 &rad) {return rad*(180/PI );} // convert Radians to Degrees

inline Flt MpsToKmph   (Flt x) {return x*((60*60)/1000.0f);} // convert "Meter     per Second" To "Kilometer per Hour  "
inline Flt KmphToMps   (Flt x) {return x*(1000.0f/(60*60));} // convert "Kilometer per Hour  " To "Meter     per Second"
inline Flt RadpsToRotpm(Flt x) {return x*(60/PID2        );} // convert "Radian    per Second" To "Rotation  per Minute"
inline Flt RotpmToRadps(Flt x) {return x*(PID2/60        );} // convert "Rotation  per Minute" To "Radian    per Second"
/******************************************************************************/

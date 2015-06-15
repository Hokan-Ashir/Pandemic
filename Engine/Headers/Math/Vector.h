/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Vec2' to handle 2D vectors, Flt type
   Use 'Vec'  to handle 3D vectors, Flt type
   Use 'Vec4' to handle 4D vectors, Flt type

   Use 'VecD2' to handle 2D vectors, Dbl type
   Use 'VecD'  to handle 3D vectors, Dbl type
   Use 'VecD4' to handle 4D vectors, Dbl type

   Use 'VecI2' to handle 2D vectors, Int type
   Use 'VecI'  to handle 3D vectors, Int type
   Use 'VecI4' to handle 4D vectors, Int type

   Use 'VecB4' to handle 4D vectors, Byte type

/******************************************************************************/
#define SIGN_BIT 0x80000000 // Float Sign Bit

#define PI_6 0.52359878f // PI/6 ( 30 deg)
#define PI_4 0.78539816f // PI/4 ( 45 deg)
#define PI_3 1.04719755f // PI/3 ( 60 deg)
#define PI_2 1.57079633f // PI/2 ( 90 deg)
#define PI   3.14159265f // PI   (180 deg)
#define PI2  6.28318531f // PI*2 (360 deg)

#define PID_6 0.5235987755982988 // PI/6 ( 30 deg) Dbl
#define PID_4 0.7853981633974483 // PI/4 ( 45 deg) Dbl
#define PID_3 1.0471975511965977 // PI/3 ( 60 deg) Dbl
#define PID_2 1.5707963267948966 // PI/2 ( 90 deg) Dbl
#define PID   3.1415926535897932 // PI   (180 deg) Dbl
#define PID2  6.2831853071795864 // PI*2 (360 deg) Dbl

#define SQRT2   1.4142135623730950 // Sqrt(2)
#define SQRT3   1.7320508075688773 // Sqrt(3)
#define SQRT2_2 0.7071067811865475 // Sqrt(2)/2
#define SQRT3_3 0.5773502691896257 // Sqrt(3)/3

#define EPSA 0.0010000f // Angular       Epsilon
#define EPSL 0.0002000f // Low Precision Epsilon
#define EPS  0.0000350f // Flt           Epsilon
#define EPSD 0.0000005f // Dbl           Epsilon

#ifndef  INT_MAX
#define  INT_MIN (-0x7FFFFFFF-1)         // Minimum possible value of 32-bit   signed int ( Int)
#define  INT_MAX   0x7FFFFFFF            // Maximum possible value of 32-bit   signed int ( Int)
#define UINT_MAX   0xFFFFFFFFu           // Maximum possible value of 32-bit unsigned int (UInt)
#endif
#define HALF_MAX 65504                   // Maximum possible value of 16-bit real         (Half)
#ifndef  FLT_MAX
#define  FLT_MAX 3.402823466e+38F        // Maximum possible value of 32-bit real         ( Flt)
#define  DBL_MAX 1.7976931348623158e+308 // Maximum possible value of 64-bit real         ( Dbl)
#endif
/******************************************************************************/
enum AXIS_TYPE
{
   AXIS_X,
   AXIS_Y,
   AXIS_Z,
};
enum DIR_ENUM // Direction Enums
{
   DIRE_RIGHT  , // right
   DIRE_LEFT   , // left
   DIRE_UP     , // up
   DIRE_DOWN   , // down
   DIRE_FORWARD, // forward
   DIRE_BACK   , // backwards
   DIRE_NUM    , // number of directions
};
enum DIR_FLAG // Direction Flags
{
   DIRF_RIGHT  =1<<DIRE_RIGHT  , // right
   DIRF_LEFT   =1<<DIRE_LEFT   , // left
   DIRF_UP     =1<<DIRE_UP     , // up
   DIRF_DOWN   =1<<DIRE_DOWN   , // down
   DIRF_FORWARD=1<<DIRE_FORWARD, // forward
   DIRF_BACK   =1<<DIRE_BACK   , // backwards

   DIRF_X=DIRF_RIGHT  |DIRF_LEFT,
   DIRF_Y=DIRF_UP     |DIRF_DOWN,
   DIRF_Z=DIRF_FORWARD|DIRF_BACK,

   DIRF_XYZ=DIRF_X|DIRF_Y|DIRF_Z,
   DIRF_ALL=DIRF_XYZ,
};
/******************************************************************************/
// MINIMUM MAXIMUM AVERAGE
/******************************************************************************/
// get minimum/maximum value
inline Int  Min(Int  x, Int   y) {return (x<y) ? x : y;}
inline Int  Min(UInt x, Int   y) {return (x<y) ? x : y;}
inline Int  Min(Int  x, UInt  y) {return (x<y) ? x : y;}
inline UInt Min(UInt x, UInt  y) {return (x<y) ? x : y;}
inline Int  Min(Int  x, ULong y) {return (x<y) ? x : y;}
inline Long Min(Int  x, Long  y) {return (x<y) ? x : y;}
inline Flt  Min(Flt  x, Flt   y) {return (x<y) ? x : y;}
inline Flt  Min(Int  x, Flt   y) {return (x<y) ? x : y;}
inline Flt  Min(Flt  x, Int   y) {return (x<y) ? x : y;}
inline Dbl  Min(Dbl  x, Dbl   y) {return (x<y) ? x : y;}

inline Int  Max(Int  x, Int  y) {return (x>y) ? x : y;}
inline UInt Max(UInt x, Int  y) {return (x>y) ? x : y;}
inline UInt Max(Int  x, UInt y) {return (x>y) ? x : y;}
inline UInt Max(UInt x, UInt y) {return (x>y) ? x : y;}
inline Long Max(Int  x, Long y) {return (x>y) ? x : y;}
inline Flt  Max(Flt  x, Flt  y) {return (x>y) ? x : y;}
inline Flt  Max(Int  x, Flt  y) {return (x>y) ? x : y;}
inline Flt  Max(Flt  x, Int  y) {return (x>y) ? x : y;}
inline Dbl  Max(Dbl  x, Dbl  y) {return (x>y) ? x : y;}

inline Int Min(Int x, Int y, Int z       ) {return Min(x, Min(y, z));}
inline Flt Min(Flt x, Flt y, Flt z       ) {return Min(x, Min(y, z));}
inline Dbl Min(Dbl x, Dbl y, Dbl z       ) {return Min(x, Min(y, z));}
inline Int Max(Int x, Int y, Int z       ) {return Max(x, Max(y, z));}
inline Flt Max(Flt x, Flt y, Flt z       ) {return Max(x, Max(y, z));}
inline Dbl Max(Dbl x, Dbl y, Dbl z       ) {return Max(x, Max(y, z));}
inline Int Min(Int x, Int y, Int z, Int w) {return Min(x, Min(y, z, w));}
inline Flt Min(Flt x, Flt y, Flt z, Flt w) {return Min(x, Min(y, z, w));}
inline Dbl Min(Dbl x, Dbl y, Dbl z, Dbl w) {return Min(x, Min(y, z, w));}
inline Int Max(Int x, Int y, Int z, Int w) {return Max(x, Max(y, z, w));}
inline Flt Max(Flt x, Flt y, Flt z, Flt w) {return Max(x, Max(y, z, w));}
inline Dbl Max(Dbl x, Dbl y, Dbl z, Dbl w) {return Max(x, Max(y, z, w));}

// minimize/maximize value
T2(TA, TB) inline TA& MIN(TA &x, TB y) {if(y<x)x=y; return x;} // equal to: x=Min(x, y)
T2(TA, TB) inline TA& MAX(TA &x, TB y) {if(y>x)x=y; return x;} // equal to: x=Max(x, y)

// get index of minimum/maximum value (if the min/max value is shared between multiple values, then index of the first value is returned)
Int MinI(Int x, Int y);
Int MinI(Flt x, Flt y);
Int MinI(Dbl x, Dbl y);
Int MaxI(Int x, Int y);
Int MaxI(Flt x, Flt y);
Int MaxI(Dbl x, Dbl y);
Int MinI(Int x, Int y, Int z);
Int MinI(Flt x, Flt y, Flt z);
Int MinI(Dbl x, Dbl y, Dbl z);
Int MaxI(Int x, Int y, Int z);
Int MaxI(Flt x, Flt y, Flt z);
Int MaxI(Dbl x, Dbl y, Dbl z);
Int MinI(Int x, Int y, Int z, Int w);
Int MinI(Flt x, Flt y, Flt z, Flt w);
Int MinI(Dbl x, Dbl y, Dbl z, Dbl w);
Int MaxI(Int x, Int y, Int z, Int w);
Int MaxI(Flt x, Flt y, Flt z, Flt w);
Int MaxI(Dbl x, Dbl y, Dbl z, Dbl w);

// get average value
inline Int AvgI(Int x, Int y              ) {return DivRound(x+y    , 2)      ;}
inline Flt AvgF(Int x, Int y              ) {return         (x+y       )*0.5f ;}
inline Flt Avg (Flt x, Flt y              ) {return         (x+y       )*0.5f ;}
inline Dbl Avg (Dbl x, Dbl y              ) {return         (x+y       )*0.5  ;}
inline Int AvgI(Int x, Int y, Int z       ) {return DivRound(x+y+z  , 3)      ;}
inline Flt AvgF(Int x, Int y, Int z       ) {return         (x+y+z     )/3.0f ;}
inline Flt Avg (Flt x, Flt y, Flt z       ) {return         (x+y+z     )/3.0f ;}
inline Dbl Avg (Dbl x, Dbl y, Dbl z       ) {return         (x+y+z     )/3.0  ;}
inline Int AvgI(Int x, Int y, Int z, Int w) {return DivRound(x+y+z+w, 4)      ;}
inline Flt AvgF(Int x, Int y, Int z, Int w) {return         (x+y+z+w   )*0.25f;}
inline Flt Avg (Flt x, Flt y, Flt z, Flt w) {return         (x+y+z+w   )*0.25f;}
inline Dbl Avg (Dbl x, Dbl y, Dbl z, Dbl w) {return         (x+y+z+w   )*0.25 ;}
/******************************************************************************/
// TESTING
/******************************************************************************/
// test if any of the parameters isn't zero
inline Bool Any(C Flt &x                              ); // faster version of "x!=0"
inline Bool Any(C Flt &x, C Flt &y                    ); // faster version of "x!=0 || y!=0"
inline Bool Any(C Flt &x, C Flt &y, C Flt &z          ); // faster version of "x!=0 || y!=0 || z!=0"
inline Bool Any(C Flt &x, C Flt &y, C Flt &z, C Flt &w); // faster version of "x!=0 || y!=0 || z!=0 || w!=0"
/******************************************************************************/
// 16-BIT FLOAT
/******************************************************************************/
typedef struct Half
{
   U16 data;

   Half() {}
   Half(Flt f); // create from float
   operator Flt()C; // convert to float

   Half& operator+=(Flt f) {T=Flt(T)+f; return T;}
   Half& operator-=(Flt f) {T=Flt(T)-f; return T;}
   Half& operator*=(Flt f) {T=Flt(T)*f; return T;}
   Half& operator/=(Flt f) {T=Flt(T)/f; return T;}

   Bool operator< (Flt  f)C {return Flt(T)< f;}
   Bool operator<=(Flt  f)C {return Flt(T)<=f;}
   Bool operator> (Flt  f)C {return Flt(T)> f;}
   Bool operator>=(Flt  f)C {return Flt(T)>=f;}
   Bool operator==(Flt  f)C {return Flt(T)==f;}
   Bool operator==(Half h)C {return data  ==h.data;}
}F16;
inline Int Compare(C Half &a, C Half &b) {if(a<b)return -1; if(a>b)return +1; return 0;} // compare 'a' 'b' values and return -1, 0, +1
/******************************************************************************/
// VECTORS
/******************************************************************************/
struct Vec2 // Vector 2D
{
   union
   {
      struct{Flt x, y;};
      struct{Flt c[2];}; // component
   };

   Vec2& zero(            ) {x=y=0;        return T;}
   Vec2& set (Flt r       ) {x=y=r;        return T;}
   Vec2& set (Flt x, Flt y) {T.x=x; T.y=y; return T;}

          Vec2& operator+=(  Flt      r) {x+=  r; y+=  r; return T;}
          Vec2& operator-=(  Flt      r) {x-=  r; y-=  r; return T;}
          Vec2& operator*=(  Flt      r) {x*=  r; y*=  r; return T;}
          Vec2& operator/=(  Flt      r) {x/=  r; y/=  r; return T;}
          Vec2& operator+=(C Vec2    &v) {x+=v.x; y+=v.y; return T;}
          Vec2& operator-=(C Vec2    &v) {x-=v.x; y-=v.y; return T;}
          Vec2& operator*=(C Vec2    &v) {x*=v.x; y*=v.y; return T;}
          Vec2& operator/=(C Vec2    &v) {x/=v.x; y/=v.y; return T;}
          Vec2& operator*=(C Matrix3 &m) {return mul(m);}
          Vec2& operator*=(C Matrix  &m) {return mul(m);}
          Vec2& operator/=(C Matrix3 &m) {return div(m);}
          Vec2& operator/=(C Matrix  &m) {return div(m);}
          Vec2& operator&=(C Rect    &r) ; // intersect
          Bool  operator==(C Vec2    &v)C;
          Bool  operator!=(C Vec2    &v)C;

   friend Vec2  operator+ (C Vec2    &v,   Flt      r) {return Vec2(v.x+r, v.y+r);}
   friend Vec2  operator- (C Vec2    &v,   Flt      r) {return Vec2(v.x-r, v.y-r);}
   friend Vec2  operator* (C Vec2    &v,   Flt      r) {return Vec2(v.x*r, v.y*r);}
   friend Vec2  operator/ (C Vec2    &v,   Flt      r) {return Vec2(v.x/r, v.y/r);}
   friend Vec2  operator+ (  Flt      r, C Vec2    &v) {return Vec2(r+v.x, r+v.y);}
   friend Vec2  operator- (  Flt      r, C Vec2    &v) {return Vec2(r-v.x, r-v.y);}
   friend Vec2  operator* (  Flt      r, C Vec2    &v) {return Vec2(r*v.x, r*v.y);}
   friend Vec2  operator/ (  Flt      r, C Vec2    &v) {return Vec2(r/v.x, r/v.y);}
   friend Vec2  operator+ (C Vec2    &a, C Vec2    &b) {return Vec2(a.x+b.x, a.y+b.y);}
   friend Vec2  operator- (C Vec2    &a, C Vec2    &b) {return Vec2(a.x-b.x, a.y-b.y);}
   friend Vec2  operator* (C Vec2    &a, C Vec2    &b) {return Vec2(a.x*b.x, a.y*b.y);}
   friend Vec2  operator/ (C Vec2    &a, C Vec2    &b) {return Vec2(a.x/b.x, a.y/b.y);}
   friend Vec2  operator* (C Vec2    &v, C Matrix3 &m) {return Vec2(v)*=m;}
   friend Vec2  operator* (C Vec2    &v, C Matrix  &m) {return Vec2(v)*=m;}
   friend Vec2  operator/ (C Vec2    &v, C Matrix3 &m) {return Vec2(v)/=m;}
   friend Vec2  operator/ (C Vec2    &v, C Matrix  &m) {return Vec2(v)/=m;}
   friend Vec2  operator& (C Vec2    &v, C Rect    &r) {return Vec2(v)&=r;} // intersection
   friend Vec2  operator- (C Vec2    &v              ) {return Vec2(-v.x, -v.y);}
   friend Vec2  operator! (C Vec2    &v              ) {       Vec2 ret=v; ret.normalize(); return ret;} // return normalized vector

   Vec2 xy ()C {return Vec2(x, y);} // return as Vec2(x, y)
   Vec2 yx ()C {return Vec2(y, x);} // return as Vec2(y, x)
   Vec  xy0()C;                     // return as Vec (x, y, 0)
   Vec  x0y()C;                     // return as Vec (x, 0, y)
   Vec _0xy()C;                     // return as Vec (0, x, y)
   Vec _0yx()C;                     // return as Vec (0, y, x)

   Bool      any      (                                   )C {return Any (x, y);}   // if any component  is  non-zero
   Bool      all      (                                   )C {return x && y    ;}   // if all components are non-zero
   Int       minI     (                                   )C {return MinI(x, y);}   // components minimum index
   Int       maxI     (                                   )C {return MaxI(x, y);}   // components maximum index
   Flt       min      (                                   )C {return Min (x, y);}   // components minimum
   Flt       max      (                                   )C {return Max (x, y);}   // components maximum
   Flt       avg      (                                   )C {return Avg (x, y);}   // components average
   Flt       sum      (                                   )C {return      x+ y ;}   // components sum
   Flt       mul      (                                   )C {return      x* y ;}   // components multiplication
   Flt       length   (                                   )C;                       // get               length
   Flt       length2  (                                   )C {return  x*x + y*y;}   // get       squared length
   Vec2&  satLength   (                                   );                        // saturate  length (clip it to 0..1)
   Flt    setLength   (  Flt length                       );                        // set       length and return previous length
   Vec2& clipLength   (  Flt max_length                   );                        // clip      length to 0..max_length range
   Flt       normalize(                                   );                        // normalize length and return previous length
   Vec2&     mul      (C Matrix3 &m                       );                        // transform by matrix
   Vec2&     mul      (C Matrix  &m                       );                        // transform by matrix
   Vec2&     div      (C Matrix3 &m, Bool normalized=false);                        // transform by matrix inverse, if you know that the matrix is normalized then set 'normalized=true' for more performance
   Vec2&     div      (C Matrix  &m, Bool normalized=false);                        // transform by matrix inverse, if you know that the matrix is normalized then set 'normalized=true' for more performance
   Vec2&     rotate   (  Flt angle                        );                        // rotate by angle
   Vec2&     rotate   (  Flt sin, Flt cos                 );                        // rotate by sin and cos of angle
   Vec2&     chs      (                                   );                        // change sign of all components
   Vec2&     abs      (                                   );                        // absolute       all components
   Vec2&     sat      (                                   );                        // saturate       all components
   Vec2&     swap     (                                   ) {Swap(x, y); return T;} // swap               components

   Str asText(Int precision=INT_MAX)C; // return as text

   // draw
   void draw(C Color &color, Flt r=0.007f)C; // this can be optionally called outside of Render function

   Vec2() {}
   Vec2(Flt r       ) {set(r   );}
   Vec2(Flt x, Flt y) {set(x, y);}
   Vec2(C VecD2 &v);
   Vec2(C VecI2 &v);
};
/******************************************************************************/
struct VecD2 // Vector 2D (double precision)
{
   union
   {
      struct{Dbl x, y;};
      struct{Dbl c[2];}; // component
   };

   VecD2& zero(            ) {x=y=0;        return T;}
   VecD2& set (Dbl r       ) {x=y=r;        return T;}
   VecD2& set (Dbl x, Dbl y) {T.x=x; T.y=y; return T;}

          VecD2& operator+=(  Dbl       r) {x+=  r; y+=  r; return T;}
          VecD2& operator-=(  Dbl       r) {x-=  r; y-=  r; return T;}
          VecD2& operator*=(  Dbl       r) {x*=  r; y*=  r; return T;}
          VecD2& operator/=(  Dbl       r) {x/=  r; y/=  r; return T;}
          VecD2& operator+=(C VecD2    &v) {x+=v.x; y+=v.y; return T;}
          VecD2& operator-=(C VecD2    &v) {x-=v.x; y-=v.y; return T;}
          VecD2& operator*=(C VecD2    &v) {x*=v.x; y*=v.y; return T;}
          VecD2& operator/=(C VecD2    &v) {x/=v.x; y/=v.y; return T;}
          VecD2& operator*=(C MatrixD3 &m) {return mul(m);}
          VecD2& operator*=(C MatrixD  &m) {return mul(m);}
          VecD2& operator/=(C MatrixD3 &m) {return div(m);}
          VecD2& operator/=(C MatrixD  &m) {return div(m);}
          Bool   operator==(C VecD2    &v)C;
          Bool   operator!=(C VecD2    &v)C;

   friend VecD2  operator+ (C VecD2    &v,   Dbl       r) {return VecD2(v.x+r, v.y+r);}
   friend VecD2  operator- (C VecD2    &v,   Dbl       r) {return VecD2(v.x-r, v.y-r);}
   friend VecD2  operator* (C VecD2    &v,   Dbl       r) {return VecD2(v.x*r, v.y*r);}
   friend VecD2  operator/ (C VecD2    &v,   Dbl       r) {return VecD2(v.x/r, v.y/r);}
   friend VecD2  operator+ (  Dbl       r, C VecD2    &v) {return VecD2(r+v.x, r+v.y);}
   friend VecD2  operator- (  Dbl       r, C VecD2    &v) {return VecD2(r-v.x, r-v.y);}
   friend VecD2  operator* (  Dbl       r, C VecD2    &v) {return VecD2(r*v.x, r*v.y);}
   friend VecD2  operator/ (  Dbl       r, C VecD2    &v) {return VecD2(r/v.x, r/v.y);}
   friend VecD2  operator+ (C VecD2    &a, C VecD2    &b) {return VecD2(a.x+b.x, a.y+b.y);}
   friend VecD2  operator- (C VecD2    &a, C VecD2    &b) {return VecD2(a.x-b.x, a.y-b.y);}
   friend VecD2  operator* (C VecD2    &a, C VecD2    &b) {return VecD2(a.x*b.x, a.y*b.y);}
   friend VecD2  operator/ (C VecD2    &a, C VecD2    &b) {return VecD2(a.x/b.x, a.y/b.y);}
   friend VecD2  operator* (C VecD2    &v, C MatrixD3 &m) {return VecD2(v)*=m;}
   friend VecD2  operator* (C VecD2    &v, C MatrixD  &m) {return VecD2(v)*=m;}
   friend VecD2  operator/ (C VecD2    &v, C MatrixD3 &m) {return VecD2(v)/=m;}
   friend VecD2  operator/ (C VecD2    &v, C MatrixD  &m) {return VecD2(v)/=m;}
   friend VecD2  operator- (C VecD2    &v               ) {return VecD2(-v.x, -v.y);}
   friend VecD2  operator! (C VecD2    &v               ) {       VecD2 ret=v; ret.normalize(); return ret;} // return normalized vector

   VecD2 xy ()C {return VecD2(x, y);} // return as VecD2(x, y)
   VecD2 yx ()C {return VecD2(y, x);} // return as VecD2(y, x)
   VecD  xy0()C;                      // return as VecD (x, y, 0)
   VecD  x0y()C;                      // return as VecD (x, 0, y)
   VecD _0xy()C;                      // return as VecD (0, x, y)
   VecD _0yx()C;                      // return as VecD (0, y, x)

   Bool       any      (                                    )C {return x || y    ;}   // if any component  is  non-zero
   Bool       all      (                                    )C {return x && y    ;}   // if all components are non-zero
   Int        minI     (                                    )C {return MinI(x, y);}   // components minimum index
   Int        maxI     (                                    )C {return MaxI(x, y);}   // components maximum index
   Dbl        min      (                                    )C {return Min (x, y);}   // components minimum
   Dbl        max      (                                    )C {return Max (x, y);}   // components maximum
   Dbl        avg      (                                    )C {return Avg (x, y);}   // components average
   Dbl        sum      (                                    )C {return      x+ y ;}   // components sum
   Dbl        mul      (                                    )C {return      x* y ;}   // components multiplication
   Dbl        length   (                                    )C;                       // get               length
   Dbl        length2  (                                    )C {return  x*x + y*y;}   // get       squared length
   VecD2&  satLength   (                                    );                        // saturate  length (clip it to 0..1)
   Dbl     setLength   (  Dbl length                        );                        // set       length and return previous length
   VecD2& clipLength   (  Dbl max_length                    );                        // clip      length to 0..max_length range
   Dbl        normalize(                                    );                        // normalize length and return previous length
   VecD2&     mul      (C MatrixD3 &m                       );                        // transform by matrix
   VecD2&     mul      (C MatrixD  &m                       );                        // transform by matrix
   VecD2&     div      (C MatrixD3 &m, Bool normalized=false);                        // transform by matrix inverse, if you know that the matrix is normalized then set 'normalized=true' for more performance
   VecD2&     div      (C MatrixD  &m, Bool normalized=false);                        // transform by matrix inverse, if you know that the matrix is normalized then set 'normalized=true' for more performance
   VecD2&     chs      (                                    );                        // change sign of all components
   VecD2&     abs      (                                    );                        // absolute       all components
   VecD2&     sat      (                                    );                        // saturate       all components
   VecD2&     swap     (                                    ) {Swap(x, y); return T;} // swap               components

   Str asText(Int precision=INT_MAX)C; // return as text

   // draw
   void draw(C Color &color, Flt r=0.007f)C; // this can be optionally called outside of Render function

   VecD2() {}
   VecD2(Dbl r       ) {set(r   );}
   VecD2(Dbl x, Dbl y) {set(x, y);}
   VecD2(C Vec2  &v);
   VecD2(C VecI2 &v);
};
/******************************************************************************/
struct Vec // Vector 3D
{
   union
   {
      struct{Flt x, y, z;};
      struct{Flt c[3]   ;}; // component
   };

   Vec2& v2()  {return (Vec2&)T;} // get reference to self as       Vec2
 C Vec2& v2()C {return (Vec2&)T;} // get reference to self as const Vec2

   Vec& zero(                   ) {x=y=z=0;             return T;}
   Vec& set (Flt r              ) {x=y=z=r;             return T;}
   Vec& set (Flt x, Flt y, Flt z) {T.x=x; T.y=y; T.z=z; return T;}
   Vec& set (C Vec2 &v2  , Flt z) {T.v2()=v2;    T.z=z; return T;}

          Vec& operator+=(  Flt      r) {x+=  r; y+=  r; z+=  r; return T;}
          Vec& operator-=(  Flt      r) {x-=  r; y-=  r; z-=  r; return T;}
          Vec& operator*=(  Flt      r) {x*=  r; y*=  r; z*=  r; return T;}
          Vec& operator/=(  Flt      r) {x/=  r; y/=  r; z/=  r; return T;}
          Vec& operator+=(C Vec     &v) {x+=v.x; y+=v.y; z+=v.z; return T;}
          Vec& operator-=(C Vec     &v) {x-=v.x; y-=v.y; z-=v.z; return T;}
          Vec& operator*=(C Vec     &v) {x*=v.x; y*=v.y; z*=v.z; return T;}
          Vec& operator/=(C Vec     &v) {x/=v.x; y/=v.y; z/=v.z; return T;}
          Vec& operator*=(C Matrix3 &m) {return mul(m);}
          Vec& operator/=(C Matrix3 &m) {return div(m);}
          Vec& operator*=(C Matrix  &m) {return mul(m);}
          Vec& operator/=(C Matrix  &m) {return div(m);}
          Vec& operator&=(C Box     &b) ; // intersect
          Vec& operator&=(C OBox    &b) ; // intersect
          Bool operator==(C Vec     &v)C;
          Bool operator!=(C Vec     &v)C;

   friend Vec  operator+ (C Vec     &v,   Flt      r) {return Vec(v.x+r, v.y+r, v.z+r);}
   friend Vec  operator- (C Vec     &v,   Flt      r) {return Vec(v.x-r, v.y-r, v.z-r);}
   friend Vec  operator* (C Vec     &v,   Flt      r) {return Vec(v.x*r, v.y*r, v.z*r);}
   friend Vec  operator/ (C Vec     &v,   Flt      r) {return Vec(v.x/r, v.y/r, v.z/r);}
   friend Vec  operator+ (  Flt      r, C Vec     &v) {return Vec(r+v.x, r+v.y, r+v.z);}
   friend Vec  operator- (  Flt      r, C Vec     &v) {return Vec(r-v.x, r-v.y, r-v.z);}
   friend Vec  operator* (  Flt      r, C Vec     &v) {return Vec(r*v.x, r*v.y, r*v.z);}
   friend Vec  operator/ (  Flt      r, C Vec     &v) {return Vec(r/v.x, r/v.y, r/v.z);}
   friend Vec  operator+ (C Vec     &a, C Vec     &b) {return Vec(a.x+b.x, a.y+b.y, a.z+b.z);}
   friend Vec  operator- (C Vec     &a, C Vec     &b) {return Vec(a.x-b.x, a.y-b.y, a.z-b.z);}
   friend Vec  operator* (C Vec     &a, C Vec     &b) {return Vec(a.x*b.x, a.y*b.y, a.z*b.z);}
   friend Vec  operator/ (C Vec     &a, C Vec     &b) {return Vec(a.x/b.x, a.y/b.y, a.z/b.z);}
   friend Vec  operator* (C Vec     &v, C Matrix3 &m) {return Vec(v)*=m;}
   friend Vec  operator* (C Vec     &v, C Matrix  &m) {return Vec(v)*=m;}
   friend Vec  operator/ (C Vec     &v, C Matrix3 &m) {return Vec(v)/=m;}
   friend Vec  operator/ (C Vec     &v, C Matrix  &m) {return Vec(v)/=m;}
   friend Vec  operator& (C Vec     &v, C Box     &b) {return Vec(v)&=b;} // intersection
   friend Vec  operator& (C Vec     &v, C OBox    &b) {return Vec(v)&=b;} // intersection
   friend Vec  operator- (C Vec     &v              ) {return Vec(-v.x, -v.y, -v.z);}
   friend Vec  operator! (C Vec     &v              ) {       Vec ret=v; ret.normalize(); return ret;} // return normalized vector

   Vec2 xy ()C {return Vec2(x, y   );} // return as Vec2(x, y)
   Vec2 xz ()C {return Vec2(x, z   );} // return as Vec2(x, z)
   Vec2 yx ()C {return Vec2(y, x   );} // return as Vec2(y, x)
   Vec2 yz ()C {return Vec2(y, z   );} // return as Vec2(y, z)
   Vec2 zx ()C {return Vec2(z, x   );} // return as Vec2(z, x)
   Vec2 zy ()C {return Vec2(z, y   );} // return as Vec2(z, y)
   Vec  xzy()C {return Vec (x, z, y);} // return as Vec (x, z, y)
   Vec  x0z()C {return Vec (x, 0, z);} // return as Vec (x, 0, z)

   Bool     any      (                                   )C {return Any (x, y, z);}   // if any component  is  non-zero
   Bool     all      (                                   )C {return  x && y && z ;}   // if all components are non-zero
   Int      minI     (                                   )C {return MinI(x, y, z);}   // components minimum index
   Int      maxI     (                                   )C {return MaxI(x, y, z);}   // components maximum index
   Flt      min      (                                   )C {return Min (x, y, z);}   // components minimum
   Flt      max      (                                   )C {return Max (x, y, z);}   // components maximum
   Flt      avg      (                                   )C {return Avg (x, y, z);}   // components average
   Flt      sum      (                                   )C {return      x+ y+ z ;}   // components sum
   Flt      length   (                                   )C;                          // get               length
   Flt      length2  (                                   )C {return x*x + y*y + z*z;} // get       squared length
   Vec&  satLength   (                                   );                           // saturate  length (clip it to 0..1)
   Flt   setLength   (  Flt length                       );                           // set       length and return previous length
   Vec& clipLength   (  Flt max_length                   );                           // clip      length to 0..max_length range
   Flt      normalize(                                   );                           // normalize length and return previous length
   Vec&     mul      (C Matrix3 &m                       );                           // transform by matrix
   Vec&     mul      (C Matrix  &m                       );                           // transform by matrix
   Vec&     div      (C Matrix3 &m, Bool normalized=false);                           // transform by matrix inverse, if you know that the matrix is normalized then set 'normalized=true' for more performance
   Vec&     div      (C Matrix  &m, Bool normalized=false);                           // transform by matrix inverse, if you know that the matrix is normalized then set 'normalized=true' for more performance
   Vec&     chs      (                                   );                           // change sign of all components
   Vec&     abs      (                                   );                           // absolute       all components
   Vec&     sat      (                                   );                           // saturate       all components
   Vec&     swapYZ   (                                   ) {Swap(y, z); return T;}    // swap       Y and Z components

   Str asText(Int precision=INT_MAX)C; // return as text

   // draw
   void draw (C Color &color, Flt r=0.007f)C; // draw                                                             , this can be optionally called outside of Render function, this relies on active object matrix which can be set using 'SetMatrix' function
   void drawP(C Color &color, Flt r=0.007f)C; // draw with perspective making size dependent on distance to camera, this can be optionally called outside of Render function, this relies on active object matrix which can be set using 'SetMatrix' function

   Vec() {}
   Vec(Flt r              ) {set(r      );}
   Vec(Flt x, Flt y, Flt z) {set(x, y, z);}
   Vec(C Vec2 &v2  , Flt z) {set(v2  , z);}
   Vec(C VecD &v);
   Vec(C VecI &v);
};extern const Vec
   VecDir[DIRE_NUM], // vector[DIR_ENUM] array
   VecZero         ; // Vec(0, 0, 0)
/******************************************************************************/
struct VecD // Vector 3D (double precision)
{
   union
   {
      struct{Dbl x, y, z;};
      struct{Dbl c[3]   ;}; // component
   };

   VecD2& v2()  {return (VecD2&)T;} // get reference to self as       VecD2
 C VecD2& v2()C {return (VecD2&)T;} // get reference to self as const VecD2

   VecD& zero(                   ) {x=y=z=0;             return T;}
   VecD& set (Dbl r              ) {x=y=z=r;             return T;}
   VecD& set (Dbl x, Dbl y, Dbl z) {T.x=x; T.y=y; T.z=z; return T;}
   VecD& set (C VecD2 &v2 , Dbl z) {T.v2()=v2;    T.z=z; return T;}

          VecD& operator+=(  Dbl       r) {x+=  r; y+=  r; z+=  r; return T;}
          VecD& operator-=(  Dbl       r) {x-=  r; y-=  r; z-=  r; return T;}
          VecD& operator*=(  Dbl       r) {x*=  r; y*=  r; z*=  r; return T;}
          VecD& operator/=(  Dbl       r) {x/=  r; y/=  r; z/=  r; return T;}
          VecD& operator+=(C VecD     &v) {x+=v.x; y+=v.y; z+=v.z; return T;}
          VecD& operator-=(C VecD     &v) {x-=v.x; y-=v.y; z-=v.z; return T;}
          VecD& operator*=(C VecD     &v) {x*=v.x; y*=v.y; z*=v.z; return T;}
          VecD& operator/=(C VecD     &v) {x/=v.x; y/=v.y; z/=v.z; return T;}
          VecD& operator*=(C MatrixD3 &m) {return mul(m);}
          VecD& operator/=(C MatrixD3 &m) {return div(m);}
          VecD& operator*=(C MatrixD  &m) {return mul(m);}
          VecD& operator/=(C MatrixD  &m) {return div(m);}
          Bool  operator==(C VecD     &v)C;
          Bool  operator!=(C VecD     &v)C;

   friend VecD  operator+ (C VecD     &v,   Dbl       r) {return VecD(v.x+r, v.y+r, v.z+r);}
   friend VecD  operator- (C VecD     &v,   Dbl       r) {return VecD(v.x-r, v.y-r, v.z-r);}
   friend VecD  operator* (C VecD     &v,   Dbl       r) {return VecD(v.x*r, v.y*r, v.z*r);}
   friend VecD  operator/ (C VecD     &v,   Dbl       r) {return VecD(v.x/r, v.y/r, v.z/r);}
   friend VecD  operator+ (  Dbl       r, C VecD     &v) {return VecD(r+v.x, r+v.y, r+v.z);}
   friend VecD  operator- (  Dbl       r, C VecD     &v) {return VecD(r-v.x, r-v.y, r-v.z);}
   friend VecD  operator* (  Dbl       r, C VecD     &v) {return VecD(r*v.x, r*v.y, r*v.z);}
   friend VecD  operator/ (  Dbl       r, C VecD     &v) {return VecD(r/v.x, r/v.y, r/v.z);}
   friend VecD  operator+ (C VecD     &a, C VecD     &b) {return VecD(a.x+b.x, a.y+b.y, a.z+b.z);}
   friend VecD  operator- (C VecD     &a, C VecD     &b) {return VecD(a.x-b.x, a.y-b.y, a.z-b.z);}
   friend VecD  operator* (C VecD     &a, C VecD     &b) {return VecD(a.x*b.x, a.y*b.y, a.z*b.z);}
   friend VecD  operator/ (C VecD     &a, C VecD     &b) {return VecD(a.x/b.x, a.y/b.y, a.z/b.z);}
   friend VecD  operator* (C VecD     &v, C MatrixD3 &m) {return VecD(v)*=m;}
   friend VecD  operator* (C VecD     &v, C MatrixD  &m) {return VecD(v)*=m;}
   friend VecD  operator/ (C VecD     &v, C MatrixD3 &m) {return VecD(v)/=m;}
   friend VecD  operator/ (C VecD     &v, C MatrixD  &m) {return VecD(v)/=m;}
   friend VecD  operator- (C VecD     &v               ) {return VecD(-v.x, -v.y, -v.z);}
   friend VecD  operator! (C VecD     &v               ) {       VecD ret=v; ret.normalize(); return ret;} // return normalized vector

   VecD2 xy()C {return VecD2(x, y);} // return as VecD2(x, y)
   VecD2 xz()C {return VecD2(x, z);} // return as VecD2(x, z)
   VecD2 yx()C {return VecD2(y, x);} // return as VecD2(y, x)
   VecD2 yz()C {return VecD2(y, z);} // return as VecD2(y, z)
   VecD2 zx()C {return VecD2(z, x);} // return as VecD2(z, x)
   VecD2 zy()C {return VecD2(z, y);} // return as VecD2(z, y)

   Bool      any      (                                    )C {return  x || y || z ;}   // if any component  is  non-zero
   Bool      all      (                                    )C {return  x && y && z ;}   // if all components are non-zero
   Int       minI     (                                    )C {return MinI(x, y, z);}   // components minimum index
   Int       maxI     (                                    )C {return MaxI(x, y, z);}   // components maximum index
   Dbl       min      (                                    )C {return Min (x, y, z);}   // components minimum
   Dbl       max      (                                    )C {return Max (x, y, z);}   // components maximum
   Dbl       avg      (                                    )C {return Avg (x, y, z);}   // components average
   Dbl       sum      (                                    )C {return      x+ y+ z ;}   // components sum
   Dbl       length   (                                    )C;                          // get               length
   Dbl       length2  (                                    )C {return x*x + y*y + z*z;} // get       squared length
   VecD&  satLength   (                                    );                           // saturate  length (clip it to 0..1)
   Dbl    setLength   (  Dbl length                        );                           // set       length and return previous length
   VecD& clipLength   (  Dbl max_length                    );                           // clip      length to 0..max_length range
   Dbl       normalize(                                    );                           // normalize length and return previous length
   VecD&     mul      (C MatrixD3 &m                       );                           // transform by matrix
   VecD&     mul      (C MatrixD  &m                       );                           // transform by matrix
   VecD&     div      (C MatrixD3 &m, Bool normalized=false);                           // transform by matrix inverse, if you know that the matrix is normalized then set 'normalized=true' for more performance
   VecD&     div      (C MatrixD  &m, Bool normalized=false);                           // transform by matrix inverse, if you know that the matrix is normalized then set 'normalized=true' for more performance
   VecD&     chs      (                                    );                           // change sign of all components
   VecD&     abs      (                                    );                           // absolute       all components
   VecD&     sat      (                                    );                           // saturate       all components
   VecD&     swapYZ   (                                    ) {Swap(y, z); return T;}    // swap       Y and Z components

   Str asText(Int precision=INT_MAX)C; // return as text

   // draw
   void draw (C Color &color, Flt r=0.007f)C; // draw                                                             , this can be optionally called outside of Render function, this relies on active object matrix which can be set using 'SetMatrix' function
   void drawP(C Color &color, Flt r=0.007f)C; // draw with perspective making size dependent on distance to camera, this can be optionally called outside of Render function, this relies on active object matrix which can be set using 'SetMatrix' function

   VecD() {}
   VecD(Dbl r              ) {set(r      );}
   VecD(Dbl x, Dbl y, Dbl z) {set(x, y, z);}
   VecD(C VecD2 &v2 , Dbl z) {set(v2  , z);}
   VecD(C Vec   &v);
   VecD(C VecI  &v);
};
/******************************************************************************/
struct Vec4 // Vector 4D
{
   union
   {
      struct{Flt x, y, z, w;};
      struct{Flt c[4]      ;}; // component
   };

   Vec2& v2()  {return (Vec2&)T;} // get reference to self as       Vec2
   Vec & v3()  {return (Vec &)T;} // get reference to self as       Vec 
 C Vec2& v2()C {return (Vec2&)T;} // get reference to self as const Vec2
 C Vec & v3()C {return (Vec &)T;} // get reference to self as const Vec 

   Vec4& zero(                          ) {x=y=z=w=0;                  return T;}
   Vec4& set (Flt r                     ) {x=y=z=w=r;                  return T;}
   Vec4& set (Flt x, Flt y, Flt z, Flt w) {T.x=x; T.y=y; T.z=z; T.w=w; return T;}
   Vec4& set (C Vec2 &v2,   Flt z, Flt w) {T.v2()=v2;    T.z=z; T.w=w; return T;}
   Vec4& set (C Vec  &v3,          Flt w) {T.v3()=v3;           T.w=w; return T;}
   Vec4& set (C Vec2 &a ,   C Vec2 &b   ) {x=a.x; y=a.y; z=b.x; w=b.y; return T;}

          Vec4& operator+=(  Flt   r) {x+=  r; y+=  r; z+=  r; w+=  r; return T;}
          Vec4& operator-=(  Flt   r) {x-=  r; y-=  r; z-=  r; w-=  r; return T;}
          Vec4& operator*=(  Flt   r) {x*=  r; y*=  r; z*=  r; w*=  r; return T;}
          Vec4& operator/=(  Flt   r) {x/=  r; y/=  r; z/=  r; w/=  r; return T;}
          Vec4& operator+=(C Vec4 &v) {x+=v.x; y+=v.y; z+=v.z; w+=v.w; return T;}
          Vec4& operator-=(C Vec4 &v) {x-=v.x; y-=v.y; z-=v.z; w-=v.w; return T;}
          Vec4& operator*=(C Vec4 &v) {x*=v.x; y*=v.y; z*=v.z; w*=v.w; return T;}
          Vec4& operator/=(C Vec4 &v) {x/=v.x; y/=v.y; z/=v.z; w/=v.w; return T;}
          Bool  operator==(C Vec4 &v)C;
          Bool  operator!=(C Vec4 &v)C;

   friend Vec4  operator+ (C Vec4 &v,   Flt   r) {return Vec4(v.x+r, v.y+r, v.z+r, v.w+r);}
   friend Vec4  operator- (C Vec4 &v,   Flt   r) {return Vec4(v.x-r, v.y-r, v.z-r, v.w-r);}
   friend Vec4  operator* (C Vec4 &v,   Flt   r) {return Vec4(v.x*r, v.y*r, v.z*r, v.w*r);}
   friend Vec4  operator/ (C Vec4 &v,   Flt   r) {return Vec4(v.x/r, v.y/r, v.z/r, v.w/r);}
   friend Vec4  operator+ (  Flt   r, C Vec4 &v) {return Vec4(r+v.x, r+v.y, r+v.z, r+v.w);}
   friend Vec4  operator- (  Flt   r, C Vec4 &v) {return Vec4(r-v.x, r-v.y, r-v.z, r-v.w);}
   friend Vec4  operator* (  Flt   r, C Vec4 &v) {return Vec4(r*v.x, r*v.y, r*v.z, r*v.w);}
   friend Vec4  operator/ (  Flt   r, C Vec4 &v) {return Vec4(r/v.x, r/v.y, r/v.z, r/v.w);}
   friend Vec4  operator+ (C Vec4 &a, C Vec4 &b) {return Vec4(a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w);}
   friend Vec4  operator- (C Vec4 &a, C Vec4 &b) {return Vec4(a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w);}
   friend Vec4  operator* (C Vec4 &a, C Vec4 &b) {return Vec4(a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w);}
   friend Vec4  operator/ (C Vec4 &a, C Vec4 &b) {return Vec4(a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w);}
   friend Vec4  operator- (C Vec4 &v           ) {return Vec4(-v.x, -v.y, -v.z, -v.w);}
   friend Vec4  operator! (C Vec4 &v           ) {       Vec4 ret=v; ret.normalize(); return ret;} // return normalized vector

   Bool  any      ()C {return  Any (x, y, z, w);}     // if any component  is  non-zero
   Bool  all      ()C {return x && y && z && w ;}     // if all components are non-zero
   Int   minI     ()C {return  MinI(x, y, z, w);}     // components minimum index
   Int   maxI     ()C {return  MaxI(x, y, z, w);}     // components maximum index
   Flt   min      ()C {return  Min (x, y, z, w);}     // components minimum
   Flt   max      ()C {return  Max (x, y, z, w);}     // components maximum
   Flt   avg      ()C {return  Avg (x, y, z, w);}     // components average
   Flt   sum      ()C {return       x+ y+ z+ w ;}     // components sum
   Flt   length   ()C;                                // get         length
   Flt   length2  ()C {return x*x + y*y + z*z + w*w;} // get squared length
   Flt   normalize();                                 // normalize and return previous length
   Vec4& chs      ();                                 // change sign of all components
   Vec4& abs      ();                                 // absolute       all components
   Vec4& sat      ();                                 // saturate       all components

   Str asText(Int precision=INT_MAX)C; // return as text

   Vec4() {}
   Vec4(Flt r                     ) {set(r         );}
   Vec4(Flt x, Flt y, Flt z, Flt w) {set(x, y, z, w);}
   Vec4(C Vec2  &v,   Flt z, Flt w) {set(v,    z, w);}
   Vec4(C Vec   &v,          Flt w) {set(v,       w);}
   Vec4(C Vec2  &a,      C Vec2 &b) {set(a,    b   );}
   Vec4(C VecD4 &v);
   Vec4(C VecI4 &v);
   Vec4(C VecB4 &v);
};extern const Vec4
   Vec4Zero; // Vec4(0, 0, 0, 0)
/******************************************************************************/
struct VecD4 // Vector 4D (double precision)
{
   union
   {
      struct{Dbl x, y, z, w;};
      struct{Dbl c[4]      ;}; // component
   };

   VecD2& v2()  {return (VecD2&)T;} // get reference to self as       VecD2
   VecD & v3()  {return (VecD &)T;} // get reference to self as       VecD 
 C VecD2& v2()C {return (VecD2&)T;} // get reference to self as const VecD2
 C VecD & v3()C {return (VecD &)T;} // get reference to self as const VecD 

   VecD4& zero(                          ) {x=y=z=w=0;                  return T;}
   VecD4& set (Dbl r                     ) {x=y=z=w=r;                  return T;}
   VecD4& set (Dbl x, Dbl y, Dbl z, Dbl w) {T.x=x; T.y=y; T.z=z; T.w=w; return T;}
   VecD4& set (C VecD2 &v2 , Dbl z, Dbl w) {T.v2()=v2;    T.z=z; T.w=w; return T;}
   VecD4& set (C VecD  &v3 ,        Dbl w) {T.v3()=v3;           T.w=w; return T;}
   VecD4& set (C VecD2 &a  ,   C VecD2 &b) {x=a.x; y=a.y; z=b.x; w=b.y; return T;}

          VecD4& operator+=(  Dbl    r) {x+=  r; y+=  r; z+=  r; w+=  r; return T;}
          VecD4& operator-=(  Dbl    r) {x-=  r; y-=  r; z-=  r; w-=  r; return T;}
          VecD4& operator*=(  Dbl    r) {x*=  r; y*=  r; z*=  r; w*=  r; return T;}
          VecD4& operator/=(  Dbl    r) {x/=  r; y/=  r; z/=  r; w/=  r; return T;}
          VecD4& operator+=(C VecD4 &v) {x+=v.x; y+=v.y; z+=v.z; w+=v.w; return T;}
          VecD4& operator-=(C VecD4 &v) {x-=v.x; y-=v.y; z-=v.z; w-=v.w; return T;}
          VecD4& operator*=(C VecD4 &v) {x*=v.x; y*=v.y; z*=v.z; w*=v.w; return T;}
          VecD4& operator/=(C VecD4 &v) {x/=v.x; y/=v.y; z/=v.z; w/=v.w; return T;}
          Bool   operator==(C VecD4 &v)C;
          Bool   operator!=(C VecD4 &v)C;

   friend VecD4  operator+ (C VecD4 &v,   Dbl    r) {return VecD4(v.x+r, v.y+r, v.z+r, v.w+r);}
   friend VecD4  operator- (C VecD4 &v,   Dbl    r) {return VecD4(v.x-r, v.y-r, v.z-r, v.w-r);}
   friend VecD4  operator* (C VecD4 &v,   Dbl    r) {return VecD4(v.x*r, v.y*r, v.z*r, v.w*r);}
   friend VecD4  operator/ (C VecD4 &v,   Dbl    r) {return VecD4(v.x/r, v.y/r, v.z/r, v.w/r);}
   friend VecD4  operator+ (  Dbl    r, C VecD4 &v) {return VecD4(r+v.x, r+v.y, r+v.z, r+v.w);}
   friend VecD4  operator- (  Dbl    r, C VecD4 &v) {return VecD4(r-v.x, r-v.y, r-v.z, r-v.w);}
   friend VecD4  operator* (  Dbl    r, C VecD4 &v) {return VecD4(r*v.x, r*v.y, r*v.z, r*v.w);}
   friend VecD4  operator/ (  Dbl    r, C VecD4 &v) {return VecD4(r/v.x, r/v.y, r/v.z, r/v.w);}
   friend VecD4  operator+ (C VecD4 &a, C VecD4 &b) {return VecD4(a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w);}
   friend VecD4  operator- (C VecD4 &a, C VecD4 &b) {return VecD4(a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w);}
   friend VecD4  operator* (C VecD4 &a, C VecD4 &b) {return VecD4(a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w);}
   friend VecD4  operator/ (C VecD4 &a, C VecD4 &b) {return VecD4(a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w);}
   friend VecD4  operator- (C VecD4 &v            ) {return VecD4(-v.x, -v.y, -v.z, -v.w);}
   friend VecD4  operator! (C VecD4 &v            ) {       VecD4 ret=v; ret.normalize(); return ret;} // return normalized vector

   Bool   any      ()C {return x || y || z || w ;}      // if any component  is  non-zero
   Bool   all      ()C {return x && y && z && w ;}      // if all components are non-zero
   Int    minI     ()C {return  MinI(x, y, z, w);}      // components minimum index
   Int    maxI     ()C {return  MaxI(x, y, z, w);}      // components maximum index
   Dbl    min      ()C {return  Min (x, y, z, w);}      // components minimum
   Dbl    max      ()C {return  Max (x, y, z, w);}      // components maximum
   Dbl    avg      ()C {return  Avg (x, y, z, w);}      // components average
   Dbl    sum      ()C {return       x+ y+ z+ w ;}      // components sum
   Dbl    length   ()C;                                 // get         length
   Dbl    length2  ()C {return  x*x + y*y + z*z + w*w;} // get squared length
   Dbl    normalize();                                  // normalize and return previous length
   VecD4& chs      ();                                  // change sign of all components
   VecD4& abs      ();                                  // absolute       all components
   VecD4& sat      ();                                  // saturate       all components

   Str asText(Int precision=INT_MAX)C; // return as text

   VecD4() {}
   VecD4(Dbl r                     ) {set(r         );}
   VecD4(Dbl x, Dbl y, Dbl z, Dbl w) {set(x, y, z, w);}
   VecD4(C VecD2 &v,   Dbl z, Dbl w) {set(v,    z, w);}
   VecD4(C VecD  &v,          Dbl w) {set(v,       w);}
   VecD4(C VecD2 &a,     C VecD2 &b) {set(a,    b   );}
   VecD4(C Vec4  &v);
};
/******************************************************************************/
struct VecB4 // Vector 4D (Byte)
{
   union
   {
      struct{Byte x, y, z, w;};
      struct{Byte c[4]      ;}; // component
      struct{UInt u         ;};
   };

   VecB4& zero(                              ) {u=0;                        return T;}
   VecB4& set (Byte i                        ) {x=y=z=w=i;                  return T;}
   VecB4& set (Byte x, Byte y, Byte z, Byte w) {T.x=x; T.y=y; T.z=z; T.w=w; return T;}

          VecB4& operator++(  Int     ) {x++ ; y++ ; z++ ; w++ ; return T;}
          VecB4& operator--(  Int     ) {x-- ; y-- ; z-- ; w-- ; return T;}
          VecB4& operator+=(  Int    i) {x+=i; y+=i; z+=i; w+=i; return T;}
          VecB4& operator-=(  Int    i) {x-=i; y-=i; z-=i; w-=i; return T;}
          Bool   operator==(C VecB4 &v)C{return u==v.u;}
          Bool   operator!=(C VecB4 &v)C{return u!=v.u;}

   friend VecB4  operator+ (C VecB4 &v, Int i) {return VecB4(v.x+i, v.y+i, v.z+i, v.w+i);}
   friend VecB4  operator- (C VecB4 &v, Int i) {return VecB4(v.x-i, v.y-i, v.z-i, v.w-i);}

   Bool   any         (         )C {return u!=0             ;}                            // if any component  is  non-zero, faster version of "x || y || z || w"
   Bool   all         (         )C {return x && y && z && w ;}                            // if all components are non-zero
   Bool   allDifferent(         )C {return x!=y && x!=z && x!=w && y!=z && y!=w && z!=w;} // if all components are different
   Int    minI        (         )C {return  MinI(x, y, z, w);}                            // components minimum index
   Int    maxI        (         )C {return  MaxI(x, y, z, w);}                            // components maximum index
   Int    min         (         )C {return  Min (x, y, z, w);}                            // components minimum
   Int    max         (         )C {return  Max (x, y, z, w);}                            // components maximum
   Int    sum         (         )C {return       x+ y+ z+ w ;}                            // components sum
   Int    find        (Int value)C;                                                       // get index of first component that equals 'value' (-1 if none)
   VecB4& reverse     (         ) {Swap(c[0], c[3]); Swap(c[1], c[2]); return T;}         // reverse components order

   VecB4() {}
   VecB4(Byte i                        ) {set(i         );}
   VecB4(Byte x, Byte y, Byte z, Byte w) {set(x, y, z, w);}
};
/******************************************************************************/
struct VecI2 // Vector 2D (integer)
{
   union
   {
      struct{Int x, y;};
      struct{Int c[2];}; // component
   };

   VecI2& zero(            ) {x=y=0;        return T;}
   VecI2& set (Int i       ) {x=y=i;        return T;}
   VecI2& set (Int x, Int y) {T.x=x; T.y=y; return T;}

          VecI2& operator ++(  Int     ) {x++   ; y++   ; return T;}
          VecI2& operator --(  Int     ) {x--   ; y--   ; return T;}
          VecI2& operator +=(  Int    i) {x+=  i; y+=  i; return T;}
          VecI2& operator -=(  Int    i) {x-=  i; y-=  i; return T;}
          VecI2& operator *=(  Int    i) {x*=  i; y*=  i; return T;}
          VecI2& operator /=(  Int    i) {x/=  i; y/=  i; return T;}
          VecI2& operator +=(C VecI2 &v) {x+=v.x; y+=v.y; return T;}
          VecI2& operator -=(C VecI2 &v) {x-=v.x; y-=v.y; return T;}
          VecI2& operator *=(C VecI2 &v) {x*=v.x; y*=v.y; return T;}
          VecI2& operator /=(C VecI2 &v) {x/=v.x; y/=v.y; return T;}
          VecI2& operator<<=(  Int    i) {x<<= i; y<<= i; return T;}
          VecI2& operator>>=(  Int    i) {x>>= i; y>>= i; return T;}
          VecI2& operator &=(C RectI &r); // intersect
          Bool   operator ==(C VecI2 &v)C{return x==v.x && y==v.y;}
          Bool   operator !=(C VecI2 &v)C{return x!=v.x || y!=v.y;}

   friend VecI2  operator + (C VecI2 &v,   Int    i) {return VecI2(v.x+i, v.y+i);}
   friend VecI2  operator - (C VecI2 &v,   Int    i) {return VecI2(v.x-i, v.y-i);}
   friend Vec2   operator + (C VecI2 &v,   Flt    f) {return Vec2 (v.x+f, v.y+f);}
   friend Vec2   operator - (C VecI2 &v,   Flt    f) {return Vec2 (v.x-f, v.y-f);}
   friend VecI2  operator * (C VecI2 &v,   Int    i) {return VecI2(v.x*i, v.y*i);}
   friend VecI2  operator / (C VecI2 &v,   Int    i) {return VecI2(v.x/i, v.y/i);}
   friend Vec2   operator * (C VecI2 &v,   Flt    f) {return Vec2 (v.x*f, v.y*f);}
   friend Vec2   operator / (C VecI2 &v,   Flt    f) {return Vec2 (v.x/f, v.y/f);}
   friend VecI2  operator * (  Int    i, C VecI2 &v) {return VecI2(i*v.x, i*v.y);}
   friend VecI2  operator / (  Int    i, C VecI2 &v) {return VecI2(i/v.x, i/v.y);}
   friend Vec2   operator * (  Flt    f, C VecI2 &v) {return Vec2 (f*v.x, f*v.y);}
   friend Vec2   operator / (  Flt    f, C VecI2 &v) {return Vec2 (f/v.x, f/v.y);}
   friend VecI2  operator + (C VecI2 &a, C VecI2 &b) {return VecI2(a.x+b.x, a.y+b.y);}
   friend VecI2  operator - (C VecI2 &a, C VecI2 &b) {return VecI2(a.x-b.x, a.y-b.y);}
   friend VecI2  operator * (C VecI2 &a, C VecI2 &b) {return VecI2(a.x*b.x, a.y*b.y);}
   friend VecI2  operator / (C VecI2 &a, C VecI2 &b) {return VecI2(a.x/b.x, a.y/b.y);}
   friend VecI2  operator<< (C VecI2 &v,   Int    i) {return VecI2(v.x<<i, v.y<<i);}
   friend VecI2  operator>> (C VecI2 &v,   Int    i) {return VecI2(v.x>>i, v.y>>i);}
   friend VecI2  operator & (C VecI2 &v, C RectI &r) {return VecI2(v)&=r;} // intersection
   friend VecI2  operator - (C VecI2 &v            ) {return VecI2(-v.x, -v.y);}

   VecI  xy0()C; // return as VecI(x, y, 0)
   VecI  x0y()C; // return as VecI(x, 0, y)
   VecI _0xy()C; // return as VecI(0, x, y)
   VecI _0yx()C; // return as VecI(0, y, x)

   Bool   any         (         )C {return    x || y ;}         // if any  component  is  non-zero
   Bool   all         (         )C {return    x && y ;}         // if all  components are non-zero
   Bool   allDifferent(         )C {return      x!=y ;}         // if all  components are different
   Int    minI        (         )C {return MinI(x, y);}         // components minimum index
   Int    maxI        (         )C {return MaxI(x, y);}         // components maximum index
   Int    min         (         )C {return Min (x, y);}         // components minimum
   Int    max         (         )C {return Max (x, y);}         // components maximum
   Int    sum         (         )C {return      x+ y ;}         // components sum
   Int    mul         (         )C {return      x* y ;}         // components multiplication
   Flt    length      (         )C;                             // get         length
   Int    length2     (         )C {return  x*x + y*y;}         // get squared length
   Int    find        (Int value)C;                             // get index of first component that equals 'value' (-1 if none)
   VecI2& swap        (         ) {Swap(c[0], c[1]); return T;} // swap    components
   VecI2& reverse     (         ) {Swap(c[0], c[1]); return T;} // reverse components order
   VecI2& rotateOrder (         ) {Swap(c[0], c[1]); return T;} // rotate  components order
   VecI2& chs         (         );                              // change sign of all components
   VecI2& abs         (         );                              // absolute       all components
   VecI2& sat         (         );                              // saturate       all components

   VecI2() {}
   VecI2(Int i       ) {set(i   );}
   VecI2(Int x, Int y) {set(x, y);}
};
/******************************************************************************/
struct VecI // Vector 3D (integer)
{
   union
   {
      struct{Int x, y, z;};
      struct{Int c[3]   ;}; // component
   };

   VecI2& v2()  {return (VecI2&)T;} // get reference to self as       VecI2
 C VecI2& v2()C {return (VecI2&)T;} // get reference to self as const VecI2

   VecI& zero(                   ) {x=y=z=0;             return T;}
   VecI& set (Int i              ) {x=y=z=i;             return T;}
   VecI& set (Int x, Int y, Int z) {T.x=x; T.y=y; T.z=z; return T;}
   VecI& set (C VecI2 &v2 , Int z) {T.v2()=v2;    T.z=z; return T;}

          VecI& operator ++(  Int    ) {x++   ; y++   ; z++   ; return T;}
          VecI& operator --(  Int    ) {x--   ; y--   ; z--   ; return T;}
          VecI& operator +=(  Int   i) {x+=  i; y+=  i; z+=  i; return T;}
          VecI& operator -=(  Int   i) {x-=  i; y-=  i; z-=  i; return T;}
          VecI& operator *=(  Int   i) {x*=  i; y*=  i; z*=  i; return T;}
          VecI& operator /=(  Int   i) {x/=  i; y/=  i; z/=  i; return T;}
          VecI& operator +=(C VecI &v) {x+=v.x; y+=v.y; z+=v.z; return T;}
          VecI& operator -=(C VecI &v) {x-=v.x; y-=v.y; z-=v.z; return T;}
          VecI& operator *=(C VecI &v) {x*=v.x; y*=v.y; z*=v.z; return T;}
          VecI& operator /=(C VecI &v) {x/=v.x; y/=v.y; z/=v.z; return T;}
          VecI& operator<<=(  Int   i) {x<<= i; y<<= i; z<<= i; return T;}
          VecI& operator>>=(  Int   i) {x>>= i; y>>= i; z>>= i; return T;}
          VecI& operator &=(C BoxI &b); // intersect
          Bool  operator ==(C VecI &v)C{return x==v.x && y==v.y && z==v.z;}
          Bool  operator !=(C VecI &v)C{return x!=v.x || y!=v.y || z!=v.z;}

   friend VecI  operator + (C VecI &v,   Int   i) {return VecI(v.x+i, v.y+i, v.z+i);}
   friend VecI  operator - (C VecI &v,   Int   i) {return VecI(v.x-i, v.y-i, v.z-i);}
   friend Vec   operator + (C VecI &v,   Flt   f) {return Vec (v.x+f, v.y+f, v.z+f);}
   friend Vec   operator - (C VecI &v,   Flt   f) {return Vec (v.x-f, v.y-f, v.z-f);}
   friend VecI  operator * (C VecI &v,   Int   i) {return VecI(v.x*i, v.y*i, v.z*i);}
   friend VecI  operator / (C VecI &v,   Int   i) {return VecI(v.x/i, v.y/i, v.z/i);}
   friend Vec   operator * (C VecI &v,   Flt   f) {return Vec (v.x*f, v.y*f, v.z*f);}
   friend Vec   operator / (C VecI &v,   Flt   f) {return Vec (v.x/f, v.y/f, v.z/f);}
   friend VecI  operator * (  Int   i, C VecI &v) {return VecI(i*v.x, i*v.y, i*v.z);}
   friend VecI  operator / (  Int   i, C VecI &v) {return VecI(i/v.x, i/v.y, i/v.z);}
   friend Vec   operator * (  Flt   f, C VecI &v) {return Vec (f*v.x, f*v.y, f*v.z);}
   friend Vec   operator / (  Flt   f, C VecI &v) {return Vec (f/v.x, f/v.y, f/v.z);}
   friend VecI  operator + (C VecI &a, C VecI &b) {return VecI(a.x+b.x, a.y+b.y, a.z+b.z);}
   friend VecI  operator - (C VecI &a, C VecI &b) {return VecI(a.x-b.x, a.y-b.y, a.z-b.z);}
   friend VecI  operator * (C VecI &a, C VecI &b) {return VecI(a.x*b.x, a.y*b.y, a.z*b.z);}
   friend VecI  operator / (C VecI &a, C VecI &b) {return VecI(a.x/b.x, a.y/b.y, a.z/b.z);}
   friend VecI  operator<< (C VecI &v,   Int   i) {return VecI(v.x<<i, v.y<<i, v.z<<i);}
   friend VecI  operator>> (C VecI &v,   Int   i) {return VecI(v.x>>i, v.y>>i, v.z>>i);}
   friend VecI  operator & (C VecI &v, C BoxI &b) {return VecI(v)&=b;} // intersection
   friend VecI  operator - (C VecI &v           ) {return VecI(-v.x, -v.y, -v.z);}

   VecI2 xy ()C {return VecI2(x, y   );} // return as VecI2(x, y)
   VecI2 xz ()C {return VecI2(x, z   );} // return as VecI2(x, z)
   VecI2 yx ()C {return VecI2(y, x   );} // return as VecI2(y, x)
   VecI2 yz ()C {return VecI2(y, z   );} // return as VecI2(y, z)
   VecI2 zx ()C {return VecI2(z, x   );} // return as VecI2(z, x)
   VecI2 zy ()C {return VecI2(z, y   );} // return as VecI2(z, y)
   VecI  xzy()C {return VecI (x, z, y);} // return as VecI (x, z, y)
   VecI  x0z()C {return VecI (x, 0, z);} // return as VecI (x, 0, z)

   Bool  any         (         )C {return   x || y || z ;}       // if any  component  is  non-zero
   Bool  all         (         )C {return   x && y && z ;}       // if all  components are non-zero
   Bool  allDifferent(         )C {return x!=y && x!=z && y!=z;} // if all  components are different
   Int   minI        (         )C {return  MinI(x, y, z);}       // components minimum index
   Int   maxI        (         )C {return  MaxI(x, y, z);}       // components maximum index
   Int   min         (         )C {return  Min (x, y, z);}       // components minimum
   Int   max         (         )C {return  Max (x, y, z);}       // components maximum
   Int   sum         (         )C {return       x+ y+ z ;}       // components sum
   Flt   length      (         )C;                               // get         length
   Int   length2     (         )C {return x*x + y*y + z*z;}      // get squared length
   Int   find        (Int value)C;                               // get index of first component that equals 'value' (-1 if none)
   VecI& reverse     (         ) {Swap(c[0], c[2]); return T;}   // reverse components order
   VecI& rotateOrder (         );                                // rotate  components order
   VecI& chs         (         );                                // change sign of all components
   VecI& abs         (         );                                // absolute       all components
   VecI& sat         (         );                                // saturate       all components

   VecI() {}
   VecI(Int i              ) {set(i      );}
   VecI(Int x, Int y, Int z) {set(x, y, z);}
   VecI(C VecI2 &v2 , Int z) {set(v2  , z);}
};
/******************************************************************************/
struct VecI4 // Vector 4D (integer)
{
   union
   {
      struct{Int x, y, z, w;};
      struct{Int c[4]      ;}; // component
   };

   VecI2& v2()  {return (VecI2&)T;} // get reference to self as       VecI2
   VecI & v3()  {return (VecI &)T;} // get reference to self as       VecI
 C VecI2& v2()C {return (VecI2&)T;} // get reference to self as const VecI2
 C VecI & v3()C {return (VecI &)T;} // get reference to self as const VecI

   VecI4& zero(                          ) {x=y=z=w=0;                  return T;}
   VecI4& set (Int i                     ) {x=y=z=w=i;                  return T;}
   VecI4& set (Int x, Int y, Int z, Int w) {T.x=x; T.y=y; T.z=z; T.w=w; return T;}
   VecI4& set (C VecI2 &v2 , Int z, Int w) {T.v2()=v2;    T.z=z; T.w=w; return T;}
   VecI4& set (C VecI  &v3 ,        Int w) {T.v3()=v3;           T.w=w; return T;}
   VecI4& set (C VecI2 &a  ,   C VecI2 &b) {x=a.x; y=a.y; z=b.x; w=b.y; return T;}

          VecI4& operator ++(  Int     ) {x++   ; y++   ; z++   ; w++   ; return T;}
          VecI4& operator --(  Int     ) {x--   ; y--   ; z--   ; w--   ; return T;}
          VecI4& operator +=(  Int    i) {x+=  i; y+=  i; z+=  i; w+=  i; return T;}
          VecI4& operator -=(  Int    i) {x-=  i; y-=  i; z-=  i; w-=  i; return T;}
          VecI4& operator *=(  Int    i) {x*=  i; y*=  i; z*=  i; w*=  i; return T;}
          VecI4& operator /=(  Int    i) {x/=  i; y/=  i; z/=  i; w/=  i; return T;}
          VecI4& operator +=(C VecI4 &v) {x+=v.x; y+=v.y; z+=v.z; w+=v.w; return T;}
          VecI4& operator +=(C VecB4 &v) {x+=v.x; y+=v.y; z+=v.z; w+=v.w; return T;}
          VecI4& operator -=(C VecI4 &v) {x-=v.x; y-=v.y; z-=v.z; w-=v.w; return T;}
          VecI4& operator -=(C VecB4 &v) {x-=v.x; y-=v.y; z-=v.z; w-=v.w; return T;}
          VecI4& operator *=(C VecI4 &v) {x*=v.x; y*=v.y; z*=v.z; w*=v.w; return T;}
          VecI4& operator /=(C VecI4 &v) {x/=v.x; y/=v.y; z/=v.z; w/=v.w; return T;}
          VecI4& operator<<=(  Int    i) {x<<= i; y<<= i; z<<= i; w<<= i; return T;}
          VecI4& operator>>=(  Int    i) {x>>= i; y>>= i; z>>= i; w>>= i; return T;}
          Bool   operator ==(C VecI4 &v)C{return x==v.x && y==v.y && z==v.z && w==v.w;}
          Bool   operator !=(C VecI4 &v)C{return x!=v.x || y!=v.y || z!=v.z || w!=v.w;}

   friend VecI4  operator + (C VecI4 &v,   Int    i) {return VecI4(v.x+i, v.y+i, v.z+i, v.w+i);}
   friend VecI4  operator - (C VecI4 &v,   Int    i) {return VecI4(v.x-i, v.y-i, v.z-i, v.w-i);}
   friend Vec4   operator + (C VecI4 &v,   Flt    f) {return Vec4 (v.x+f, v.y+f, v.z+f, v.w+f);}
   friend Vec4   operator - (C VecI4 &v,   Flt    f) {return Vec4 (v.x-f, v.y-f, v.z-f, v.w-f);}
   friend VecI4  operator * (C VecI4 &v,   Int    i) {return VecI4(v.x*i, v.y*i, v.z*i, v.w*i);}
   friend VecI4  operator / (C VecI4 &v,   Int    i) {return VecI4(v.x/i, v.y/i, v.z/i, v.w/i);}
   friend Vec4   operator * (C VecI4 &v,   Flt    f) {return Vec4 (v.x*f, v.y*f, v.z*f, v.w*f);}
   friend Vec4   operator / (C VecI4 &v,   Flt    f) {return Vec4 (v.x/f, v.y/f, v.z/f, v.w/f);}
   friend VecI4  operator * (  Int    i, C VecI4 &v) {return VecI4(i*v.x, i*v.y, i*v.z, i*v.w);}
   friend VecI4  operator / (  Int    i, C VecI4 &v) {return VecI4(i/v.x, i/v.y, i/v.z, i/v.w);}
   friend Vec4   operator * (  Flt    f, C VecI4 &v) {return Vec4 (f*v.x, f*v.y, f*v.z, f*v.w);}
   friend Vec4   operator / (  Flt    f, C VecI4 &v) {return Vec4 (f/v.x, f/v.y, f/v.z, f/v.w);}
   friend VecI4  operator + (C VecI4 &a, C VecI4 &b) {return VecI4(a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w);}
   friend VecI4  operator - (C VecI4 &a, C VecI4 &b) {return VecI4(a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w);}
   friend VecI4  operator * (C VecI4 &a, C VecI4 &b) {return VecI4(a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w);}
   friend VecI4  operator / (C VecI4 &a, C VecI4 &b) {return VecI4(a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w);}
   friend VecI4  operator<< (C VecI4 &v,   Int    i) {return VecI4(v.x<<i, v.y<<i, v.z<<i, v.w<<i);}
   friend VecI4  operator>> (C VecI4 &v,   Int    i) {return VecI4(v.x>>i, v.y>>i, v.z>>i, v.w>>i);}
   friend VecI4  operator - (C VecI4 &v            ) {return VecI4(-v.x, -v.y, -v.z, -v.w);}

   Bool   any         (         )C {return x || y || z || w ;}                            // if any  component  is  non-zero
   Bool   all         (         )C {return x && y && z && w ;}                            // if all  components are non-zero
   Bool   allDifferent(         )C {return x!=y && x!=z && x!=w && y!=z && y!=w && z!=w;} // if all  components are different
   Int    minI        (         )C {return  MinI(x, y, z, w);}                            // components minimum index
   Int    maxI        (         )C {return  MaxI(x, y, z, w);}                            // components maximum index
   Int    min         (         )C {return  Min (x, y, z, w);}                            // components minimum
   Int    max         (         )C {return  Max (x, y, z, w);}                            // components maximum
   Int    sum         (         )C {return       x+ y+ z+ w ;}                            // components sum
   Flt    length      (         )C;                                                       // get         length
   Int    length2     (         )C {return x*x + y*y + z*z + w*w;}                        // get squared length
   Int    find        (Int value)C;                                                       // get index of first component that equals 'value' (-1 if none)
   VecI4& reverse     (         ) {Swap(c[0], c[3]); Swap(c[1], c[2]); return T;}         // reverse components order
   VecI4& rotateOrder (         );                                                        // rotate  components order
   VecI4& chs         (         );                                                        // change sign of all components
   VecI4& abs         (         );                                                        // absolute       all components
   VecI4& sat         (         );                                                        // saturate       all components

   VecI tri0()C {return VecI(x, y, w);}
   VecI tri1()C {return VecI(w, y, z);}

   VecI4() {}
   VecI4(Int i                     ) {set(i         );}
   VecI4(Int x, Int y, Int z, Int w) {set(x, y, z, w);}
   VecI4(C VecI2 &v,   Int z, Int w) {set(v,    z, w);}
   VecI4(C VecI  &v,          Int w) {set(v,       w);}
   VecI4(C VecI2 &a,     C VecI2 &b) {set(a,    b   );}
};
/******************************************************************************/
// ROUNDING
/******************************************************************************/
// truncate, remove fractional part, Sample Usage: Trunc(7.3) -> 7, Trunc(7.9) -> 7
inline Int   Trunc(  Int    x) {return     x ;}
inline Int   Trunc(  Flt    x) {return Int(x);}
inline Int   Trunc(  Dbl    x) {return Int(x);}
inline VecI2 Trunc(C Vec2  &v) {return VecI2(Trunc(v.x), Trunc(v.y)                        );}
inline VecI2 Trunc(C VecD2 &v) {return VecI2(Trunc(v.x), Trunc(v.y)                        );}
inline VecI  Trunc(C Vec   &v) {return VecI (Trunc(v.x), Trunc(v.y), Trunc(v.z)            );}
inline VecI  Trunc(C VecD  &v) {return VecI (Trunc(v.x), Trunc(v.y), Trunc(v.z)            );}
inline VecI4 Trunc(C Vec4  &v) {return VecI4(Trunc(v.x), Trunc(v.y), Trunc(v.z), Trunc(v.w));}
inline VecI4 Trunc(C VecD4 &v) {return VecI4(Trunc(v.x), Trunc(v.y), Trunc(v.z), Trunc(v.w));}

// round, round to nearest integer, Sample Usage: Round(7.3) -> 7, Round(7.9) -> 8
inline Int   Round(  Int    x) {return x;}
inline Int   Round(  Flt    x) {return (x>=0) ? Trunc(x+0.5f) : Trunc(x-0.5f);}
inline Int   Round(  Dbl    x) {return (x>=0) ? Trunc(x+0.5 ) : Trunc(x-0.5 );}
inline VecI2 Round(C Vec2  &x) {return VecI2(Round(x.x), Round(x.y)                        );}
inline VecI2 Round(C VecD2 &x) {return VecI2(Round(x.x), Round(x.y)                        );}
inline VecI  Round(C Vec   &x) {return VecI (Round(x.x), Round(x.y), Round(x.z)            );}
inline VecI  Round(C VecD  &x) {return VecI (Round(x.x), Round(x.y), Round(x.z)            );}
inline VecI4 Round(C Vec4  &x) {return VecI4(Round(x.x), Round(x.y), Round(x.z), Round(x.w));}
inline VecI4 Round(C VecD4 &x) {return VecI4(Round(x.x), Round(x.y), Round(x.z), Round(x.w));}

// floor, round to nearest integer which is smaller or equal to value, Sample Usage: Floor(7.3) -> 7, Floor(7.9) -> 7
inline Int   Floor(  Int    x) {return x;}
       Int   Floor(  Flt    x);
       Int   Floor(  Dbl    x);
inline VecI2 Floor(C Vec2  &x) {return VecI2(Floor(x.x), Floor(x.y)                        );}
inline VecI2 Floor(C VecD2 &x) {return VecI2(Floor(x.x), Floor(x.y)                        );}
inline VecI  Floor(C Vec   &x) {return VecI (Floor(x.x), Floor(x.y), Floor(x.z)            );}
inline VecI  Floor(C VecD  &x) {return VecI (Floor(x.x), Floor(x.y), Floor(x.z)            );}
inline VecI4 Floor(C Vec4  &x) {return VecI4(Floor(x.x), Floor(x.y), Floor(x.z), Floor(x.w));}
inline VecI4 Floor(C VecD4 &x) {return VecI4(Floor(x.x), Floor(x.y), Floor(x.z), Floor(x.w));}

// ceil, round to nearest integer which is greater or equal to value, Sample Usage: Ceil(7.3) -> 8, Ceil(7.9) -> 8
inline Int   Ceil(  Int    x) {return x;}
       Int   Ceil(  Flt    x);
       Int   Ceil(  Dbl    x);
inline VecI2 Ceil(C Vec2  &x) {return VecI2(Ceil(x.x), Ceil(x.y)                      );}
inline VecI2 Ceil(C VecD2 &x) {return VecI2(Ceil(x.x), Ceil(x.y)                      );}
inline VecI  Ceil(C Vec   &x) {return VecI (Ceil(x.x), Ceil(x.y), Ceil(x.z)           );}
inline VecI  Ceil(C VecD  &x) {return VecI (Ceil(x.x), Ceil(x.y), Ceil(x.z)           );}
inline VecI4 Ceil(C Vec4  &x) {return VecI4(Ceil(x.x), Ceil(x.y), Ceil(x.z), Ceil(x.w));}
inline VecI4 Ceil(C VecD4 &x) {return VecI4(Ceil(x.x), Ceil(x.y), Ceil(x.z), Ceil(x.w));}

// get fraction, gets fractional part of a real value, Sample Usage: Frac(7.3) -> 0.3, Frac(7.9) -> 0.9
inline Flt  Frac(  Flt   x) {return (x>=0) ? x-Trunc(x) : x-Floor(x);} // [0..1)
       Dbl  Frac(  Dbl   x);                                           // [0..1) high precision version
inline Vec2 Frac(C Vec2 &v) {return Vec2(Frac(v.x), Frac(v.y)                      );}
inline Vec  Frac(C Vec  &v) {return Vec (Frac(v.x), Frac(v.y), Frac(v.z)           );}
inline Vec4 Frac(C Vec4 &v) {return Vec4(Frac(v.x), Frac(v.y), Frac(v.z), Frac(v.w));}

inline Flt FracS(Flt x) {return x-Trunc(x);} // (-1..1) (sign preserving)
inline Dbl FracS(Dbl x) {return x-Trunc(x);} // (-1..1) (sign preserving)

inline Flt Frac (Flt x, Flt range) {return Frac (x/range)*range;} // [     0..range)
inline Dbl Frac (Dbl x, Dbl range) {return Frac (x/range)*range;} // [     0..range)
inline Flt FracS(Flt x, Flt range) {return FracS(x/range)*range;} // (-range..range) (sign preserving)
inline Dbl FracS(Dbl x, Dbl range) {return FracS(x/range)*range;} // (-range..range) (sign preserving)

// align
inline Flt AlignTrunc(Flt x, Flt align) {return Trunc(x/align)*align;} // align 'x' to nearest multiple of 'align' using truncation
inline Dbl AlignTrunc(Dbl x, Dbl align) {return Trunc(x/align)*align;} // align 'x' to nearest multiple of 'align' using truncation
inline Flt AlignRound(Flt x, Flt align) {return Round(x/align)*align;} // align 'x' to nearest multiple of 'align' using rounding
inline Dbl AlignRound(Dbl x, Dbl align) {return Round(x/align)*align;} // align 'x' to nearest multiple of 'align' using rounding
inline Flt AlignFloor(Flt x, Flt align) {return Floor(x/align)*align;} // align 'x' to nearest multiple of 'align' using floor
inline Dbl AlignFloor(Dbl x, Dbl align) {return Floor(x/align)*align;} // align 'x' to nearest multiple of 'align' using floor
inline Flt AlignCeil (Flt x, Flt align) {return Ceil (x/align)*align;} // align 'x' to nearest multiple of 'align' using ceil
inline Dbl AlignCeil (Dbl x, Dbl align) {return Ceil (x/align)*align;} // align 'x' to nearest multiple of 'align' using ceil
/******************************************************************************/
// FUNCTIONS
/******************************************************************************/
inline Vec2 ::Vec2 (C VecD2 &v) {set(v.x, v.y          );}
inline Vec2 ::Vec2 (C VecI2 &v) {set(v.x, v.y          );}
inline VecD2::VecD2(C Vec2  &v) {set(v.x, v.y          );}
inline VecD2::VecD2(C VecI2 &v) {set(v.x, v.y          );}
inline Vec  ::Vec  (C VecD  &v) {set(v.x, v.y, v.z     );}
inline Vec  ::Vec  (C VecI  &v) {set(v.x, v.y, v.z     );}
inline VecD ::VecD (C Vec   &v) {set(v.x, v.y, v.z     );}
inline VecD ::VecD (C VecI  &v) {set(v.x, v.y, v.z     );}
inline Vec4 ::Vec4 (C VecD4 &v) {set(v.x, v.y, v.z, v.w);}
inline Vec4 ::Vec4 (C VecI4 &v) {set(v.x, v.y, v.z, v.w);}
inline Vec4 ::Vec4 (C VecB4 &v) {set(v.x, v.y, v.z, v.w);}
inline VecD4::VecD4(C Vec4  &v) {set(v.x, v.y, v.z, v.w);}

inline Vec  Vec2 :: xy0()C {return Vec (x, y, 0);}
inline Vec  Vec2 :: x0y()C {return Vec (x, 0, y);}
inline Vec  Vec2 ::_0xy()C {return Vec (0, x, y);}
inline Vec  Vec2 ::_0yx()C {return Vec (0, y, x);}
inline VecD VecD2:: xy0()C {return VecD(x, y, 0);}
inline VecD VecD2:: x0y()C {return VecD(x, 0, y);}
inline VecD VecD2::_0xy()C {return VecD(0, x, y);}
inline VecD VecD2::_0yx()C {return VecD(0, y, x);}
inline VecI VecI2:: xy0()C {return VecI(x, y, 0);}
inline VecI VecI2:: x0y()C {return VecI(x, 0, y);}
inline VecI VecI2::_0xy()C {return VecI(0, x, y);}
inline VecI VecI2::_0yx()C {return VecI(0, y, x);}

// minimum & maximum
inline Vec2  Min(C Vec2  &a, C Vec2  &b) {return Vec2 (Min(a.x,b.x), Min(a.y,b.y)                            );}
inline VecI2 Min(C VecI2 &a, C VecI2 &b) {return VecI2(Min(a.x,b.x), Min(a.y,b.y)                            );}
inline Vec2  Max(C Vec2  &a, C Vec2  &b) {return Vec2 (Max(a.x,b.x), Max(a.y,b.y)                            );}
inline VecI2 Max(C VecI2 &a, C VecI2 &b) {return VecI2(Max(a.x,b.x), Max(a.y,b.y)                            );}
inline Vec   Min(C Vec   &a, C Vec   &b) {return Vec  (Min(a.x,b.x), Min(a.y,b.y), Min(a.z,b.z)              );}
inline VecI  Min(C VecI  &a, C VecI  &b) {return VecI (Min(a.x,b.x), Min(a.y,b.y), Min(a.z,b.z)              );}
inline Vec   Max(C Vec   &a, C Vec   &b) {return Vec  (Max(a.x,b.x), Max(a.y,b.y), Max(a.z,b.z)              );}
inline VecI  Max(C VecI  &a, C VecI  &b) {return VecI (Max(a.x,b.x), Max(a.y,b.y), Max(a.z,b.z)              );}
inline Vec4  Min(C Vec4  &a, C Vec4  &b) {return Vec4 (Min(a.x,b.x), Min(a.y,b.y), Min(a.z,b.z), Min(a.w,b.w));}
inline VecI4 Min(C VecI4 &a, C VecI4 &b) {return VecI4(Min(a.x,b.x), Min(a.y,b.y), Min(a.z,b.z), Min(a.w,b.w));}
inline Vec4  Max(C Vec4  &a, C Vec4  &b) {return Vec4 (Max(a.x,b.x), Max(a.y,b.y), Max(a.z,b.z), Max(a.w,b.w));}
inline VecI4 Max(C VecI4 &a, C VecI4 &b) {return VecI4(Max(a.x,b.x), Max(a.y,b.y), Max(a.z,b.z), Max(a.w,b.w));}
       VecB4 Min(C VecB4 &a, C VecB4 &b);
       VecB4 Max(C VecB4 &a, C VecB4 &b);
       VecB4 Min(C VecB4 &a, C VecB4 &b, C VecB4 &c);
       VecB4 Max(C VecB4 &a, C VecB4 &b, C VecB4 &c);
       VecB4 Min(C VecB4 &a, C VecB4 &b, C VecB4 &c, C VecB4 &d);
       VecB4 Max(C VecB4 &a, C VecB4 &b, C VecB4 &c, C VecB4 &d);

// average
inline Vec2  Avg(C Vec2  &a, C Vec2  &b                        ) {return (a+b    )*0.5f ;}
inline VecD2 Avg(C VecD2 &a, C VecD2 &b                        ) {return (a+b    )*0.5  ;}
inline Vec   Avg(C Vec   &a, C Vec   &b                        ) {return (a+b    )*0.5f ;}
inline VecD  Avg(C VecD  &a, C VecD  &b                        ) {return (a+b    )*0.5  ;}
inline Vec4  Avg(C Vec4  &a, C Vec4  &b                        ) {return (a+b    )*0.5f ;}
inline VecD4 Avg(C VecD4 &a, C VecD4 &b                        ) {return (a+b    )*0.5  ;}
inline Vec2  Avg(C Vec2  &a, C Vec2  &b, C Vec2  &c            ) {return (a+b+c  )/3.0f ;}
inline VecD2 Avg(C VecD2 &a, C VecD2 &b, C VecD2 &c            ) {return (a+b+c  )/3.0  ;}
inline Vec   Avg(C Vec   &a, C Vec   &b, C Vec   &c            ) {return (a+b+c  )/3.0f ;}
inline VecD  Avg(C VecD  &a, C VecD  &b, C VecD  &c            ) {return (a+b+c  )/3.0  ;}
inline Vec2  Avg(C Vec2  &a, C Vec2  &b, C Vec2  &c, C Vec2  &d) {return (a+b+c+d)*0.25f;}
inline VecD2 Avg(C VecD2 &a, C VecD2 &b, C VecD2 &c, C VecD2 &d) {return (a+b+c+d)*0.25 ;}
inline Vec   Avg(C Vec   &a, C Vec   &b, C Vec   &c, C Vec   &d) {return (a+b+c+d)*0.25f;}
inline VecD  Avg(C VecD  &a, C VecD  &b, C VecD  &c, C VecD  &d) {return (a+b+c+d)*0.25 ;}

VecB4 AvgI(C VecB4 &a, C VecB4 &b                        );
VecB4 AvgI(C VecB4 &a, C VecB4 &b, C VecB4 &c            );
VecB4 AvgI(C VecB4 &a, C VecB4 &b, C VecB4 &c, C VecB4 &d);

VecI2 AvgI(C VecI2 &a, C VecI2 &b);
VecI  AvgI(C VecI  &a, C VecI  &b);
VecI4 AvgI(C VecI4 &a, C VecI4 &b);
Vec2  AvgF(C VecI2 &a, C VecI2 &b);
Vec   AvgF(C VecI  &a, C VecI  &b);
Vec4  AvgF(C VecI4 &a, C VecI4 &b);

// distance between 2 points
Flt Dist(C Vec2  &a, C Vec2  &b);
Dbl Dist(C VecD2 &a, C VecD2 &b);
Flt Dist(C VecI2 &a, C VecI2 &b);
Flt Dist(C Vec   &a, C Vec   &b);
Dbl Dist(C VecD  &a, C VecD  &b);
Flt Dist(C VecI  &a, C VecI  &b);

// squared distance between 2 points
Flt Dist2(C Vec2  &a, C Vec2  &b);
Dbl Dist2(C VecD2 &a, C VecD2 &b);
Int Dist2(C VecI2 &a, C VecI2 &b);
Flt Dist2(C Vec   &a, C Vec   &b);
Dbl Dist2(C VecD  &a, C VecD  &b);
Int Dist2(C VecI  &a, C VecI  &b);
Flt Dist2(C Vec4  &a, C Vec4  &b);

// dot product
inline Flt Dot(C Vec2  &a, C Vec2  &b) {return a.x*b.x + a.y*b.y                    ;}
inline Dbl Dot(C VecD2 &a, C VecD2 &b) {return a.x*b.x + a.y*b.y                    ;}
inline Flt Dot(C Vec   &a, C Vec   &b) {return a.x*b.x + a.y*b.y + a.z*b.z          ;}
inline Dbl Dot(C VecD  &a, C VecD  &b) {return a.x*b.x + a.y*b.y + a.z*b.z          ;}
inline Flt Dot(C Vec4  &a, C Vec4  &b) {return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;}
inline Dbl Dot(C VecD4 &a, C VecD4 &b) {return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;}

// cross product
Flt Cross(C Vec2  &a, C Vec2  &b);
Dbl Cross(C VecD2 &a, C VecD2 &b);

// cross product
Vec  Cross(C Vec  &a, C Vec  &b);
VecD Cross(C VecD &a, C VecD &b);

// cross product normalized
Vec  CrossN(C Vec  &a, C Vec  &b);
VecD CrossN(C VecD &a, C VecD &b);

// perpendicular vector
Vec2  Perp(C Vec2  &v);
VecD2 Perp(C VecD2 &v);
VecI2 Perp(C VecI2 &v);
Vec   Perp(C Vec   &v);
VecD  Perp(C VecD  &v);

// perpendicular vector normalized
Vec2  PerpN(C Vec2  &v);
VecD2 PerpN(C VecD2 &v);
Vec   PerpN(C Vec   &v);
VecD  PerpN(C VecD  &v);

// reflect vector (result is on the same side of the plane)
Vec2  Reflect(C Vec2  &vec,                 C Vec2  &nrm);
VecD2 Reflect(C VecD2 &vec,                 C VecD2 &nrm);
Vec   Reflect(C Vec   &vec,                 C Vec   &nrm);
VecD  Reflect(C VecD  &vec,                 C VecD  &nrm);
Vec2  Reflect(C Vec2  &vec, C Vec2  &plane, C Vec2  &nrm);
VecD2 Reflect(C VecD2 &vec, C VecD2 &plane, C VecD2 &nrm);
Vec   Reflect(C Vec   &vec, C Vec   &plane, C Vec   &nrm);
VecD  Reflect(C VecD  &vec, C VecD  &plane, C VecD  &nrm);

// mirror vector (result is on the other side of the plane)
Vec2  Mirror(C Vec2  &vec,                 C Vec2  &nrm);
VecD2 Mirror(C VecD2 &vec,                 C VecD2 &nrm);
Vec   Mirror(C Vec   &vec,                 C Vec   &nrm);
VecD  Mirror(C VecD  &vec,                 C VecD  &nrm);
Vec2  Mirror(C Vec2  &vec, C Vec2  &plane, C Vec2  &nrm);
VecD2 Mirror(C VecD2 &vec, C VecD2 &plane, C VecD2 &nrm);
Vec   Mirror(C Vec   &vec, C Vec   &plane, C Vec   &nrm);
VecD  Mirror(C VecD  &vec, C VecD  &plane, C VecD  &nrm);

// if equal (epsilon=EPS)
Bool Equal(  Flt   r0,   Flt   r1);
Bool Equal(C Vec2 &v0, C Vec2 &v1);
Bool Equal(C Vec  &v0, C Vec  &v1);
Bool Equal(C Vec4 &v0, C Vec4 &v1);

// if equal (epsilon=EPSD)
Bool Equal(  Dbl    r0,   Dbl    r1);
Bool Equal(C VecD2 &v0, C VecD2 &v1);
Bool Equal(C VecD  &v0, C VecD  &v1);
Bool Equal(C VecD4 &v0, C VecD4 &v1);

// if equal (with custom epsilon)
Bool Equal(  Flt    r0,   Flt    r1, Flt epsilon);
Bool Equal(  Dbl    r0,   Dbl    r1, Dbl epsilon);
Bool Equal(C Vec2  &v0, C Vec2  &v1, Flt epsilon);
Bool Equal(C VecD2 &v0, C VecD2 &v1, Dbl epsilon);
Bool Equal(C Vec   &v0, C Vec   &v1, Flt epsilon);
Bool Equal(C VecD  &v0, C VecD  &v1, Dbl epsilon);
Bool Equal(C Vec4  &v0, C Vec4  &v1, Flt epsilon);
Bool Equal(C VecD4 &v0, C VecD4 &v1, Dbl epsilon);

// compare
Int Compare(C Vec2  &v0, C Vec2  &v1);
Int Compare(C VecD2 &v0, C VecD2 &v1);
Int Compare(C Vec   &v0, C Vec   &v1);
Int Compare(C VecD  &v0, C VecD  &v1);
Int Compare(C Vec4  &v0, C Vec4  &v1);
Int Compare(C VecD4 &v0, C VecD4 &v1);
Int Compare(C VecI2 &v0, C VecI2 &v1);
Int Compare(C VecI  &v0, C VecI  &v1);
Int Compare(C VecI4 &v0, C VecI4 &v1);
Int Compare(C VecB4 &v0, C VecB4 &v1);
Int Compare(C Color &c0, C Color &c1);

// normalize array of vectors
void Normalize(Vec2  *v, Int num);
void Normalize(VecD2 *v, Int num);
void Normalize(Vec   *v, Int num);
void Normalize(VecD  *v, Int num);

// transform vectors by matrix
void Transform(Vec2 *v, C Matrix3 &m, Int num);
void Transform(Vec2 *v, C Matrix  &m, Int num);
void Transform(Vec  *v, C Matrix3 &m, Int num);
void Transform(Vec  *v, C Matrix  &m, Int num);

// change sign of vectors
void Chs(Vec2  *v, Int num);
void Chs(VecD2 *v, Int num);
void Chs(Vec   *v, Int num);
void Chs(VecD  *v, Int num);

// change sign of X component in vectors
void ChsX(Vec2 *v, Int num);
void ChsX(Vec  *v, Int num);

// change sign of Y component in vectors
void ChsY(Vec2 *v, Int num);
void ChsY(Vec  *v, Int num);

// change sign of Z component in vectors
void ChsZ(Vec  *v, Int num);

// reverse components order in vectors
void Reverse(VecI2 *v, Int num);
void Reverse(VecI  *v, Int num);
void Reverse(VecI4 *v, Int num);

// get minimum and maximum from array of vectors
Bool MinMax(C Vec2  *v, Int num, Vec2  &min, Vec2  &max);
Bool MinMax(C VecD2 *v, Int num, VecD2 &min, VecD2 &max);
Bool MinMax(C Vec   *v, Int num, Vec   &min, Vec   &max);
Bool MinMax(C VecD  *v, Int num, VecD  &min, VecD  &max);
Bool MinMax(C Vec4  *v, Int num, Vec4  &min, Vec4  &max);
Bool MinMax(C VecD4 *v, Int num, VecD4 &min, VecD4 &max);

       CChar*    DirToText(DIR_ENUM dir);                 // return direction in text format, "Right", "Left", "Up", "Down", "Forward", "Back"
inline UInt      DirToFlag(DIR_ENUM dir) {return 1<<dir;} // convert DIR_ENUM to DIR_FLAG
       AXIS_TYPE DirToAxis(DIR_ENUM dir);                 // convert DIR_ENUM to AXIS_TYPE
/******************************************************************************/
inline Int Elms(C Vec2  &v) {return 2;}
inline Int Elms(C VecD2 &v) {return 2;}
inline Int Elms(C VecI2 &v) {return 2;}

inline Int Elms(C Vec   &v) {return 3;}
inline Int Elms(C VecD  &v) {return 3;}
inline Int Elms(C VecI  &v) {return 3;}

inline Int Elms(C Vec4  &v) {return 4;}
inline Int Elms(C VecD4 &v) {return 4;}
inline Int Elms(C VecI4 &v) {return 4;}
inline Int Elms(C VecB4 &v) {return 4;}
/******************************************************************************/

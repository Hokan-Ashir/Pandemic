/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Random' to generate random values.

/******************************************************************************/
struct Randomizer // Randomizer is multi-threaded safe
{
   UInt seed[3]; // current seed value, this may be freely modified, it affects generated random values

   void randomize(); // randomize seed

   UInt operator()(            ); // return random UInt in range 0..0xFFFFFFFF
   UInt operator()(UInt n      ); // return random UInt in range 0..n-1
   Int  operator()(Int f, Int t); // return random Int  in range f..t
   Bool b         (            ); // return random Bool (false/true)
   Flt  f         (            ); // return random Flt  in range 0..1
   Flt  f         (Flt x       ); // return random Flt  in range 0..x
   Flt  f         (Flt f, Flt t); // return random Flt  in range f..t
   Vec2 vec2      (            ); // return random Vec2 in range (0,0)..(1,1)
   Vec2 vec2      (Flt x       ); // return random Vec2 in range (0,0)..(x,x)
   Vec2 vec2      (Flt f, Flt t); // return random Vec2 in range (f,f)..(t,t)
   Vec  vec       (            ); // return random Vec  in range (0,0,0)..(1,1,1)
   Vec  vec       (Flt x       ); // return random Vec  in range (0,0,0)..(x,x,x)
   Vec  vec       (Flt f, Flt t); // return random Vec  in range (f,f,f)..(t,t,t)

   Vec  dir(C Vec &dir, Flt a       ); // return random direction based on 'dir', and 0..a angle difference, 'dir' must be normalized
   Vec  dir(C Vec &dir, Flt f, Flt t); // return random direction based on 'dir', and f..t angle difference, 'dir' must be normalized

   Vec  sphere(C Ball &ball, Flt f, Flt t); // return random point on sphere surface, with f..t vertical angle limit, (f=-1..t, t=f..1)

   Vec  operator()(C Edge    &edge                     ); // return random point on        edge
   Vec2 operator()(C Tri2    &tri    , Bool inside=true); // return random point on/inside triangle
   Vec  operator()(C Tri     &tri    , Bool inside=true); // return random point on/inside triangle
   Vec2 operator()(C Quad2   &quad   , Bool inside=true); // return random point on/inside quad
   Vec  operator()(C Quad    &quad   , Bool inside=true); // return random point on/inside quad
   Vec2 operator()(C Rect    &rect   , Bool inside=true); // return random point on/inside rectangle
   Vec  operator()(C Box     &box    , Bool inside=true); // return random point on/inside box
   Vec  operator()(C OBox    &obox   , Bool inside=true); // return random point on/inside oriented box
   Vec2 operator()(C Circle  &circle , Bool inside=true); // return random point on/inside circle
   Vec  operator()(C Ball    &ball   , Bool inside=true); // return random point on/inside ball
   Vec  operator()(C Capsule &capsule, Bool inside=true); // return random point on/inside capsule
   Vec  operator()(C Tube    &tube   , Bool inside=true); // return random point on/inside tube
   Vec  operator()(C Torus   &torus  , Bool inside=true); // return random point on/inside tube
   Vec  operator()(C Cone    &cone   , Bool inside=true); // return random point on/inside tube
   Vec  operator()(C Pyramid &pyramid, Bool inside=true); // return random point on/inside tube
   Vec  operator()(C Shape   &shape  , Bool inside=true); // return random point on/inside shape

   Vec  operator()(MeshBase   &mshb, AnimatedSkeleton *anim_skel=NULL); // return random point on MeshBase   surface (if 'anim_skel' is not NULL then mesh is assumed to be animated by the Skeleton)
   Vec  operator()(MeshRender &mshr, AnimatedSkeleton *anim_skel=NULL); // return random point on MeshRender surface (if 'anim_skel' is not NULL then mesh is assumed to be animated by the Skeleton)
   Vec  operator()(MeshPart   &part, AnimatedSkeleton *anim_skel=NULL); // return random point on MeshPart   surface (if 'anim_skel' is not NULL then mesh is assumed to be animated by the Skeleton)
   Vec  operator()(Mesh       &mesh, AnimatedSkeleton *anim_skel=NULL); // return random point on Mesh       surface (if 'anim_skel' is not NULL then mesh is assumed to be animated by the Skeleton)

   // custom probability alignment
   UInt align (UInt n      , Flt (&func)(Flt x)); // return random UInt in range 0..n-1 with probability aligned based on 'func' function
   Int  align (Int f, Int t, Flt (&func)(Flt x)); // return random Int  in range f..t   with probability aligned based on 'func' function
   Flt  alignF(              Flt (&func)(Flt x)); // return random Flt  in range 0..1   with probability aligned based on 'func' function
   Flt  alignF(Flt x       , Flt (&func)(Flt x)); // return random Flt  in range 0..x   with probability aligned based on 'func' function
   Flt  alignF(Flt f, Flt t, Flt (&func)(Flt x)); // return random Flt  in range f..t   with probability aligned based on 'func' function

   UInt align (UInt n      , Flt (&func)(Flt x, Flt y), Flt y); // return random UInt in range 0..n-1 with probability aligned based on 'func' function
   Int  align (Int f, Int t, Flt (&func)(Flt x, Flt y), Flt y); // return random Int  in range f..t   with probability aligned based on 'func' function
   Flt  alignF(              Flt (&func)(Flt x, Flt y), Flt y); // return random Flt  in range 0..1   with probability aligned based on 'func' function
   Flt  alignF(Flt x       , Flt (&func)(Flt x, Flt y), Flt y); // return random Flt  in range 0..x   with probability aligned based on 'func' function
   Flt  alignF(Flt f, Flt t, Flt (&func)(Flt x, Flt y), Flt y); // return random Flt  in range f..t   with probability aligned based on 'func' function

   UInt alignPow (UInt n      , Flt pow); // return random UInt in range 0..n-1 with probability aligned to "0" (for pow>1 towards Inf) or to "n-1" (for pow<1 towards 0)
   Int  alignPow (Int f, Int t, Flt pow); // return random Int  in range f..t   with probability aligned to "f" (for pow>1 towards Inf) or to "t"   (for pow<1 towards 0)
   Flt  alignPowF(              Flt pow); // return random Flt  in range 0..1   with probability aligned to "0" (for pow>1 towards Inf) or to "1"   (for pow<1 towards 0)
   Flt  alignPowF(Flt x       , Flt pow); // return random Flt  in range 0..x   with probability aligned to "0" (for pow>1 towards Inf) or to "x"   (for pow<1 towards 0)
   Flt  alignPowF(Flt f, Flt t, Flt pow); // return random Flt  in range f..t   with probability aligned to "f" (for pow>1 towards Inf) or to "t"   (for pow<1 towards 0)

   Randomizer() {}
   Randomizer(UInt s0, UInt s1, UInt s2) {seed[0]=s0; seed[1]=s1; seed[2]=s2;}
}extern
   Random; // Main Randomizer
/******************************************************************************/
inline Flt RandomF(            ) {return Random.f(    );} // return random Flt in range 0..1
inline Flt RandomF(Flt x       ) {return Random.f(x   );} // return random Flt in range 0..x
inline Flt RandomF(Flt f, Flt t) {return Random.f(f, t);} // return random Flt in range f..t
/******************************************************************************/

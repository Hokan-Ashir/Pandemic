/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Circle'  to handle circle shapes, Flt type
   Use 'CircleD' to handle circle shapes, Dbl type

/******************************************************************************/
struct Circle // Circle Shape
{
   Flt  r  ; // radius
   Vec2 pos; // center position

   // set
   Circle& set(Flt r, C Vec2 &pos=Vec2(0,0)) {T.r=r; T.pos=pos      ; return T;}
   Circle& set(Flt r, Flt x, Flt y         ) {T.r=r; T.pos.set(x, y); return T;}

   // get
   Flt area     ()C {return PID *r*r;} // get surface area
   Flt perimeter()C {return PID2*r  ;} // get perimeter

   Str asText()C {return S+"Radius: "+r+", Pos: "+pos;} // get text description

   // transform
          Circle& operator+=(C Vec2   &v) {pos+=v     ;    return T;}
          Circle& operator-=(C Vec2   &v) {pos-=v     ;    return T;}
          Circle& operator+=(C Vec    &v) {pos+=v.v2();    return T;}
          Circle& operator-=(C Vec    &v) {pos-=v.v2();    return T;}
          Circle& operator+=(  Flt     f) {r  +=f;         return T;}
          Circle& operator-=(  Flt     f) {r  -=f;         return T;}
          Circle& operator*=(  Flt     f) {r  *=f; pos*=f; return T;}
          Circle& operator/=(  Flt     f) {r  /=f; pos/=f; return T;}
   friend Circle  operator+ (C Circle &circle, C Vec2 &v);
   friend Circle  operator- (C Circle &circle, C Vec2 &v);

   // operations
   Circle& extend(Flt e) {r+=e; return T;} // extend

   // draw
   void draw(C Color &color, Bool fill=true, Int resolution=-1)C;

   void drawPie(C Color &color, Flt r_start, Flt angle_start=0, Flt angle_range=PI2, Bool fill=true, Int resolution=-1)C; // draw pie, 'r_start'=radius at which start drawing (0..'r'), 'angle_start'=angle at which start drawing (0..PI2), 'angle_range'=angle range (0..PI2)

   Circle() {}
   Circle(Flt r, C Vec2 &pos=Vec2(0,0)) {set(r, pos );}
   Circle(Flt r, Flt x, Flt y         ) {set(r, x, y);}
};
/******************************************************************************/
struct CircleD // Circle Shape (double precision)
{
   Dbl   r  ; // radius
   VecD2 pos; // center

   // set
   CircleD& set(Dbl r, C VecD2 &pos=VecD2(0,0)) {T.r=r; T.pos=pos      ; return T;}
   CircleD& set(Dbl r, Dbl x, Dbl y           ) {T.r=r; T.pos.set(x, y); return T;}

   // get
   Dbl area     ()C {return PID *r*r;} // get surface area
   Dbl perimeter()C {return PID2*r  ;} // get perimeter

   CircleD() {}
   CircleD(Dbl r, C VecD2 &pos=VecD2(0,0)) {set(r, pos );}
   CircleD(Dbl r, Dbl x, Dbl y           ) {set(r, x, y);}
};
/******************************************************************************/
// distance
Flt Dist(C Vec2   &point, C Circle &circle); // distance between point     and a circle
Flt Dist(C Rect   &rect , C Circle &circle); // distance between rectangle and a circle
Flt Dist(C Circle &a    , C Circle &b     ); // distance between circle    and a circle

// cuts
Bool Cuts(C Vec2   &point, C Circle &circle); // if point     cuts circle
Bool Cuts(C Rect   &rect , C Circle &circle); // if rectangle cuts circle
Bool Cuts(C Circle &a    , C Circle &b     ); // if circle    cuts circle

// if straight line cuts circle, return number of contacts
Int CutsStrCircle(C Vec2 &point, C Vec2 &normal, C Circle &circle, Vec2 *contact_a=NULL, Vec2 *contact_b=NULL, Flt *width=NULL);

// if circle cuts circle, returns number of contacts
Int CutsCircleCircle(C Circle &a, C Circle &b, Vec2 *contact_a=NULL, Vec2 *contact_b=NULL, Flt *width=NULL);

// if moving point cuts through a static circle
Bool SweepPointCircle(C Vec2  &point, C Vec2  &move, C Circle  &circle, Flt *hit_frac=NULL, Vec2  *hit_normal=NULL);
Bool SweepPointCircle(C VecD2 &point, C VecD2 &move, C CircleD &circle, Dbl *hit_frac=NULL, VecD2 *hit_normal=NULL);

// if moving edge cuts through a static circle
Bool SweepEdgeCircle(C Edge2  &edge, C Vec2  &move, C Circle  &circle, Flt *hit_frac=NULL, Vec2  *hit_normal=NULL);
Bool SweepEdgeCircle(C EdgeD2 &edge, C VecD2 &move, C CircleD &circle, Dbl *hit_frac=NULL, VecD2 *hit_normal=NULL);

// if moving circle cuts through a static circle
Bool SweepCircleCircle(C Circle  &circle, C Vec2  &move, C Circle  &c2, Flt *hit_frac=NULL, Vec2  *hit_normal=NULL);
Bool SweepCircleCircle(C CircleD &circle, C VecD2 &move, C CircleD &c2, Dbl *hit_frac=NULL, VecD2 *hit_normal=NULL);

// if moving circle cuts through a static point
Bool SweepCirclePoint(C Circle  &circle, C Vec2  &move, C Vec2  &point, Flt *hit_frac=NULL, Vec2  *hit_normal=NULL);
Bool SweepCirclePoint(C CircleD &circle, C VecD2 &move, C VecD2 &point, Dbl *hit_frac=NULL, VecD2 *hit_normal=NULL);

// if moving circle cuts through a static edge
Bool SweepCircleEdge(C Circle  &circle, C Vec2  &move, C Edge2  &edge, Flt *hit_frac=NULL, Vec2  *hit_normal=NULL);
Bool SweepCircleEdge(C CircleD &circle, C VecD2 &move, C EdgeD2 &edge, Dbl *hit_frac=NULL, VecD2 *hit_normal=NULL);
/******************************************************************************/

/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Tube' to handle tube shapes.

/******************************************************************************/
struct Tube // Tube Shape
{
   Flt r  , // radius
       h  ; // height
   Vec pos, // center position
       up ; // up     direction

   Tube& set(Flt r, Flt h, C Vec &pos=VecZero, C Vec &up=Vec(0,1,0)) {T.r=r; T.h=h; T.pos=pos; T.up=up; return T;}

   // get
   Flt  area  ()C {return PID2*r  *(h+r)          ;} // get surface area
   Flt  volume()C {return PID *r*r* h             ;} // get volume
   Vec  pointU()C {return pos+up*(h*0.5f)         ;} // upper circle center point
   Vec  pointD()C {return pos-up*(h*0.5f)         ;} // lower circle center point
   Edge edge  ()C {return Edge(pointD(), pointU());} // get edge between lower and upper points

   Str asText()C {return S+"Radius: "+r+", Height: "+h+", Pos: "+pos+", Up: "+up;} // get text description

   // transform
          Tube& operator+=(C Vec     &v) {pos+=v; return T;}
          Tube& operator-=(C Vec     &v) {pos-=v; return T;}
          Tube& operator*=(  Flt      f);
          Tube& operator/=(  Flt      f);
          Tube& operator*=(C Vec     &v);
          Tube& operator/=(C Vec     &v);
          Tube& operator*=(C Matrix3 &m);
          Tube& operator*=(C Matrix  &m);
   friend Tube  operator+ (C Tube    &tube, C Vec     &v);
   friend Tube  operator- (C Tube    &tube, C Vec     &v);
   friend Tube  operator* (C Tube    &tube,   Flt      f);
   friend Tube  operator/ (C Tube    &tube,   Flt      f);
   friend Tube  operator* (C Tube    &tube, C Vec     &v);
   friend Tube  operator/ (C Tube    &tube, C Vec     &v);
   friend Tube  operator* (C Tube    &tube, C Matrix3 &m);
   friend Tube  operator* (C Tube    &tube, C Matrix  &m);

   // operations
   Tube& extend(Flt e) {r+=e; h+=e+e; return T;} // extend

   // draw
   void draw(C Color &color=WHITE, Bool fill=false, Int resolution=-1)C; // this relies on active object matrix which can be set using 'SetMatrix' function

   Tube() {}
   Tube(Flt r, Flt h, C Vec &pos=VecZero, C Vec &up=Vec(0,1,0)) {set(r, h, pos, up);}
};
/******************************************************************************/
// cuts
Bool Cuts(C Vec  &point, C Tube &tube); // if point cuts tube
Bool Cuts(C Edge &edge , C Tube &tube); // if edge  cuts tube

// sweep
Bool SweepPointTube(C Vec &point, C Vec &move, C Tube &tube, Flt *hit_frac=NULL, Vec *hit_normal=NULL); // if moving point cuts through a static tube
/******************************************************************************/

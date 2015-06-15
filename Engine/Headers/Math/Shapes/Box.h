/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Box'  to handle box          shapes, Flt type
   Use 'BoxD' to handle box          shapes, Dbl type
   Use 'BoxI' to handle box          shapes, Int type
   Use 'OBox' to handle oriented box shapes, Flt type (oriented box is a box which can be rotated)

/******************************************************************************/
struct Box // Box Shape
{
   Vec min, max;

   Box& zero(                                                                ) {min.zero(); max.zero(); return T;}
   Box& set (C Vec &min, C Vec &max                                          ) {T.min=min;  T.max=max;  return T;}
   Box& set (Flt min_x, Flt min_y, Flt min_z, Flt max_x, Flt max_y, Flt max_z) {min.set(min_x       , min_y       , min_z       ); max.set(max_x       , max_y       , max_z       ); return T;}
   Box& set (Flt r,               C Vec &pos=VecZero                         ) {min.set(pos.x-r     , pos.y-r     , pos.z-r     ); max.set(pos.x+r     , pos.y+r     , pos.z+r     ); return T;}
   Box& set (Flt w, Flt h, Flt d, C Vec &pos=VecZero                         ) {min.set(pos.x-w*0.5f, pos.y-h*0.5f, pos.z-d*0.5f); max.set(pos.x+w*0.5f, pos.y+h*0.5f, pos.z+d*0.5f); return T;}
   Box& setR(Flt w, Flt h, Flt d, C Vec &pos=VecZero                         ) {min.set(pos.x-w     , pos.y-h*0.5f, pos.z-d*0.5f); max.set(pos.x       , pos.y+h*0.5f, pos.z+d*0.5f); return T;} // set right
   Box& setL(Flt w, Flt h, Flt d, C Vec &pos=VecZero                         ) {min.set(pos.x       , pos.y-h*0.5f, pos.z-d*0.5f); max.set(pos.x+w     , pos.y+h*0.5f, pos.z+d*0.5f); return T;} // set left
   Box& setU(Flt w, Flt h, Flt d, C Vec &pos=VecZero                         ) {min.set(pos.x-w*0.5f, pos.y-h     , pos.z-d*0.5f); max.set(pos.x+w*0.5f, pos.y       , pos.z+d*0.5f); return T;} // set up
   Box& setD(Flt w, Flt h, Flt d, C Vec &pos=VecZero                         ) {min.set(pos.x-w*0.5f, pos.y       , pos.z-d*0.5f); max.set(pos.x+w*0.5f, pos.y+h     , pos.z+d*0.5f); return T;} // set down
   Box& setF(Flt w, Flt h, Flt d, C Vec &pos=VecZero                         ) {min.set(pos.x-w*0.5f, pos.y-h*0.5f, pos.z-d     ); max.set(pos.x+w*0.5f, pos.y+h*0.5f, pos.z       ); return T;} // set forward
   Box& setB(Flt w, Flt h, Flt d, C Vec &pos=VecZero                         ) {min.set(pos.x-w*0.5f, pos.y-h*0.5f, pos.z       ); max.set(pos.x+w*0.5f, pos.y+h*0.5f, pos.z+d     ); return T;} // set back

          Box& operator+=(C Vec     &v) {min+=v; max+=v; return T;}
          Box& operator-=(C Vec     &v) {min-=v; max-=v; return T;}
          Box& operator*=(  Flt      f) {min*=f; max*=f; return T;}
          Box& operator/=(  Flt      f) {min/=f; max/=f; return T;}
          Box& operator*=(C Vec     &v) {min*=v; max*=v; return T;}
          Box& operator/=(C Vec     &v) {min/=v; max/=v; return T;}
          Box& operator*=(C Matrix3 &m); // transform by matrix
          Box& operator*=(C Matrix  &m); // transform by matrix
          Box& operator|=(C Vec     &v) {return include(v);}
          Box& operator|=(C Box     &b) {return include(b);}
          Box& operator&=(C Box     &b); // intersect
   friend Box  operator| (C Box     &box, C Vec     &v); // union
   friend Box  operator| (C Box     &box, C Box     &b); // union
   friend Box  operator& (C Box     &box, C Box     &b); // intersection
   friend Box  operator+ (C Box     &box, C Vec     &v);
   friend Box  operator- (C Box     &box, C Vec     &v);
   friend Box  operator* (C Box     &box,   Flt      f);
   friend Box  operator/ (C Box     &box,   Flt      f);
   friend Box  operator* (C Box     &box, C Vec     &v);
   friend Box  operator/ (C Box     &box, C Vec     &v);
   friend Box  operator* (C Box     &box, C Matrix3 &m);
   friend Box  operator* (C Box     &box, C Matrix  &m);

   // get
   Flt  w        ()C {return  max.x-min.x;} // get width
   Flt  h        ()C {return  max.y-min.y;} // get height
   Flt  d        ()C {return  max.z-min.z;} // get depth
   Vec  size     ()C {return  max  -min  ;} // get size
   Flt  centerX  ()C {return  Avg(min.x, max.x);} // get center x
   Flt  centerY  ()C {return  Avg(min.y, max.y);} // get center y
   Flt  centerZ  ()C {return  Avg(min.z, max.z);} // get center z
   Vec  center   ()C {return  Vec(centerX(), centerY(), centerZ());} // get center
   Vec  cornerLDB()C {return  Vec(  min.x  ,   min.y  ,   min.z  );} // get left  down back  corner
   Vec  cornerLDF()C {return  Vec(  min.x  ,   min.y  ,   max.z  );} // get left  down front corner
   Vec  cornerLUB()C {return  Vec(  min.x  ,   max.y  ,   min.z  );} // get left  up   back  corner
   Vec  cornerLUF()C {return  Vec(  min.x  ,   max.y  ,   max.z  );} // get left  up   front corner
   Vec  cornerRDB()C {return  Vec(  max.x  ,   min.y  ,   min.z  );} // get right down back  corner
   Vec  cornerRDF()C {return  Vec(  max.x  ,   min.y  ,   max.z  );} // get right down front corner
   Vec  cornerRUB()C {return  Vec(  max.x  ,   max.y  ,   min.z  );} // get right up   back  corner
   Vec  cornerRUF()C {return  Vec(  max.x  ,   max.y  ,   max.z  );} // get right up   front corner
   Vec  left     ()C {return  Vec(  min.x  , centerY(), centerZ());} // get left    point
   Vec  right    ()C {return  Vec(  max.x  , centerY(), centerZ());} // get right   point
   Vec  down     ()C {return  Vec(centerX(),   min.y  , centerZ());} // get down    point
   Vec  up       ()C {return  Vec(centerX(),   max.y  , centerZ());} // get up      point
   Vec  back     ()C {return  Vec(centerX(), centerY(),   min.z  );} // get back    point
   Vec  forward  ()C {return  Vec(centerX(), centerY(),   max.z  );} // get forward point
   Flt  area     ()C;                                              // get surface area
   Flt  volume   ()C {return w()*h()*d() ;}                        // get volume
   Bool validX   ()C {return min.x<=max.x;}                        // if has valid x's
   Bool validY   ()C {return min.y<=max.y;}                        // if has valid y's
   Bool validZ   ()C {return min.z<=max.z;}                        // if has valid z's
   Bool valid    ()C {return validX() && validY() && validZ();}    // if is  valid
   Rect xz       ()C {return Rect(min.x, min.z, max.x, max.z);}    // get rectangle in XZ plane

   Flt lerpX(Flt s              )C {return Lerp(min.x, max.x, s)            ;} // lerp between min.x and max.x
   Flt lerpY(Flt s              )C {return Lerp(min.y, max.y, s)            ;} // lerp between min.y and max.y
   Flt lerpZ(Flt s              )C {return Lerp(min.z, max.z, s)            ;} // lerp between min.z and max.z
   Vec lerp (Flt x, Flt y, Flt z)C {return Vec(lerpX(x), lerpY(y), lerpZ(z));} // lerp inside  box

   Str asText()C {return S+"Min: "+min+", Max: "+max;} // get text description

   // set
   Box& setX(Flt x           ) {T.min.x=x  ; T.max.x=x  ; return T;}
   Box& setY(Flt y           ) {T.min.y=y  ; T.max.y=y  ; return T;}
   Box& setZ(Flt z           ) {T.min.z=z  ; T.max.z=z  ; return T;}
   Box& setX(Flt min, Flt max) {T.min.x=min; T.max.x=max; return T;}
   Box& setY(Flt min, Flt max) {T.min.y=min; T.max.y=max; return T;}
   Box& setZ(Flt min, Flt max) {T.min.z=min; T.max.z=max; return T;}

   // operations
   Box& extendX  (  Flt  e); // extend x
   Box& extendY  (  Flt  e); // extend y
   Box& extendZ  (  Flt  e); // extend z
   Box& extend   (  Flt  e); // extend by float
   Box& extend   (C Vec &e); // extend by vector
   Box& includeX (  Flt  x); // extend box to include x
   Box& includeY (  Flt  y); // extend box to include y
   Box& includeZ (  Flt  z); // extend box to include z
   Box& include  (C Vec &v); // extend box to include vector
   Box& include  (C Box &b); // extend box to include box
   Box& from     (C Vec &a    , C Vec &b  ) ; // set box from 2 points
   Bool from     (C Vec *point, Int points) ; // set box from an array of points, false on fail (if there are no points)
   void toCorners(  Vec (&v)[8]           )C; // convert to 8 corner points

   // draw
   void draw(C Color &color=WHITE, Bool fill=false)C; // this relies on active object matrix which can be set using 'SetMatrix' function

   Box() {}
   Box(C Vec      &vec                                                 ) {min=max=vec                                  ;}
   Box(C Vec      &min, C Vec &max                                     ) {set(min, max                                );}
   Box(Flt min_x, Flt min_y, Flt min_z, Flt max_x, Flt max_y, Flt max_z) {set(min_x, min_y, min_z, max_x, max_y, max_z);}
   Box(  Flt      r,               C Vec &pos=VecZero                  ) {set(r,       pos                            );}
   Box(  Flt      w, Flt h, Flt d, C Vec &pos=VecZero                  ) {set(w, h, d, pos                            );}
   Box(C Rect     &rect    );
   Box(C Circle   &circle  );
   Box(C Edge     &edge    );
   Box(C Tri      &tri     );
   Box(C Quad     &quad    );
   Box(C BoxD     &box     );
   Box(C BoxI     &box     );
   Box(C OBox     &obox    );
   Box(C Ball     &ball    );
   Box(C Capsule  &capsule );
   Box(C Tube     &tube    );
   Box(C Torus    &torus   );
   Box(C Cone     &cone    );
   Box(C Pyramid  &pyramid );
   Box(C Shape    &shape   );
   Box(C MeshBase &mesh    );
   Box(C MeshPart &mesh    );
   Box(C Skeleton &skeleton);
};
/******************************************************************************/
// box with helper constructor
struct Box_R : Box{   Box_R(Flt w, Flt h, Flt d, C Vec &pos=VecZero) {setR(w, h, d, pos);}   }; // right
struct Box_L : Box{   Box_L(Flt w, Flt h, Flt d, C Vec &pos=VecZero) {setL(w, h, d, pos);}   }; // left
struct Box_U : Box{   Box_U(Flt w, Flt h, Flt d, C Vec &pos=VecZero) {setU(w, h, d, pos);}   }; // up
struct Box_D : Box{   Box_D(Flt w, Flt h, Flt d, C Vec &pos=VecZero) {setD(w, h, d, pos);}   }; // down
struct Box_F : Box{   Box_F(Flt w, Flt h, Flt d, C Vec &pos=VecZero) {setF(w, h, d, pos);}   }; // forward
struct Box_B : Box{   Box_B(Flt w, Flt h, Flt d, C Vec &pos=VecZero) {setB(w, h, d, pos);}   }; // back
/******************************************************************************/
struct BoxD // Box Shape (double precision)
{
   VecD min, max;

   BoxD& zero() {min.zero(); max.zero(); return T;}

          BoxD& operator|=(C VecD &v) {return include(v);}
          BoxD& operator|=(C BoxD &b) {return include(b);}
          BoxD& operator&=(C BoxD &b); // intersect
   friend BoxD  operator| (C BoxD &box, C VecD &v); // union
   friend BoxD  operator| (C BoxD &box, C BoxD &b); // union
   friend BoxD  operator& (C BoxD &box, C BoxD &b); // intersection

   // get
   Dbl  w   ()C {return max.x-min.x;} // get width
   Dbl  h   ()C {return max.y-min.y;} // get height
   Dbl  d   ()C {return max.z-min.z;} // get depth
   VecD size()C {return max  -min  ;} // get size

   // operations
   BoxD& extendX (  Dbl   e); // extend x
   BoxD& extendY (  Dbl   e); // extend y
   BoxD& extendZ (  Dbl   e); // extend z
   BoxD& extend  (  Dbl   e); // extend by float
   BoxD& extend  (C VecD &e); // extend by vector
   BoxD& includeX(  Dbl   x); // extend box to include x
   BoxD& includeY(  Dbl   y); // extend box to include y
   BoxD& includeZ(  Dbl   z); // extend box to include z
   BoxD& include (C VecD &v); // extend box to include vector
   BoxD& include (C BoxD &b); // extend box to include box
   BoxD& from    (C VecD &a, C VecD &b); // set box from 2 points
   Bool  from    (C VecD *v,   Int   n); // set box from 'n' 'v' points, false on fail

   BoxD() {}
   BoxD(C EdgeD &edge);
   BoxD(C TriD  &tri );
   BoxD(C QuadD &quad);
   BoxD(C Box   &box );
};
/******************************************************************************/
struct BoxI // Box Shape (integer)
{
   VecI min, max;

   BoxI& zero(                                                                ) {min.zero(); max.zero(); return T;}
   BoxI& set (C VecI &min, C VecI &max                                        ) {T.min=min;  T.max=max;  return T;}
   BoxI& set (Int min_x, Int min_y, Int min_z, Int max_x, Int max_y, Int max_z) {min.set(min_x, min_y, min_z); max.set(max_x, max_y, max_z); return T;}

          BoxI& operator|=(C VecI &v) {return include(v);}
          BoxI& operator|=(C BoxI &b) {return include(b);}
          BoxI& operator&=(C BoxI &b); // intersect
   friend BoxI  operator| (C BoxI &box, C VecI &v); // union
   friend BoxI  operator| (C BoxI &box, C BoxI &b); // union
   friend BoxI  operator& (C BoxI &box, C BoxI &b); // intersection

   // get
   RectI xz()C {return RectI(min.x, min.z, max.x, max.z);} // get rectangle in XZ plane

   Flt  centerXI()C {return AvgI(min.x, max.x);} // get center x (Int)
   Flt  centerXF()C {return AvgF(min.x, max.x);} // get center x (Flt)
   Flt  centerYI()C {return AvgI(min.y, max.y);} // get center y (Int)
   Flt  centerYF()C {return AvgF(min.y, max.y);} // get center y (Flt)
   Flt  centerZI()C {return AvgI(min.z, max.z);} // get center z (Int)
   Flt  centerZF()C {return AvgF(min.z, max.z);} // get center z (Flt)
   VecI centerI ()C {return VecI(centerXI(), centerYI(), centerZI());} // get center (VecI)
   Vec  centerF ()C {return Vec (centerXF(), centerYF(), centerZF());} // get center (Vec )

   Str asText()C {return S+"Min: "+min+", Max: "+max;} // get text description

   // set
   BoxI& setX(Int x           ) {T.min.x=x  ; T.max.x=x  ; return T;}
   BoxI& setY(Int y           ) {T.min.y=y  ; T.max.y=y  ; return T;}
   BoxI& setZ(Int z           ) {T.min.z=z  ; T.max.z=z  ; return T;}
   BoxI& setX(Int min, Int max) {T.min.x=min; T.max.x=max; return T;}
   BoxI& setY(Int min, Int max) {T.min.y=min; T.max.y=max; return T;}
   BoxI& setZ(Int min, Int max) {T.min.z=min; T.max.z=max; return T;}

   // operations
   BoxI& extendX (  Int   e); // extend x
   BoxI& extendY (  Int   e); // extend y
   BoxI& extendZ (  Int   e); // extend z
   BoxI& extend  (  Int   e); // extend by float
   BoxI& extend  (C VecI &e); // extend by vector
   BoxI& includeX(  Int   x); // extend box to include x
   BoxI& includeY(  Int   y); // extend box to include y
   BoxI& includeZ(  Int   z); // extend box to include z
   BoxI& include (C VecI &v); // extend box to include vector
   BoxI& include (C BoxI &b); // extend box to include box

   BoxI() {}
   BoxI(C VecI &vec                                                     ) {min=max=vec                                  ;}
   BoxI(C VecI &min, C VecI &max                                        ) {set(min, max                                );}
   BoxI(Int min_x, Int min_y, Int min_z, Int max_x, Int max_y, Int max_z) {set(min_x, min_y, min_z, max_x, max_y, max_z);}
};
/******************************************************************************/
struct OBox // Oriented Box (Box with matrix transformation, can be rotated)
{
   Box    box   ;
   Matrix matrix; // must be normalized

          OBox& operator+=(C Vec     &v) {matrix.pos+=v; return T;}
          OBox& operator-=(C Vec     &v) {matrix.pos-=v; return T;}
          OBox& operator*=(  Flt      f);
          OBox& operator/=(  Flt      f);
          OBox& operator*=(C Vec     &v);
          OBox& operator/=(C Vec     &v);
          OBox& operator*=(C Matrix3 &m) {return mul(m);}
          OBox& operator*=(C Matrix  &m) {return mul(m);}
          OBox& operator/=(C Matrix3 &m) {return div(m);}
          OBox& operator/=(C Matrix  &m) {return div(m);}
   friend OBox  operator+ (C OBox &obox, C Vec     &v);
   friend OBox  operator- (C OBox &obox, C Vec     &v);
   friend OBox  operator* (C OBox &obox,   Flt      f);
   friend OBox  operator/ (C OBox &obox,   Flt      f);
   friend OBox  operator* (C OBox &obox, C Vec     &v);
   friend OBox  operator/ (C OBox &obox, C Vec     &v);
   friend OBox  operator* (C OBox &obox, C Matrix3 &m);
   friend OBox  operator* (C OBox &obox, C Matrix  &m);

   // get / set
   Vec center()C {return box.center()*matrix;} // get center
   Flt area  ()C {return box.area  ()       ;} // get surface area
   Flt volume()C {return box.volume()       ;} // get volume

   Str asText()C {return box.asText();} // get text description

   // operations
   OBox& extend(  Flt      e                            ); // extend
   OBox& mul   (C Matrix3 &matrix, Bool normalized=false); // transform by 'matrix', if you know that the matrix is normalized then set 'normalized=true' for more performance
   OBox& mul   (C Matrix  &matrix, Bool normalized=false); // transform by 'matrix', if you know that the matrix is normalized then set 'normalized=true' for more performance
   OBox& div   (C Matrix3 &matrix, Bool normalized=false); // transform by 'matrix', if you know that the matrix is normalized then set 'normalized=true' for more performance
   OBox& div   (C Matrix  &matrix, Bool normalized=false); // transform by 'matrix', if you know that the matrix is normalized then set 'normalized=true' for more performance

   void toCorners(Vec (&v)[8])C; // convert to 8 corner points

   OBox& mirrorX(); // mirror in X axis
   OBox& mirrorY(); // mirror in Y axis
   OBox& mirrorZ(); // mirror in Z axis

   // draw
   void draw(C Color &color=WHITE, Bool fill=false)C; // this relies on active object matrix which can be set using 'SetMatrix' function

   OBox() {}
   OBox(C Box   &box, C Matrix &matrix=MatrixIdentity) {T.box=box; T.matrix=matrix;} // 'matrix' must be normalized
   OBox(C Torus &torus);
};
/******************************************************************************/
inline BoxI Round(C Box &b) {return BoxI(Round(b.min.x), Round(b.min.y), Round(b.min.z), Round(b.max.x), Round(b.max.y), Round(b.max.z));}

// distance
Flt Dist (C Vec  &point, C Box   &box  ); // distance   between point and a box
Flt Dist (C Vec  &point, C OBox  &obox ); // distance   between point and a box
Flt Dist2(C Vec  &point, C Box   &box  ); // distance^2 between point and a box
Flt Dist2(C Vec  &point, C OBox  &obox ); // distance^2 between point and a box
Flt Dist (C Edge &edge , C Box   &box  ); // distance   between edge  and a box
Flt Dist (C Edge &edge , C OBox  &obox ); // distance   between edge  and a box
Flt Dist (C Box  &a    , C Box   &b    ); // distance   between box   and a box
Flt Dist (C Box  &box  , C Plane &plane); // distance   between box   and a plane
Flt Dist (C OBox &obox , C Plane &plane); // distance   between box   and a plane

// if cuts
Bool Cuts   (C Vec  &point, C Box  &box ); // if point     cuts a box
Bool Cuts   (C Vec  &point, C OBox &obox); // if point     cuts a box
Bool Cuts   (C VecI &point, C BoxI &box ); // if point     cuts a box
Bool Cuts   (C Edge &edge , C Box  &box ); // if edge      cuts a box
Bool Cuts   (C Edge &edge , C OBox &obox); // if edge      cuts a box
Bool Cuts   (C Rect &rect , C Box  &box ); // if rectangle cuts a rectangle (from box)
Bool Cuts   (C Box  &a    , C Box  &b   ); // if box       cuts a box, epsilon=0
Bool Cuts   (C Box  &box  , C OBox &obox); // if box       cuts a box, epsilon=0
Bool Cuts   (C OBox &a    , C OBox &b   ); // if box       cuts a box, epsilon=0
Bool Cuts   (C BoxD &a    , C BoxD &b   ); // if box       cuts a box, epsilon=0
Bool Cuts   (C BoxI &a    , C BoxI &b   ); // if box       cuts a box, epsilon=0
Bool CutsEps(C Box  &a    , C Box  &b   ); // if box       cuts a box, epsilon=EPS
Bool CutsEps(C BoxD &a    , C BoxD &b   ); // if box       cuts a box, epsilon=EPSD

Bool Inside(C Box  &a, C Box  &b); // if 'a' is fully inside 'b'
Bool Inside(C BoxD &a, C BoxD &b); // if 'a' is fully inside 'b'
Bool Inside(C BoxI &a, C BoxI &b); // if 'a' is fully inside 'b'

// sweep
Bool SweepPointBox(C Vec &point, C Vec &move, C Box  &box , Flt *hit_frac=NULL, Vec *hit_pos=NULL); // if moving point cuts through a static box
Bool SweepPointBox(C Vec &point, C Vec &move, C OBox &obox, Flt *hit_frac=NULL, Vec *hit_pos=NULL); // if moving point cuts through a static oriented box
/******************************************************************************/

/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Orient' to handle objects orientation.

   This is similar to 'Matrix', except the 'Orient' stores only 2 vectors of the orientation:
      'z-forward' and 'y-up' (the 'x-right' can always be computed from 'z' and 'y')

/******************************************************************************/
struct Orient // Orientation
{
   Vec dir ,                               // direction                  (z - forward)
       perp;                               // perpendicular to direction (y - up     )
   Vec cross()C {return Cross(perp, dir);} // cross                      (x - right  )

          Orient& operator+=(C Orient  &o);
          Orient& operator*=(  Flt      f);
          Orient& operator*=(C Vec     &v);
          Orient& operator*=(C Matrix3 &m) {return transform(m);}
          Orient& operator/=(C Matrix3 &m);
   friend Orient  operator* (C Orient  &o,   Flt      f);
   friend Orient  operator* (  Flt      f, C Orient  &o);
   friend Orient  operator* (C Orient  &o, C Matrix3 &m);

   // set
   Orient& zero    (          ); // set all vectors to zero
   Orient& identity(          ); // set identity
   Orient& setDir  (C Vec &dir); // set from 'dir' and calculate correct 'perp'
   Orient& fixPerp (          ); // fix perpendicular, use when 'dir' or 'perp' has changed, this method aligns 'perp' so it's perpendicular to 'dir' and normalized
   Bool    fix     (          ); // normalize and fix perpendicular, false on fail

   // transform
   Orient& rotateDir  (  Flt      angle); // rotate by dir   vector, this is equal to "transform(Matrix3().setRotate(dir    , angle), true)" but faster
   Orient& rotatePerp (  Flt      angle); // rotate by perp  vector, this is equal to "transform(Matrix3().setRotate(perp   , angle), true)" but faster
   Orient& rotateCross(  Flt      angle); // rotate by cross vector, this is equal to "transform(Matrix3().setRotate(cross(), angle), true)" but faster
   Orient& transform  (C Matrix3 &matrix, Bool normalized=false); // transform by matrix, if 'matrix' is normalized set 'normalized' to true for more performance

   // operations
   Matrix3& inverse(Matrix3 &dest)C; // inverse orientation and store it in 'dest' matrix, returns 'dest'

   // io
   void save(Memp<TextNode> nodes)C; // save as text

   Orient() {}
   Orient(C Vec        &dir, C Vec &perp) {T.dir=dir; T.perp=perp;}
   Orient(C Matrix3    &m);
   Orient(C Quaternion &q);
};
/******************************************************************************/
STRUCT(OrientP , Orient) // Positioned Orientation
//{
   Vec pos; // position

          OrientP& operator+=(C Vec     &v) {pos+=v; return T;}
          OrientP& operator-=(C Vec     &v) {pos-=v; return T;}
          OrientP& operator+=(C OrientP &o);
          OrientP& operator*=(  Flt      f);
          OrientP& operator*=(C Vec     &v);
          OrientP& operator*=(C Matrix3 &m) {return transform(m);}
          OrientP& operator*=(C Matrix  &m) {return transform(m);}
          OrientP& operator/=(C Matrix3 &m);
          OrientP& operator/=(C Matrix  &m);
   friend OrientP  operator* (C OrientP &o,   Flt      f);
   friend OrientP  operator* (  Flt      f, C OrientP &o);
   friend OrientP  operator* (C OrientP &o, C Matrix3 &m);
   friend OrientP  operator* (C OrientP &o, C Matrix  &m);

   // set
   OrientP& zero     (                      ); // set all vectors to zero
   OrientP& identity (                      ); // set identity
   OrientP& setPosDir(C Vec &pos, C Vec &dir); // set from 'pos dir' and calculate correct 'perp'

   // transform
   OrientP& transform(C Matrix3 &matrix, Bool normalized=false); // transform by matrix, if 'matrix' is normalized set 'normalized' to true for more performance
   OrientP& transform(C Matrix  &matrix, Bool normalized=false); // transform by matrix, if 'matrix' is normalized set 'normalized' to true for more performance

   // draw
   void draw(C Color &color, Flt size=0.2f)C; // this can be optionally called outside of Render function, this relies on active object matrix which can be set using 'SetMatrix' function

   // io
   void save(Memp<TextNode> nodes)C; // save as text

   OrientP() {}
   OrientP(C Vec        &pos, C Vec &dir, C Vec &perp) {T.pos=pos; T.dir=dir; T.perp=perp;}
   OrientP(C Orient     &o);
   OrientP(C Matrix3    &m);
   OrientP(C Matrix     &m);
   OrientP(C Quaternion &q);
};
/******************************************************************************/
struct AxisRoll // Axis+Roll based rotation
{
   Vec axis; // direction of this vector specifies the rotation axis, and the length of this vector specifies the rotation angle
   Flt roll; // roll angle, rotation along the original direction

   Vec4& v4()  {return (Vec4&)T;} // return this in Vec4 format, this returns reference to self and not a new object!
 C Vec4& v4()C {return (Vec4&)T;} // return this in Vec4 format, this returns reference to self and not a new object!

   // set
   AxisRoll& zero(                                 ) {axis.zero(); roll=0; return T;} // clear to zero
   AxisRoll& from(C Orient &start, C Orient &result); // set axis roll which transforms 'start' into 'result'

   // transform
   AxisRoll& transform (C Matrix3 &matrix); // transform by matrix
   AxisRoll& operator*=(C Matrix3 &matrix) {return transform(matrix);}   // transform by matrix
   AxisRoll& operator*=(  Flt      f     ) {axis*=f; roll*=f; return T;} // scale by 'f'
};
/******************************************************************************/
Orient GetAnimOrient(C Orient  &orn ,                                             C Orient *parent=NULL                               ); // get animation orientation     'orn'                               to be displayed when having 'parent'                               , which is " orn               /  parent               "
Orient GetAnimOrient(C Orient  &bone, C Matrix3 &bone_matrix,                     C Orient *parent=NULL, C Matrix3 *parent_matrix=NULL); // get animation orientation for 'bone' transformed by 'bone_matrix' to be displayed when having 'parent' transformed by 'parent_matrix', which is "(bone*bone_matrix) / (parent*parent_matrix)"
Vec    GetAnimPos   (C OrientP &bone, C Vec     &bone_pos   , C Orient &bone_orn, C Orient *parent=NULL, C Matrix  *parent_matrix=NULL); // get animation position    for 'bone' currently set with 'bone_orn' orientation and having 'bone_pos' offset, with 'parent' transformed by 'parent_matrix'
/******************************************************************************/

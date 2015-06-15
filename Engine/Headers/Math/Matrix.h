/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Matrix3' to represent objects orientation and scale.

   Use 'Matrix' to represent objects orientation, scale and position.

   Use 'GetVel' to calculate objects velocities according to its previous and current matrix.

   Use 'SetMatrix' to set mesh rendering matrix (use before manual drawing only).

/******************************************************************************/
struct Matrix3 // Matrix 3x3 (orientation + scale)
{
   Vec x, // right   vector
       y, // up      vector
       z; // forward vector

   // transform
          Matrix3& operator*=(  Flt      f);
          Matrix3& operator/=(  Flt      f);
          Matrix3& operator*=(C Vec     &v);
          Matrix3& operator/=(C Vec     &v);
          Matrix3& operator+=(C Matrix3 &m);
          Matrix3& operator-=(C Matrix3 &m);
          Matrix3& operator*=(C Matrix3 &m) {return mul(m);}
          Matrix3& operator/=(C Matrix3 &m) {return div(m);}
 
   friend Matrix3  operator* (C Matrix3 &a, C Matrix3 &b) {Matrix3 temp; a.mul    (b, temp); return temp;} // get a*b
   friend Matrix3  operator/ (C Matrix3 &a, C Matrix3 &b) {Matrix3 temp; a.div    (b, temp); return temp;} // get a/b
   friend Matrix3  operator~ (C Matrix3 &m              ) {Matrix3 temp; m.inverse(   temp); return temp;} // get inversed 'm'

   void     mul(C Matrix3 &matrix, Matrix3 &dest)C;                           // multiply self by 'matrix' and store result in 'dest'
   Matrix3& mul(C Matrix3 &matrix               ) {mul(matrix, T); return T;} // multiply self by 'matrix'

   void     div(C Matrix3 &matrix, Matrix3 &dest, Bool normalized=false)C;                                       // divide self by 'matrix' and store result in 'dest', if you know that 'matrix' is normalized then set 'normalized=true' for more performance
   Matrix3& div(C Matrix3 &matrix               , Bool normalized=false) {div(matrix, T, normalized); return T;} // divide self by 'matrix'                           , if you know that 'matrix' is normalized then set 'normalized=true' for more performance

   Matrix3& inverse(Matrix3 &dest, Bool normalized=false)C;                                   // inverse self to 'dest', if you know that the matrix is normalized then set 'normalized=true' for more performance !! returns 'dest' !!
   Matrix3& inverse(               Bool normalized=false) {inverse(T, normalized); return T;} // inverse self          , if you know that the matrix is normalized then set 'normalized=true' for more performance
   Matrix3& inverseScale(                               );                                    // inverse scale

   Matrix3& normalize(            ); // normalize scale           , this sets the length of 'x' 'y' 'z' vectors to 1
   Matrix3& normalize(  Flt  scale); // normalize scale to 'scale', this sets the length of 'x' 'y' 'z' vectors to 'scale'
   Matrix3& normalize(C Vec &scale); // normalize scale to 'scale', this sets the length of 'x' 'y' 'z' vectors to 'scale.x' 'scale.y' 'scale.z'

   Matrix3& scale     (              Flt  scale) {T*=scale; return T;} // scale
   Matrix3& scale     (            C Vec &scale) {T*=scale; return T;} // scale
   Matrix3& scaleL    (            C Vec &scale);                      // scale in local space
   Matrix3& scale     (C Vec &dir,   Flt  scale);                      // scale along       'dir' direction by 'scale' value, 'dir' must be normalized
   Matrix3& scalePlane(C Vec &nrm,   Flt  scale);                      // scale along plane of 'nrm' normal by 'scale' value, 'nrm' must be normalized

   Matrix3& rotateX (             Flt angle); // rotate by x axis
   Matrix3& rotateY (             Flt angle); // rotate by y axis
   Matrix3& rotateZ (             Flt angle); // rotate by z axis
   Matrix3& rotateXY(  Flt  x   , Flt y    ); // rotate by x axis and then by y axis, works the same as 'rotateX(x).rotateY(y)' but faster
   Matrix3& rotate  (C Vec &axis, Flt angle); // rotate by vector, 'axis' must be normalized
   Matrix3& rotateXL(             Flt angle) {return Any(angle) ? rotate(!x, angle) : T;} // rotate matrix by its x vector (x-axis rotation in local space)
   Matrix3& rotateYL(             Flt angle) {return Any(angle) ? rotate(!y, angle) : T;} // rotate matrix by its y vector (y-axis rotation in local space)
   Matrix3& rotateZL(             Flt angle) {return Any(angle) ? rotate(!z, angle) : T;} // rotate matrix by its z vector (z-axis rotation in local space)

   Matrix3& mirrorX(             ); // mirror matrix in X axis
   Matrix3& mirrorY(             ); // mirror matrix in Y axis
   Matrix3& mirrorZ(             ); // mirror matrix in Z axis
   Matrix3& mirror (C Vec &normal); // mirror matrix by   plane normal

   Matrix3& swapYZ(); // swap Y and Z components of every vector

   // set (set methods reset the full matrix)
   Matrix3& identity(         ); // set as identity
   Matrix3& identity(Flt blend); // set as identity, this method is similar to 'clear()' however it does not perform full reset of the matrix. Instead, smooth reset is applied depending on 'blend' value (0=no reset, 1=full reset)
   Matrix3& zero    (         ); // set all vectors to zero

   Matrix3& setScale(  Flt  scale); // set as scaled identity
   Matrix3& setScale(C Vec &scale); // set as scaled identity

   Matrix3& setRotateX (             Flt angle); // set as   x-rotated identity
   Matrix3& setRotateY (             Flt angle); // set as   y-rotated identity
   Matrix3& setRotateZ (             Flt angle); // set as   z-rotated identity
   Matrix3& setRotateXY(  Flt  x   , Flt y    ); // set as x-y-rotated identity, works the same as 'setRotateX(x).rotateY(y)' but faster
   Matrix3& setRotate  (C Vec &axis, Flt angle); // set as     rotated by vector identity, 'axis' must be normalized

   Matrix3& setOrient  (DIR_ENUM dir                       ); // set as identity orientation from DIR_ENUM
   Matrix3& setRight   (C Vec &right                       ); // set as x='right'       and calculate correct y,z, 'right'        must be normalized
   Matrix3& setUp      (C Vec &up                          ); // set as y='up'          and calculate correct x,z, 'up'           must be normalized
   Matrix3& setDir     (C Vec &dir                         ); // set as z='dir'         and calculate correct x,y, 'dir'          must be normalized
   Matrix3& setDir     (C Vec &dir, C Vec &up              ); // set as z='dir', y='up' and calculate correct x  , 'dir up'       must be normalized
   Matrix3& setDir     (C Vec &dir, C Vec &up, C Vec &right); // set as z='dir', y='up', x='right'               , 'dir up right' must be normalized
   Matrix3& setRotation(C Vec &dir_from, C Vec &dir_to, Flt blend=1, Flt roll=0); // set as matrix which rotates 'dir_from' into 'dir_to', using blend value and additional roll angle, 'dir_from dir_to' must be normalized

   // get
   Vec    scale (                                )C; // get each     axis scale
   Flt avgScale (                                )C; // get average  axis scale
   Flt maxScale (                                )C; // get maximum  axis scale
   Vec angles   (                                )C; // get rotation angles, this allows to reconstruct the matrix using "setRotateZ(angle.z).rotateX(angle.x).rotateY(angle.y)" or faster by using "setRotateZ(angle.z).rotateXY(angle.x, angle.y)"
   Vec axis     (           Bool normalized=false)C; // get rotation axis          , if you know that the matrix is normalized then set 'normalized=true' for more performance
   Flt angle    (           Bool normalized=false)C; // get rotation angle         , if you know that the matrix is normalized then set 'normalized=true' for more performance
   Flt axisAngle(Vec &axis, Bool normalized=false)C; // get rotation axis and angle, if you know that the matrix is normalized then set 'normalized=true' for more performance

   Str asText(Int precision=INT_MAX)C {return S+"X: "+x.asText(precision)+", Y: "+y.asText(precision)+", Z:"+z.asText(precision);} // get text description

   // draw
   void draw(C Vec &pos, C Color &x_color=RED, C Color &y_color=GREEN, C Color &z_color=BLUE, Bool arrow=true)C; // draw axes, this can be optionally called outside of Render function, this relies on active object matrix which can be set using 'SetMatrix' function

   Matrix3() {}
   Matrix3(  Flt     scale) {setScale(scale);}
   Matrix3(C Vec    &scale) {setScale(scale);}
   Matrix3(C Vec &x, C Vec &y, C Vec &z) {T.x=x; T.y=y; T.z=z;}
   Matrix3(C MatrixD3   &m);
   Matrix3(C Matrix     &m);
   Matrix3(C Matrix4    &m);
   Matrix3(C Orient     &o);
   Matrix3(C Quaternion &q);
};extern const Matrix3
   MatrixIdentity3; // 3x3 Identity
/******************************************************************************/
struct MatrixD3 // Matrix 3x3 (orientation + scale, double precision)
{
   VecD x, // right   vector
        y, // up      vector
        z; // forward vector

   // transform
          MatrixD3& operator*=(  Dbl       f);
          MatrixD3& operator/=(  Dbl       f);
          MatrixD3& operator*=(C VecD     &v);
          MatrixD3& operator/=(C VecD     &v);
          MatrixD3& operator+=(C MatrixD3 &m);
          MatrixD3& operator-=(C MatrixD3 &m);
          MatrixD3& operator*=(C MatrixD3 &m) {return mul(m);}
          MatrixD3& operator/=(C MatrixD3 &m) {return div(m);}
 
   friend MatrixD3  operator* (C MatrixD3 &a, C MatrixD3 &b) {MatrixD3 temp; a.mul    (b, temp); return temp;} // get a*b
   friend MatrixD3  operator/ (C MatrixD3 &a, C MatrixD3 &b) {MatrixD3 temp; a.div    (b, temp); return temp;} // get a/b
   friend MatrixD3  operator~ (C MatrixD3 &m               ) {MatrixD3 temp; m.inverse(   temp); return temp;} // get inversed 'm'

   void      mul(C MatrixD3 &matrix, MatrixD3 &dest)C;                           // multiply self by 'matrix' and store result in 'dest'
   MatrixD3& mul(C MatrixD3 &matrix                ) {mul(matrix, T); return T;} // multiply self by 'matrix'

   void      div(C MatrixD3 &matrix, MatrixD3 &dest, Bool normalized=false)C;                                       // divide self by 'matrix' and store result in 'dest', if you know that 'matrix' is normalized then set 'normalized=true' for more performance
   MatrixD3& div(C MatrixD3 &matrix                , Bool normalized=false) {div(matrix, T, normalized); return T;} // divide self by 'matrix'                           , if you know that 'matrix' is normalized then set 'normalized=true' for more performance

   MatrixD3& inverse(MatrixD3 &dest, Bool normalized=false)C;                                   // inverse self to 'dest', if you know that the matrix is normalized then set 'normalized=true' for more performance !! returns 'dest' !!
   MatrixD3& inverse(                Bool normalized=false) {inverse(T, normalized); return T;} // inverse self          , if you know that the matrix is normalized then set 'normalized=true' for more performance
   MatrixD3& inverseScale(                                );                                    // inverse scale

   MatrixD3& normalize(             ); // normalize scale           , this sets the length of 'x' 'y' 'z' vectors to 1
   MatrixD3& normalize(  Dbl   scale); // normalize scale to 'scale', this sets the length of 'x' 'y' 'z' vectors to 'scale'
   MatrixD3& normalize(C VecD &scale); // normalize scale to 'scale', this sets the length of 'x' 'y' 'z' vectors to 'scale.x' 'scale.y' 'scale.z'

   MatrixD3& scale     (               Dbl   scale) {T*=scale; return T;} // scale
   MatrixD3& scale     (             C VecD &scale) {T*=scale; return T;} // scale
   MatrixD3& scale     (C VecD &dir,   Dbl   scale);                      // scale along       'dir' direction by 'scale' value, 'dir' must be normalized
   MatrixD3& scalePlane(C VecD &nrm,   Dbl   scale);                      // scale along plane of 'nrm' normal by 'scale' value, 'nrm' must be normalized

   MatrixD3& rotateX (              Dbl angle); // rotate by x axis
   MatrixD3& rotateY (              Dbl angle); // rotate by y axis
   MatrixD3& rotateZ (              Dbl angle); // rotate by z axis
   MatrixD3& rotateXY(  Dbl   x   , Dbl y    ); // rotate by x axis and then by y axis, works the same as 'rotateX(x).rotateY(y)' but faster
   MatrixD3& rotate  (C VecD &axis, Dbl angle); // rotate by vector, 'axis' must be normalized
   MatrixD3& rotateXL(              Dbl angle) {return Any(angle) ? rotate(!x, angle) : T;} // rotate matrix by its x vector (x-axis rotation in local space)
   MatrixD3& rotateYL(              Dbl angle) {return Any(angle) ? rotate(!y, angle) : T;} // rotate matrix by its y vector (y-axis rotation in local space)
   MatrixD3& rotateZL(              Dbl angle) {return Any(angle) ? rotate(!z, angle) : T;} // rotate matrix by its z vector (z-axis rotation in local space)

   MatrixD3& mirrorX(              ); // mirror matrix in X axis
   MatrixD3& mirrorY(              ); // mirror matrix in Y axis
   MatrixD3& mirrorZ(              ); // mirror matrix in Z axis
   MatrixD3& mirror (C VecD &normal); // mirror matrix by   plane normal

   // set (set methods reset the full matrix)
   MatrixD3& identity(); // set as identity
   MatrixD3& zero    (); // set all vectors to zero

   MatrixD3& setScale(  Dbl   scale); // set as scaled identity
   MatrixD3& setScale(C VecD &scale); // set as scaled identity

   MatrixD3& setRotateX (              Dbl angle); // set as   x-rotated identity
   MatrixD3& setRotateY (              Dbl angle); // set as   y-rotated identity
   MatrixD3& setRotateZ (              Dbl angle); // set as   z-rotated identity
   MatrixD3& setRotateXY(  Dbl   x   , Dbl y    ); // set as x-y-rotated identity, works the same as 'setRotateX(x).rotateY(y)' but faster
   MatrixD3& setRotate  (C VecD &axis, Dbl angle); // set as     rotated by vector identity, 'axis' must be normalized

   MatrixD3& setOrient  (DIR_ENUM dir                          ); // set as identity orientation from DIR_ENUM
   MatrixD3& setRight   (C VecD &right                         ); // set as x='right'       and calculate correct y,z, 'right'        must be normalized
   MatrixD3& setUp      (C VecD &up                            ); // set as y='up'          and calculate correct x,z, 'up'           must be normalized
   MatrixD3& setDir     (C VecD &dir                           ); // set as z='dir'         and calculate correct x,y, 'dir'          must be normalized
   MatrixD3& setDir     (C VecD &dir, C VecD &up               ); // set as z='dir', y='up' and calculate correct x  , 'dir up'       must be normalized
   MatrixD3& setDir     (C VecD &dir, C VecD &up, C VecD &right); // set as z='dir', y='up', x='right'               , 'dir up right' must be normalized
   MatrixD3& setRotation(C VecD &dir_from, C VecD &dir_to, Dbl blend=1, Dbl roll=0); // set as matrix which rotates 'dir_from' into 'dir_to', using blend value and additional roll angle, 'dir_from dir_to' must be normalized

   // get
   VecD    scale (                                 )C; // get each     axis scale
   Dbl  avgScale (                                 )C; // get average  axis scale
   Dbl  maxScale (                                 )C; // get maximum  axis scale
   VecD angles   (                                 )C; // get rotation angles, this allows to reconstruct the matrix using "setRotateZ(angle.z).rotateX(angle.x).rotateY(angle.y)" or faster by using "setRotateZ(angle.z).rotateXY(angle.x, angle.y)"
   VecD axis     (            Bool normalized=false)C; // get rotation axis          , if you know that the matrix is normalized then set 'normalized=true' for more performance
   Dbl  angle    (            Bool normalized=false)C; // get rotation angle         , if you know that the matrix is normalized then set 'normalized=true' for more performance
   Dbl  axisAngle(VecD &axis, Bool normalized=false)C; // get rotation axis and angle, if you know that the matrix is normalized then set 'normalized=true' for more performance

   Str asText(Int precision=INT_MAX)C {return S+"X: "+x.asText(precision)+", Y: "+y.asText(precision)+", Z:"+z.asText(precision);} // get text description

   // draw
   void draw(C VecD &pos, C Color &x_color=RED, C Color &y_color=GREEN, C Color &z_color=BLUE, Bool arrow=true)C; // draw axes, this can be optionally called outside of Render function, this relies on active object matrix which can be set using 'SetMatrix' function

   MatrixD3() {}
   MatrixD3(  Dbl      scale) {setScale(scale);}
   MatrixD3(C VecD    &scale) {setScale(scale);}
   MatrixD3(C VecD &x, C VecD &y, C VecD &z) {T.x=x; T.y=y; T.z=z;}
   MatrixD3(C Matrix3 &m);
   MatrixD3(C MatrixD &m);
};
/******************************************************************************/
STRUCT(Matrix , Matrix3) // Matrix 4x3 (orientation + scale + position)
//{
   Vec pos; // position

   Matrix3& orn()  {return T;} // get reference to self as       Matrix3
 C Matrix3& orn()C {return T;} // get reference to self as const Matrix3

   // transform
          Matrix& operator+=(C Vec2    &v) {pos.v2()+=v; return T;}
          Matrix& operator-=(C Vec2    &v) {pos.v2()-=v; return T;}
          Matrix& operator+=(C Vec     &v) {pos     +=v; return T;}
          Matrix& operator-=(C Vec     &v) {pos     -=v; return T;}
          Matrix& operator*=(  Flt      f);
          Matrix& operator/=(  Flt      f);
          Matrix& operator*=(C Vec     &v);
          Matrix& operator/=(C Vec     &v);
          Matrix& operator+=(C Matrix  &m);
          Matrix& operator-=(C Matrix  &m);
          Matrix& operator*=(C Matrix3 &m) {return mul(m);}
          Matrix& operator*=(C Matrix  &m) {return mul(m);}
          Matrix& operator/=(C Matrix3 &m) {return div(m);}
          Matrix& operator/=(C Matrix  &m) {return div(m);}

   friend Matrix  operator+ (C Matrix  &m, C Vec2    &v) {return Matrix(m)+=v;}
   friend Matrix  operator- (C Matrix  &m, C Vec2    &v) {return Matrix(m)-=v;}
   friend Matrix  operator+ (C Matrix  &m, C Vec     &v) {return Matrix(m)+=v;}
   friend Matrix  operator- (C Matrix  &m, C Vec     &v) {return Matrix(m)-=v;}
   friend Matrix  operator* (C Matrix  &a, C Matrix3 &b) {Matrix temp; a.mul    (b, temp); return temp;} // get a*b
   friend Matrix  operator* (C Matrix  &a, C Matrix  &b) {Matrix temp; a.mul    (b, temp); return temp;} // get a*b
   friend Matrix  operator/ (C Matrix  &a, C Matrix3 &b) {Matrix temp; a.div    (b, temp); return temp;} // get a/b
   friend Matrix  operator/ (C Matrix  &a, C Matrix  &b) {Matrix temp; a.div    (b, temp); return temp;} // get a/b
   friend Matrix  operator~ (C Matrix  &m              ) {Matrix temp; m.inverse(   temp); return temp;} // get inversed 'm'

   void    mul(C Matrix3 &matrix, Matrix  &dest)C;                           // multiply self by 'matrix' and store result into 'dest'
   void    mul(C Matrix  &matrix, Matrix  &dest)C;                           // multiply self by 'matrix' and store result into 'dest'
   void    mul(C Matrix  &matrix, Matrix4 &dest)C;                           // multiply self by 'matrix' and store result into 'dest'
   void    mul(C Matrix4 &matrix, Matrix4 &dest)C;                           // multiply self by 'matrix' and store result into 'dest'
   Matrix& mul(C Matrix  &matrix               ) {mul(matrix, T); return T;} // multiply self by 'matrix'
   Matrix& mul(C Matrix3 &matrix               ) {mul(matrix, T); return T;} // multiply self by 'matrix'

   void    div(C Matrix3 &matrix, Matrix &dest, Bool normalized=false)C;                                       // divide self by 'matrix' and store result in 'dest', if you know that 'matrix' is normalized then set 'normalized=true' for more performance
   void    div(C Matrix  &matrix, Matrix &dest, Bool normalized=false)C;                                       // divide self by 'matrix' and store result in 'dest', if you know that 'matrix' is normalized then set 'normalized=true' for more performance
   Matrix& div(C Matrix3 &matrix              , Bool normalized=false) {div(matrix, T, normalized); return T;} // divide self by 'matrix'                           , if you know that 'matrix' is normalized then set 'normalized=true' for more performance
   Matrix& div(C Matrix  &matrix              , Bool normalized=false) {div(matrix, T, normalized); return T;} // divide self by 'matrix'                           , if you know that 'matrix' is normalized then set 'normalized=true' for more performance

   Matrix& inverse(Matrix &dest, Bool normalized=false)C;                                   // inverse self to 'dest', if you know that the matrix is normalized then set 'normalized=true' for more performance !! returns 'dest' !!
   Matrix& inverse(              Bool normalized=false) {inverse(T, normalized); return T;} // inverse self          , if you know that the matrix is normalized then set 'normalized=true' for more performance

   Matrix& normalize(            ) {super::normalize(     ); return T;} // normalize scale           , this sets the length of 'x' 'y' 'z' vectors to 'scale'
   Matrix& normalize(  Flt  scale) {super::normalize(scale); return T;} // normalize scale to 'scale', this sets the length of 'x' 'y' 'z' vectors to 'scale'
   Matrix& normalize(C Vec &scale) {super::normalize(scale); return T;} // normalize scale to 'scale', this sets the length of 'x' 'y' 'z' vectors to 'scale.x' 'scale.y' 'scale.z'

   Matrix& move(Flt x, Flt y, Flt z) {T+=Vec(x, y, z); return T;} // move
   Matrix& move(C Vec2 &move       ) {T+=move        ; return T;} // move
   Matrix& move(C Vec  &move       ) {T+=move        ; return T;} // move

   Matrix& scale     (              Flt  scale) {           T*=scale ; return T;} // scale
   Matrix& scale     (            C Vec &scale) {           T*=scale ; return T;} // scale
   Matrix& scaleL    (            C Vec &scale);                                  // scale in local space
   Matrix& scaleOrn  (              Flt  scale) {super::scale (scale); return T;} // scale orientation only
   Matrix& scaleOrn  (            C Vec &scale) {super::scale (scale); return T;} // scale orientation only
   Matrix& scaleOrnL (            C Vec &scale) {super::scaleL(scale); return T;} // scale orientation only in local space
   Matrix& scale     (C Vec &dir,   Flt  scale);                                  // scale along       'dir' direction by 'scale' value, 'dir' must be normalized
   Matrix& scalePlane(C Vec &nrm,   Flt  scale);                                  // scale along plane of 'nrm' normal by 'scale' value, 'nrm' must be normalized

   Matrix& rotateX (             Flt angle);                                    // rotate by x axis
   Matrix& rotateY (             Flt angle);                                    // rotate by y axis
   Matrix& rotateZ (             Flt angle);                                    // rotate by z axis
   Matrix& rotateXY(  Flt  x   , Flt y    );                                    // rotate by x axis and then by y axis, works the same as rotateX(x).rotateY(y) but faster
   Matrix& rotate  (C Vec &axis, Flt angle);                                    // rotate by vector, 'axis' must be normalized
   Matrix& rotateXL(             Flt angle) {super::rotateXL(angle); return T;} // rotate matrix by its x vector (x-axis rotation in local space)
   Matrix& rotateYL(             Flt angle) {super::rotateYL(angle); return T;} // rotate matrix by its y vector (y-axis rotation in local space)
   Matrix& rotateZL(             Flt angle) {super::rotateZL(angle); return T;} // rotate matrix by its z vector (z-axis rotation in local space)

   Matrix& mirrorX(              ); // mirror matrix in X axis
   Matrix& mirrorY(              ); // mirror matrix in Y axis
   Matrix& mirrorZ(              ); // mirror matrix in Z axis
   Matrix& mirror (C Plane &plane); // mirror matrix by   plane

   Matrix& swapYZ(); // swap Y and Z components of every vector

   // set (set methods reset the full matrix)
   Matrix& identity(         ); // set as identity
   Matrix& identity(Flt blend); // set as identity, this method is similar to 'clear()' however it does not perform full reset of the matrix. Instead, smooth reset is applied depending on 'blend' value (0=no reset, 1=full reset)
   Matrix& zero    (         ); // set all vectors to zero

   Matrix& setPos     (C Vec2 &pos                ); // set as positioned identity
   Matrix& setPos     (C Vec  &pos                ); // set as positioned identity
   Matrix& setScale   (  Flt   scale              ); // set as scaled     identity
   Matrix& setScale   (C Vec  &scale              ); // set as scaled     identity
   Matrix& setPosScale(C Vec  &pos  ,   Flt  scale); // set as positioned & scaled identity
   Matrix& setPosScale(C Vec  &pos  , C Vec &scale); // set as positioned & scaled identity
   Matrix& setScalePos(  Flt   scale, C Vec &pos  ); // set as scaled & positioned identity
   Matrix& setScalePos(C Vec  &scale, C Vec &pos  ); // set as scaled & positioned identity

   Matrix& setRotateX (             Flt angle); // set as   x-rotated identity
   Matrix& setRotateY (             Flt angle); // set as   y-rotated identity
   Matrix& setRotateZ (             Flt angle); // set as   z-rotated identity
   Matrix& setRotateXY(  Flt  x   , Flt y    ); // set as x-y-rotated identity, works the same as setRotateX(x).rotateY(y) but faster
   Matrix& setRotate  (C Vec &axis, Flt angle); // set as     rotated by vector identity, 'axis' must be normalized

   Matrix& setPosOrient(C Vec &pos,   DIR_ENUM dir                     ); // set as positioned orientation from DIR_ENUM
   Matrix& setPosRight (C Vec &pos, C Vec &right                       ); // set as pos='pos', x='right'       and calculate correct y,z, 'right'        must be normalized
   Matrix& setPosUp    (C Vec &pos, C Vec &up                          ); // set as pos='pos', y='up'          and calculate correct x,z, 'up'           must be normalized
   Matrix& setPosDir   (C Vec &pos, C Vec &dir                         ); // set as pos='pos', z='dir'         and calculate correct x,y, 'dir'          must be normalized
   Matrix& setPosDir   (C Vec &pos, C Vec &dir, C Vec &up              ); // set as pos='pos', z='dir', y='up' and calculate correct x  , 'dir up'       must be normalized
   Matrix& setPosDir   (C Vec &pos, C Vec &dir, C Vec &up, C Vec &right); // set as pos='pos', z='dir', y='up', x='right'               , 'dir up right' must be normalized
   Matrix& setRotation (C Vec &pos, C Vec &dir_from, C Vec &dir_to, Flt blend=1, Flt roll=0); // set as matrix which rotates 'dir_from' into 'dir_to', using blend value and additional roll angle, 'dir_from dir_to' must be normalized

   Matrix& set          (C Box &src, C Box &dest); // set as matrix that transforms 'src' to 'dest' (src*m=dest)
   Matrix& setNormalizeX(C Box &box             ); // set as matrix that (box*m).w()         =1
   Matrix& setNormalizeY(C Box &box             ); // set as matrix that (box*m).h()         =1
   Matrix& setNormalizeZ(C Box &box             ); // set as matrix that (box*m).d()         =1
   Matrix& setNormalize (C Box &box             ); // set as matrix that (box*m).size().max()=1

   // get
   Vec scale()C {return super::scale();} // get each axis scale

   Str asText(Int precision=INT_MAX)C {return super::asText(precision)+", Pos: "+pos.asText(precision);} // get text description

   // operations

   Matrix& setTransformAtPos(C Vec &pos, C Matrix3 &matrix) {return setPos(-pos).mul(matrix).move(pos);} // set as transformation at position
   Matrix& setTransformAtPos(C Vec &pos, C Matrix  &matrix) {return setPos(-pos).mul(matrix).move(pos);} // set as transformation at position
   Matrix&    transformAtPos(C Vec &pos, C Matrix3 &matrix) {return move  (-pos).mul(matrix).move(pos);} //        transform      at position
   Matrix&    transformAtPos(C Vec &pos, C Matrix  &matrix) {return move  (-pos).mul(matrix).move(pos);} //        transform      at position

   // draw
   void draw(C Color &x_color=RED, C Color &y_color=GREEN, C Color &z_color=BLUE, Bool arrow=true)C {super::draw(pos, x_color, y_color, z_color, arrow);} // draw axes, this can be optionally called outside of Render function, this relies on active object matrix which can be set using 'SetMatrix' function

   Matrix() {}
   Matrix(  Flt      scale                  ) {setScale   (scale       );}
   Matrix(C Vec     &pos                    ) {setPos     (pos         );}
   Matrix(C Vec     &pos  ,   Flt      scale) {setPosScale(pos  , scale);}
   Matrix(  Flt      scale, C Vec     &pos  ) {setScalePos(scale, pos  );}
   Matrix(C Vec     &scale, C Vec     &pos  ) {setScalePos(scale, pos  );}
   Matrix(C Matrix3 &orn  , C Vec     &pos  ) {T.orn()=orn;    T.pos=pos;}
   Matrix(C Vec     &pos  , C Matrix3 &orn  ) {T.orn()=orn;    T.pos=pos;}
   Matrix(C Matrix3 &m);
   Matrix(C MatrixD &m);
   Matrix(C Matrix4 &m);
   Matrix(C OrientP &o);
};extern const Matrix
   MatrixIdentity; // identity
/******************************************************************************/
STRUCT(MatrixD , MatrixD3) // Matrix 4x3 (orientation + scale + position, double precision)
//{
   VecD pos; // position

   MatrixD3& orn()  {return T;} // get reference to self as       MatrixD3
 C MatrixD3& orn()C {return T;} // get reference to self as const MatrixD3

   // transform
          MatrixD& operator+=(C VecD2    &v) {pos.v2()+=v; return T;}
          MatrixD& operator-=(C VecD2    &v) {pos.v2()-=v; return T;}
          MatrixD& operator+=(C VecD     &v) {pos     +=v; return T;}
          MatrixD& operator-=(C VecD     &v) {pos     -=v; return T;}
          MatrixD& operator*=(  Dbl       f);
          MatrixD& operator/=(  Dbl       f);
          MatrixD& operator*=(C VecD     &v);
          MatrixD& operator/=(C VecD     &v);
          MatrixD& operator+=(C MatrixD  &m);
          MatrixD& operator-=(C MatrixD  &m);
          MatrixD& operator*=(C MatrixD3 &m) {return mul(m);}
          MatrixD& operator*=(C MatrixD  &m) {return mul(m);}
          MatrixD& operator/=(C MatrixD3 &m) {return div(m);}
          MatrixD& operator/=(C MatrixD  &m) {return div(m);}

   friend MatrixD  operator+ (C MatrixD  &m, C VecD2    &v) {return MatrixD(m)+=v;}
   friend MatrixD  operator- (C MatrixD  &m, C VecD2    &v) {return MatrixD(m)-=v;}
   friend MatrixD  operator+ (C MatrixD  &m, C VecD     &v) {return MatrixD(m)+=v;}
   friend MatrixD  operator- (C MatrixD  &m, C VecD     &v) {return MatrixD(m)-=v;}
   friend MatrixD  operator* (C MatrixD  &a, C MatrixD3 &b) {MatrixD temp; a.mul    (b, temp); return temp;} // get a*b
   friend MatrixD  operator* (C MatrixD  &a, C MatrixD  &b) {MatrixD temp; a.mul    (b, temp); return temp;} // get a*b
   friend MatrixD  operator/ (C MatrixD  &a, C MatrixD3 &b) {MatrixD temp; a.div    (b, temp); return temp;} // get a/b
   friend MatrixD  operator/ (C MatrixD  &a, C MatrixD  &b) {MatrixD temp; a.div    (b, temp); return temp;} // get a/b
   friend MatrixD  operator~ (C MatrixD  &m               ) {MatrixD temp; m.inverse(   temp); return temp;} // get inversed 'm'

   void     mul(C MatrixD3 &matrix, MatrixD &dest)C;                           // multiply self by 'matrix' and store result into 'dest'
   void     mul(C MatrixD  &matrix, MatrixD &dest)C;                           // multiply self by 'matrix' and store result into 'dest'
   MatrixD& mul(C MatrixD  &matrix               ) {mul(matrix, T); return T;} // multiply self by 'matrix'
   MatrixD& mul(C MatrixD3 &matrix               ) {mul(matrix, T); return T;} // multiply self by 'matrix'

   void     div(C MatrixD3 &matrix, MatrixD &dest, Bool normalized=false)C;                                       // divide self by 'matrix' and store result in 'dest', if you know that 'matrix' is normalized then set 'normalized=true' for more performance
   void     div(C MatrixD  &matrix, MatrixD &dest, Bool normalized=false)C;                                       // divide self by 'matrix' and store result in 'dest', if you know that 'matrix' is normalized then set 'normalized=true' for more performance
   MatrixD& div(C MatrixD3 &matrix               , Bool normalized=false) {div(matrix, T, normalized); return T;} // divide self by 'matrix'                           , if you know that 'matrix' is normalized then set 'normalized=true' for more performance
   MatrixD& div(C MatrixD  &matrix               , Bool normalized=false) {div(matrix, T, normalized); return T;} // divide self by 'matrix'                           , if you know that 'matrix' is normalized then set 'normalized=true' for more performance

   MatrixD& inverse(MatrixD &dest, Bool normalized=false)C;                                   // inverse self to 'dest', if you know that the matrix is normalized then set 'normalized=true' for more performance !! returns 'dest' !!
   MatrixD& inverse(               Bool normalized=false) {inverse(T, normalized); return T;} // inverse self          , if you know that the matrix is normalized then set 'normalized=true' for more performance

   MatrixD& normalize(             ) {super::normalize(     ); return T;} // normalize scale           , this sets the length of 'x' 'y' 'z' vectors to 'scale'
   MatrixD& normalize(  Dbl   scale) {super::normalize(scale); return T;} // normalize scale to 'scale', this sets the length of 'x' 'y' 'z' vectors to 'scale'
   MatrixD& normalize(C VecD &scale) {super::normalize(scale); return T;} // normalize scale to 'scale', this sets the length of 'x' 'y' 'z' vectors to 'scale.x' 'scale.y' 'scale.z'

   MatrixD& move(Dbl x, Dbl y, Dbl z) {T+=VecD(x, y, z); return T;} // move
   MatrixD& move(C VecD2 &move      ) {T+=move         ; return T;} // move
   MatrixD& move(C VecD  &move      ) {T+=move         ; return T;} // move

   MatrixD& scale     (               Dbl   scale) {          T*=scale ; return T;} // scale
   MatrixD& scale     (             C VecD &scale) {          T*=scale ; return T;} // scale
   MatrixD& scaleOrn  (               Dbl   scale) {super::scale(scale); return T;} // scale orientation only
   MatrixD& scaleOrn  (             C VecD &scale) {super::scale(scale); return T;} // scale orientation only
   MatrixD& scale     (C VecD &dir,   Dbl   scale);                                 // scale along       'dir' direction by 'scale' value, 'dir' must be normalized
   MatrixD& scalePlane(C VecD &nrm,   Dbl   scale);                                 // scale along plane of 'nrm' normal by 'scale' value, 'nrm' must be normalized

   MatrixD& rotateX (              Dbl angle);                                    // rotate by x axis
   MatrixD& rotateY (              Dbl angle);                                    // rotate by y axis
   MatrixD& rotateZ (              Dbl angle);                                    // rotate by z axis
   MatrixD& rotateXY(  Dbl   x   , Dbl y    );                                    // rotate by x axis and then by y axis, works the same as rotateX(x).rotateY(y) but faster
   MatrixD& rotate  (C VecD &axis, Dbl angle);                                    // rotate by vector, 'axis' must be normalized
   MatrixD& rotateXL(              Dbl angle) {super::rotateXL(angle); return T;} // rotate matrix by its x vector (x-axis rotation in local space)
   MatrixD& rotateYL(              Dbl angle) {super::rotateYL(angle); return T;} // rotate matrix by its y vector (y-axis rotation in local space)
   MatrixD& rotateZL(              Dbl angle) {super::rotateZL(angle); return T;} // rotate matrix by its z vector (z-axis rotation in local space)

   MatrixD& mirrorX(               ); // mirror matrix in X axis
   MatrixD& mirrorY(               ); // mirror matrix in Y axis
   MatrixD& mirrorZ(               ); // mirror matrix in Z axis
   MatrixD& mirror (C PlaneD &plane); // mirror matrix by   plane

   // set (set methods reset the full matrix)
   MatrixD& identity(); // set as identity
   MatrixD& zero    (); // set all vectors to zero

   MatrixD& setPos     (C VecD2 &pos                 ); // set as positioned identity
   MatrixD& setPos     (C VecD  &pos                 ); // set as positioned identity
   MatrixD& setScale   (  Dbl    scale               ); // set as scaled     identity
   MatrixD& setScale   (C VecD  &scale               ); // set as scaled     identity
   MatrixD& setPosScale(C VecD  &pos  ,   Dbl   scale); // set as positioned & scaled identity
   MatrixD& setPosScale(C VecD  &pos  , C VecD &scale); // set as positioned & scaled identity
   MatrixD& setScalePos(  Dbl    scale, C VecD &pos  ); // set as scaled & positioned identity
   MatrixD& setScalePos(C VecD  &scale, C VecD &pos  ); // set as scaled & positioned identity

   MatrixD& setRotateX (              Dbl angle); // set as   x-rotated identity
   MatrixD& setRotateY (              Dbl angle); // set as   y-rotated identity
   MatrixD& setRotateZ (              Dbl angle); // set as   z-rotated identity
   MatrixD& setRotateXY(  Dbl   x   , Dbl y    ); // set as x-y-rotated identity, works the same as setRotateX(x).rotateY(y) but faster
   MatrixD& setRotate  (C VecD &axis, Dbl angle); // set as     rotated by vector identity, 'axis' must be normalized

   MatrixD& setPosOrient(C VecD &pos,   DIR_ENUM dir                        ); // set as positioned orientation from DIR_ENUM
   MatrixD& setPosRight (C VecD &pos, C VecD &right                         ); // set as pos='pos', x='right'       and calculate correct y,z, 'right'        must be normalized
   MatrixD& setPosUp    (C VecD &pos, C VecD &up                            ); // set as pos='pos', y='up'          and calculate correct x,z, 'up'           must be normalized
   MatrixD& setPosDir   (C VecD &pos, C VecD &dir                           ); // set as pos='pos', z='dir'         and calculate correct x,y, 'dir'          must be normalized
   MatrixD& setPosDir   (C VecD &pos, C VecD &dir, C VecD &up               ); // set as pos='pos', z='dir', y='up' and calculate correct x  , 'dir up'       must be normalized
   MatrixD& setPosDir   (C VecD &pos, C VecD &dir, C VecD &up, C VecD &right); // set as pos='pos', z='dir', y='up', x='right'               , 'dir up right' must be normalized
   MatrixD& setRotation (C VecD &pos, C VecD &dir_from, C VecD &dir_to, Dbl blend=1, Dbl roll=0); // set as matrix which rotates 'dir_from' into 'dir_to', using blend value and additional roll angle, 'dir_from dir_to' must be normalized

   // get
   Vec scale()C {return super::scale();} // get each axis scale

   Str asText(Int precision=INT_MAX)C {return super::asText(precision)+", Pos: "+pos.asText(precision);} // get text description

   // operations

   MatrixD& setTransformAtPos(C VecD &pos, C MatrixD3 &matrix) {return setPos(-pos).mul(matrix).move(pos);} // set as transformation at position
   MatrixD& setTransformAtPos(C VecD &pos, C MatrixD  &matrix) {return setPos(-pos).mul(matrix).move(pos);} // set as transformation at position
   MatrixD&    transformAtPos(C VecD &pos, C MatrixD3 &matrix) {return move  (-pos).mul(matrix).move(pos);} //        transform      at position
   MatrixD&    transformAtPos(C VecD &pos, C MatrixD  &matrix) {return move  (-pos).mul(matrix).move(pos);} //        transform      at position

   // draw
   void draw(C Color &x_color=RED, C Color &y_color=GREEN, C Color &z_color=BLUE, Bool arrow=true)C {super::draw(pos, x_color, y_color, z_color, arrow);} // draw axes, this can be optionally called outside of Render function, this relies on active object matrix which can be set using 'SetMatrix' function

   MatrixD() {}
   MatrixD(  Dbl       scale                   ) {setScale   (scale       );}
   MatrixD(C VecD     &pos                     ) {setPos     (pos         );}
   MatrixD(C VecD     &pos  ,   Dbl       scale) {setPosScale(pos  , scale);}
   MatrixD(  Dbl       scale, C VecD     &pos  ) {setScalePos(scale, pos  );}
   MatrixD(C VecD     &scale, C VecD     &pos  ) {setScalePos(scale, pos  );}
   MatrixD(C MatrixD3 &orn  , C VecD     &pos  ) {T.orn()=orn;    T.pos=pos;}
   MatrixD(C VecD     &pos  , C MatrixD3 &orn  ) {T.orn()=orn;    T.pos=pos;}
   MatrixD(C MatrixD3 &m);
   MatrixD(C Matrix   &m);
};
/******************************************************************************/
struct Matrix4 // Matrix 4x4
{
   Vec4 x, y, z, pos;

   // transform
          Matrix4& operator*=(C Matrix4 &m) {return mul(m);}

   friend Matrix4  operator* (C Matrix4 &a, C Matrix4 &b) {Matrix4 temp; a.mul(b, temp); return temp;} // get a*b
   friend Matrix4  operator* (C Matrix  &a, C Matrix4 &b) {Matrix4 temp; a.mul(b, temp); return temp;} // get a*b

   Matrix4& inverse(); // inverse self

   void     mul(C Matrix4 &matrix, Matrix4 &dest)C;                           // multiply self by 'matrix' and store result in 'dest' 
   Matrix4& mul(C Matrix4 &matrix               ) {mul(matrix, T); return T;} // multiply self by 'matrix'

   // set (set methods reset the full matrix)
   Matrix4& identity(); // set as identity
   Matrix4& zero    (); // set all vectors to zero
   
   Matrix4() {}
   Matrix4(C Matrix3 &m);
   Matrix4(C Matrix  &m);
};
/******************************************************************************/
Bool Equal(C Matrix3 &a, C Matrix3 &b, Flt eps=EPS                 );
Bool Equal(C Matrix  &a, C Matrix  &b, Flt eps=EPS, Flt pos_eps=EPS);
Bool Equal(C Matrix4 &a, C Matrix4 &b, Flt eps=EPS                 );

Matrix3 GetTransform(C Matrix3 &start, C Matrix3 &result); // get 'transform' matrix that transforms 'start' into 'result' according to following formula "start*transform=result"
Matrix  GetTransform(C Matrix  &start, C Matrix  &result); // get 'transform' matrix that transforms 'start' into 'result' according to following formula "start*transform=result"

void GetVel(Vec &vel, Vec &ang_vel, C Matrix &from, C Matrix &to, Flt dt=Time.d()); // get linear velocity and angular velocity from 'from' and 'to' matrixes using 'dt' time delta !! matrixes must be normalized !!

void SetMatrix(C Matrix &matrix=MatrixIdentity); // set active object rendering matrix
/******************************************************************************/

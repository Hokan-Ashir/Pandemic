/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Frustum' to detect shapes visibility according to the camera's viewing frustum.

   Sample Usage:

      Ball ball;
      if(Frustum(ball)).. // if ball is visible in current frustum

/******************************************************************************/
struct FrustumClass // Frustum
{
   // if shape intersects with frustum (these methods should be used everywhere except stencil shadow rendering mode RM_STENCIL_SHADOW)
   Bool operator()(C Vec     &point                      )C;
   Bool operator()(C Ball    &ball                       )C;
   Bool operator()(C Capsule &capsule                    )C;
   Bool operator()(C Box     &box                        )C;
   Bool operator()(C Box     &box, C Matrix &matrix      )C; // 'box' transformed by 'matrix'
   Bool operator()(C Box     &box,   Bool   &fully_inside)C; // 'fully_inside'=after this function returns this will be set to if the 'box' is fully inside the frustum
   Bool operator()(C OBox    &obox                       )C;
   Bool operator()(C Shape   &shape                      )C;
   Bool operator()(C Shape   *shape, Int shapes          )C;

   // if shape can be drawn in stencil shadow rendering mode (these methods should be used only in stencil shadow rendering mode RM_STENCIL_SHADOW)
   Bool stencilShadow(C Vec     &point                )C;
   Bool stencilShadow(C Ball    &ball                 )C;
   Bool stencilShadow(C Capsule &capsule              )C;
   Bool stencilShadow(C Box     &box                  )C;
   Bool stencilShadow(C Box     &box, C Matrix &matrix)C;
   Bool stencilShadow(C OBox    &obox                 )C;
   Bool stencilShadow(C Shape   &shape                )C;
   Bool stencilShadow(C Shape   *shape, Int shapes    )C;

private:
   Vec    point[ 8]; Int points;
   VecI2  edge [12]; Int edges ;
   Bool   persp, use_extra_plane;
   Flt    range, eye;
   Vec2   fov, fov_cos;
   Vec    size, plane_n_abs[DIRE_NUM], extra_plane_n_abs;
   Plane  plane[DIRE_NUM], extra_plane;
   Matrix matrix;
};extern FrustumClass
   Frustum; // Active Frustum
/******************************************************************************/

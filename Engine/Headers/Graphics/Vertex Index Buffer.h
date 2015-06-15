/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'VI' vertex index buffer for drawing simple 2D or 3D buffered graphics.

/******************************************************************************/
struct Vtx2DTex
{
   Vec2 pos, tex;
};
struct Vtx2DTexCol
{
   Vec2  pos, tex;
   Color color;
};
struct Vtx3DTex
{
   Vec  pos;
   Vec2 tex;
};
struct Vtx3DTexCol
{
   Vec   pos;
   Vec2  tex;
   Color color;
};
struct Vtx3DSimple
{
   Vec   pos, nrm;
   Vec2  tex;
   Color color;
};
struct Vtx3DStandard
{
   Vec   pos, nrm;
   Vec4  tan; // tan.xyz=tangent, tan.w=binormal direction (should be -1 or +1)
   Vec2  tex;
   Color color;

   void setNrmTan(C Vec &nrm, C Vec &tan            ) {T.nrm=nrm; T.tan.set(tan,                                 +1     );} // set normal tangent binormal from 'normal' 'tangent'           , this method is faster, use it when you don't use mirroring in uv mapping or you don't use binormal in the shader at all
   void setNrmTan(C Vec &nrm, C Vec &tan, C Vec &bin) {T.nrm=nrm; T.tan.set(tan, (Dot(Cross(nrm, tan), bin)>0) ? +1 : -1);} // set normal tangent binormal from 'normal' 'tangent' 'binormal'
};
/******************************************************************************/
struct VtxIndBuf // Vertex Index Buffer - used for buffered drawing
{
   // operations
   static void shader    (ShaderTech *shader); // set custom shader
   static void image     (C Image    *image ); // set texture
   static void color     (C Color    &color ); // set color
   static void color2    (C Color    &color ); // set color2
   static void cull      (Bool        cull  ); // set face  culling
   static void depthWrite(Bool        on    ); // set depth writing (this will affect only drawing that normally uses depth buffer)
   static void alphaTest (Bool        on    ); // set alpha testing (currently this is supported only for drawing faces using 'Vtx3DTex' and 'Vtx3DTexCol' as parameters)
   static void fog       (Bool        on    ); // set fog   usage   (currently this is supported only for drawing faces using 'Vtx3DTex' and 'Vtx3DTexCol' as parameters), if this is enabled then any current 'Fog' will affect the face colors
   static void wrap      (                  ); // set texture addressing to (X:wrap , Y:wrap )
   static void wrapX     (                  ); // set texture addressing to (X:wrap , Y:clamp)
   static void wrapY     (                  ); // set texture addressing to (X:clamp, Y:wrap )
   static void flush     (                  ); // flush queued data, calling this method is optional as 'end' method will automatically call it, you can call this method during drawing before changing some shader parameters
   static void end       (                  ); // flush and finish drawing, this must be called after each series of drawing

   // draw dots
   static void dot(                C Vec2 &pos, Flt r=0.007f); // this uses 'VI.color'
   static void dot(                C Vec  &pos, Flt r=0.007f); // this uses 'VI.color'
   static void dot(C Color &color, C Vec2 &pos, Flt r=0.007f);
   static void dot(C Color &color, C Vec  &pos, Flt r=0.007f);

   // draw rectangles
   static void rect(                C Rect &rect); // this uses 'VI.color'
   static void rect(C Color &color, C Rect &rect);

   // draw non-filled rectangles (lines only)
   static void rectL(                C Rect &rect); // this uses 'VI.color'
   static void rectL(C Color &color, C Rect &rect);

   // draw shaded rectangles
   static void rectShadedX(C Color &color0, C Color &color1, C Rect &rect); // shaded horizontally
   static void rectShadedY(C Color &color0, C Color &color1, C Rect &rect); // shaded   vertically

   // draw lines
   static void line(                                C Vec2 &a, C Vec2 &b           ); // this uses 'VI.color'
   static void line(                                C Vec2 &a, C Vec2 &b, Flt width); // this uses 'VI.color'
   static void line(                                C Vec  &a, C Vec  &b           ); // this uses 'VI.color'
   static void line(C Color &color,                 C Vec2 &a, C Vec2 &b           ); // this uses 'VI.color'
   static void line(C Color &color,                 C Vec  &a, C Vec  &b           ); // this uses 'VI.color'
   static void line(C Color &col_a, C Color &col_b, C Vec2 &a, C Vec2 &b           ); // this uses 'VI.color'
   static void line(C Color &col_a, C Color &col_b, C Vec  &a, C Vec  &b           ); // this uses 'VI.color'

   // draw triangles
   static void tri(                                                C Tri2 &tri                    ); // this uses 'VI.color'
   static void tri(                                                C Tri  &tri                    ); // this uses 'VI.color'
   static void tri(                                                C Vec2 &a, C Vec2 &b, C Vec2 &c); // this uses 'VI.color'
   static void tri(                                                C Vec  &a, C Vec  &b, C Vec  &c); // this uses 'VI.color'
   static void tri(C Color &color,                                 C Vec2 &a, C Vec2 &b, C Vec2 &c);
   static void tri(C Color &color,                                 C Vec  &a, C Vec  &b, C Vec  &c);
   static void tri(C Color &col_a, C Color &col_b, C Color &col_c, C Vec2 &a, C Vec2 &b, C Vec2 &c);
   static void tri(C Color &col_a, C Color &col_b, C Color &col_c, C Vec  &a, C Vec  &b, C Vec  &c);

   // draw quads
   static void quad(                               C Quad2 &quad                             ); // this uses 'VI.color'
   static void quad(                               C Quad  &quad                             ); // this uses 'VI.color'
   static void quad(C Color &color,                C Quad2 &quad                             );
   static void quad(C Color &color,                C Quad  &quad                             );
   static void quad(                               C Vec2 &a, C Vec2 &b, C Vec2 &c, C Vec2 &d); // this uses 'VI.color'
   static void quad(                               C Vec  &a, C Vec  &b, C Vec  &c, C Vec  &d); // this uses 'VI.color'
   static void quad(C Color &color,                C Vec2 &a, C Vec2 &b, C Vec2 &c, C Vec2 &d);
   static void quad(C Color &color,                C Vec  &a, C Vec  &b, C Vec  &c, C Vec  &d);
   static void quad(C Color &col0 , C Color &col1, C Vec2 &a, C Vec2 &b, C Vec2 &c, C Vec2 &d);
   static void quad(C Color &col0 , C Color &col1, C Vec  &a, C Vec  &b, C Vec  &c, C Vec  &d);

   // draw image
   static void image    (C Rect &screen_rect                  ); // this uses 'VI.color' and 'VI.color2' as "FinalColor = Image*color + color2"
   static void imagePart(C Rect &screen_rect, C Rect &tex_rect); // this uses 'VI.color' and 'VI.color2' as "FinalColor = Image*color + color2"

   // draw faces
   static void face(C Vtx2DTex &a, C Vtx2DTex &b, C Vtx2DTex &c);
   static void face(C Vtx2DTex &a, C Vtx2DTex &b, C Vtx2DTex &c, C Vtx2DTex &d);

   static void face(C Vtx2DTexCol &a, C Vtx2DTexCol &b, C Vtx2DTexCol &c);
   static void face(C Vtx2DTexCol &a, C Vtx2DTexCol &b, C Vtx2DTexCol &c, C Vtx2DTexCol &d);

   static void face(C Vtx3DTex &a, C Vtx3DTex &b, C Vtx3DTex &c);
   static void face(C Vtx3DTex &a, C Vtx3DTex &b, C Vtx3DTex &c, C Vtx3DTex &d);

   static void face(C Vtx3DTexCol &a, C Vtx3DTexCol &b, C Vtx3DTexCol &c);
   static void face(C Vtx3DTexCol &a, C Vtx3DTexCol &b, C Vtx3DTexCol &c, C Vtx3DTexCol &d);

   static void face(C Vtx3DSimple &a, C Vtx3DSimple &b, C Vtx3DSimple &c);
   static void face(C Vtx3DSimple &a, C Vtx3DSimple &b, C Vtx3DSimple &c, C Vtx3DSimple &d);

   static void face(C Vtx3DStandard &a, C Vtx3DStandard &b, C Vtx3DStandard &c);
   static void face(C Vtx3DStandard &a, C Vtx3DStandard &b, C Vtx3DStandard &c, C Vtx3DStandard &d);

private:
   Bool        _quad_ind, _depth_write;
   Byte        _vtx_type, _flag, _user_flag;
   Int         _mem_max,
               _vtx_queued, _vtx_drawing, _vtx_drawing_raw,
               _ind_div, _ind_sub;
   Color       _color;
 C Image      *_image;
   ShaderTech *_shader;
   Byte       *_vtx_buf;
   VtxFormat   _vf2D_flat, _vf2D_col, _vf2D_tex, _vf2D_tex_col, _vf2D_tex2, _vf2D_font, _vf3D_flat, _vf3D_col, _vf3D_tex, _vf3D_tex_col, _vf3D_bilb, _vf3D_bilb_anim, _vf3D_laser, _vf3D_simple, _vf3D_standard, _vf3D_cloth, _vf3D_soft_body, _vf3D_soft_body_tex, _vf3D_full, *_vf3D_shds, *_vf3D_shds_skin;
   VtxBuf      _vb;
   UInt        _prim_type;

   VtxIndBuf();
}extern
   VI; // Buffered Drawing
/******************************************************************************/

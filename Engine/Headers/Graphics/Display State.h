/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
enum ALPHA_MODE // Alpha Blending Modes
{
   ALPHA_NONE     , // Color:set     , Alpha:set
   ALPHA_BLEND    , // Color:blend   , Alpha:increase
   ALPHA_BLEND_DEC, // Color:blend   , Alpha:decrease
   ALPHA_ADD      , // Color:add     , Alpha:add
   ALPHA_MUL      , // Color:multiply, Alpha:multiply

   ALPHA_MERGE        , // Color:blend alpha premultiplied, Alpha:increase
   ALPHA_ADDBLEND_KEEP, // Color:add blended              , Alpha:keep
   ALPHA_ADD_KEEP     , // Color:add                      , Alpha:keep
   ALPHA_BLEND_FACTOR , // Color:blend                    , Alpha:blend with factor
   ALPHA_ADD_FACTOR   , // Color:add                      , Alpha:add   with factor
};
/******************************************************************************/
struct DisplayState // Display States Control, this class methods can be called by the use of 'D' display object
{
          ALPHA_MODE alpha      (                    )C {return _alpha;} // get alpha blending mode
   static ALPHA_MODE alpha      (ALPHA_MODE alpha    );                  // set alpha blending mode and return previous mode
   static void       clip       (C Rect    *rect=NULL);                  // set rectangle clipping, NULL for none
   static void       clip       (C Rect    &rect     ) {clip(&rect);}    // set rectangle clipping
   static void       depthLock  (Bool       on       );                  // set    depth buffer usage and lock it
   static void       depthUnlock(                    );                  // unlock depth buffer usage
   static Bool       depthWrite (Bool       on       );                  // set    depth buffer writing and return previous state
   static Bool       lineSmooth (Bool       on       );                  // set line smoothing (anti-aliasing) and return previous state, enabling this option can significantly reduce performance of drawing lines, default=false

private:
   Enum1<ALPHA_MODE> _alpha;
   Bool  _depth_lock, _depth, _depth_write, _cull, _line_smooth, _wire, _clip, _clip_allow, _clip_real, _clip_plane_allow, _sampler2D;
   Byte  _col_write[4], _stencil, _stencil_ref, _bias;
   UInt  _depth_func, _sampler_filter[3], _sampler_address, _sample_mask, _fbo;
   RectI _viewport;
   Rect  _clip_rect;
   Color _alpha_factor;
   Vec4  _alpha_factor_v4, _clip_plane;
   Ptr   _vf;
protected:
   DisplayState();
};
/******************************************************************************/

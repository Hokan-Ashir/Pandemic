/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Image' for handling images (textures).

/******************************************************************************/
enum FILTER_TYPE // Filtering Type
{
   FILTER_NONE         , // 1.00 speed, worst  quality, uses 1x1 samples in 2D filtering
   FILTER_LINEAR       , // 0.48 speed, low    quality, uses 2x2 samples in 2D filtering
   FILTER_CUBIC_ORTHO  , // 0.17 speed, medium quality, uses 4x4 samples in 2D filtering, faster than FILTER_CUBIC   however it works in orthogonal mode which may result in blocky image
   FILTER_CUBIC        , // 0.12 speed, high   quality, uses 4x4 samples in 2D filtering
   FILTER_CUBIC_SHARP  , // 0.12 speed, high   quality, uses 4x4 samples in 2D filtering (best for down-scaling)
   FILTER_LANCZOS_ORTHO, // 0.02 speed, medium quality, uses 6x6 samples in 2D filtering, faster than FILTER_LANCZOS however it works in orthogonal mode which may result in blocky image
   FILTER_LANCZOS      , // 0.01 speed, high   quality, uses 6x6 samples in 2D filtering (best for   up-scaling)
   FILTER_BEST         , // automatically choose the best filter (currently FILTER_CUBIC_SHARP for down-scaling and FILTER_LANCZOS for up-scaling)
};
/******************************************************************************/
enum LOCK_MODE
{
   LOCK_READ      =1, // lock for reading only
   LOCK_WRITE     =2, // lock for writing only (if the image is stored in the GPU then any previous image data may get lost when using this mode, use if you wish to replace the whole image data)
   LOCK_READ_WRITE=3, // lock for reading and writing
};
/******************************************************************************/
enum IMAGE_TYPE // Image Type, comments specify in which mode the type is available (Soft:Software, DX9:DirectX9, DX10+:DirectX10+, GL:OpenGL-Mac, iOS:OpenGLES-iOS, Android:OpenGLES-Android, partial:may be supported on some devices but not on all of them)
{
   IMAGE_NONE, // none

   IMAGE_B8G8R8A8, // 32-bit (R,G,B,A), Soft, DX9, DX10+, GL, iOS, Android
   IMAGE_R8G8B8A8, // 32-bit (R,G,B,A), Soft,      DX10+, GL, iOS, Android
   IMAGE_R8G8B8  , // 24-bit (R,G,B,1), Soft
   IMAGE_R8G8    , // 16-bit (R,G,0,1), Soft,      DX10+, GL
   IMAGE_R8      , //  8-bit (R,0,0,1), Soft,      DX10+, GL

   IMAGE_A8  , //  8-bit alpha     (0,0,0,A), Soft, DX9, DX10+, GL, iOS, Android
   IMAGE_L8  , //  8-bit luminance (L,L,L,1), Soft, DX9,        GL, iOS, Android
   IMAGE_L8A8, // 16-bit           (L,L,L,A), Soft, DX9,        GL, iOS, Android

   IMAGE_DXT1, // DXT1 4-bit lossy RGBA compression with 1-bit  alpha            , Soft, DX9, DX10+, GL, partial Android
   IMAGE_DXT3, // DXT3 8-bit lossy RGBA compression with sharp  alpha transitions, Soft, DX9, DX10+, GL, partial Android
   IMAGE_DXT5, // DXT5 8-bit lossy RGBA compression with smooth alpha transitions, Soft, DX9, DX10+, GL, partial Android

   IMAGE_I8   , //      8-bit integer              , Soft
   IMAGE_I16  , //     16-bit integer              , Soft
   IMAGE_I24  , //     24-bit integer              , Soft
   IMAGE_I32  , //     32-bit integer              , Soft
   IMAGE_F16  , //     16-bit float                , Soft, DX9, DX10+, GL
   IMAGE_F32  , //     32-bit float                , Soft, DX9, DX10+, GL
   IMAGE_F16_2, // 2 x 16-bit float ( 32-bit total), Soft, DX9, DX10+, GL
   IMAGE_F32_2, // 2 x 32-bit float ( 64-bit total), Soft, DX9, DX10+, GL
   IMAGE_F16_3, // 3 x 16-bit float ( 48-bit total), Soft
   IMAGE_F32_3, // 3 x 32-bit float ( 96-bit total), Soft
   IMAGE_F16_4, // 4 x 16-bit float ( 64-bit total), Soft, DX9, DX10+, GL
   IMAGE_F32_4, // 4 x 32-bit float (128-bit total), Soft, DX9, DX10+, GL

   // compressed formats for iOS (compressing images to these formats is available only on Desktop platforms when 'SupportPVRTC' was called in 'InitPre', decompressing these formats is available on all platforms, GPU's that don't support these formats natively will keep them as B8G8R8A8 in the memory, decompression and especially compression may be slow, formats are recommended to be used only on iOS)
   IMAGE_PVRTC2, // PVRTC2 2-bit lossy RGBA compression, Soft, iOS, partial Android
   IMAGE_PVRTC4, // PVRTC4 4-bit lossy RGBA compression, Soft, iOS, partial Android

   // compressed format for Android (compressing and decompressing this format is available on all platforms, GPU's that don't support this format natively will keep it as B8G8R8A8 in the memory, decompression and especially compression may be slow, format is recommended to be used only on Android)
   IMAGE_ETC1, // Ericsson 4-bit lossy RGB compression with no Alpha (R,G,B,1), Soft, Android

   IMAGE_TYPES, // number of types
};
enum IMAGE_MODE // Image Mode
{
   IMAGE_2D  , // Hardware 2D   Texture
   IMAGE_3D  , // Hardware 3D   Texture (not supported on OpenGL ES)
   IMAGE_CUBE, // Hardware Cube Texture
   IMAGE_SOFT, // Software      Image   (this type is used for software processing only - it can't be drawn on the screen)
   IMAGE_RT  , // Hardware RenderTarget (only this mode can be used as custom rendering destination for 'Renderer.target', after you have rendered to this image you can treat it as typical IMAGE_2D texture, except that you can't lock it) !! Images of this mode must be deleted in a custom function set into 'D.lost' !!
};
/******************************************************************************/
struct ImageTypeInfo // Image Type Information
{
   CChar *name          ; // type name
   Bool   compressed    , // if the type is a compressed type
          high_precision; // if any channel uses more than 8-bits
   Byte   byte_pp       , // bytes per pixel
           bit_pp       , // bits  per pixel
          r             , // number of red     bits
          g             , // number of green   bits
          b             , // number of blue    bits
          a             , // number of alpha   bits
          d             , // number of depth   bits
          s             , // number of stencil bits
          channels      ; // number of channels

private:
   UInt format;
};extern const ImageTypeInfo
   ImageTI[]; // Image Type Info Array, allows obtaining information about specified IMAGE_TYPE, sample usage: ImageTI[IMAGE_B8G8R8A8].name -> "B8G8R8A8"
/******************************************************************************/
struct Image // Image (Texture)
{
   // get
   Int   w()C {return      _size.x;} // get width                              (in pixels)
   Int   h()C {return      _size.y;} // get height                             (in pixels)
   Int   d()C {return      _size.z;} // get depth                              (in pixels)
   Int  lw()C {return _lock_size.x;} // get width  of currently locked mip map (in pixels)
   Int  lh()C {return _lock_size.y;} // get height of currently locked mip map (in pixels)
   Int  ld()C {return _lock_size.z;} // get depth  of currently locked mip map (in pixels)
   Int hwW()C {return   _hw_size.x;} // get width  as it is stored on the GPU  (in pixels), this can be different than 'w' if the size is a non-power of 2, but the GPU does not support non-power of 2 textures, in which case the hardware size will be rounded up to the nearest power of 2
   Int hwH()C {return   _hw_size.y;} // get height as it is stored on the GPU  (in pixels), this can be different than 'h' if the size is a non-power of 2, but the GPU does not support non-power of 2 textures, in which case the hardware size will be rounded up to the nearest power of 2
   Int hwD()C {return   _hw_size.z;} // get depth  as it is stored on the GPU  (in pixels), this can be different than 'd' if the size is a non-power of 2, but the GPU does not support non-power of 2 textures, in which case the hardware size will be rounded up to the nearest power of 2

 C VecI2&   size ()C {return    _size.v2();} // get image size (in pixels)
 C VecI &   size3()C {return    _size     ;} // get image size (in pixels)
 C VecI2& hwSize ()C {return _hw_size.v2();} // get image size as it is stored on the GPU (in pixels)

   Bool         is   ()C {return _type!=IMAGE_NONE;} // if  valid
   IMAGE_TYPE   type ()C {return _type            ;} // get image  type
   IMAGE_TYPE hwType ()C {return _hw_type         ;} // get image  type in which it is stored on the GPU (this can be different than 'type' if it is not supported directly on the hardware, for example image was created as compressed format which the GPU does not support, 'type' will be set to the compressed format but 'hwType' may be set to B8G8R8A8 format as stored on the GPU)
   IMAGE_MODE mode   ()C {return _mode            ;} // get image  mode
   Int        mipMaps()C {return _mms             ;} // get number of mipmaps
   Byte       samples()C {return _samples         ;} // get number of samples per pixel
   Bool  multiSample ()C {return _samples>1       ;} // if  this   is a multi sampled image

   Int  lMipMap()C {return _lmm   ;} // get index              of locked mip map
   UInt  pitch ()C {return _pitch ;} // get width        pitch of locked mip map
   UInt  pitch2()C {return _pitch2;} // get width*height pitch of locked mip map
   Byte* data  ()C {return _data  ;} // get address            of locked data, memory accessed using this method should be interpreted according to 'hwType' (and not 'type')

   Flt     aspect    ()C {return Flt(w())/h()                    ;} // get          aspect ratio of image "width/height"
   Flt  invAspect    ()C {return Flt(h())/w()                    ;} // get inversed aspect ratio of image "height/width"
   UInt memUsage     ()C;                                           // get approximate memory size usage of the image
   Int  bytePP       ()C {return         _byte_pp                ;} // get number of bytes per pixel
   Bool compressed   ()C {return ImageTI[_hw_type].compressed    ;} // if hardware type is compressed
   Bool highPrecision()C {return ImageTI[_hw_type].high_precision;} // if any channel of the image uses more than 8-bits

   // manage
   Image& del          (                                                                                             );                                                                       // delete
   Bool   createTry    (Int w, Int h, Int d, IMAGE_TYPE type, IMAGE_MODE mode, Int mip_maps=0, Bool rgba_on_fail=true);                                                                       // create                 image, 'mip_maps'=number of mip-maps (0=autodetect), 'rgba_on_fail'=if try using uncompressed RGBA type if given 'type' is not supported, false on fail
   Image& create       (Int w, Int h, Int d, IMAGE_TYPE type, IMAGE_MODE mode, Int mip_maps=0, Bool rgba_on_fail=true);                                                                       // create                 image, 'mip_maps'=number of mip-maps (0=autodetect), 'rgba_on_fail'=if try using uncompressed RGBA type if given 'type' is not supported, Exit  on fail
   Bool   create2DTry  (Int w, Int h,        IMAGE_TYPE type,                  Int mip_maps=0, Bool rgba_on_fail=true) {return createTry(w, h, 1, type, IMAGE_2D  , mip_maps, rgba_on_fail);} // create hardware 2D   texture, 'mip_maps'=number of mip-maps (0=autodetect), 'rgba_on_fail'=if try using uncompressed RGBA type if given 'type' is not supported, false on fail
   Image& create2D     (Int w, Int h,        IMAGE_TYPE type,                  Int mip_maps=0, Bool rgba_on_fail=true) {return create   (w, h, 1, type, IMAGE_2D  , mip_maps, rgba_on_fail);} // create hardware 2D   texture, 'mip_maps'=number of mip-maps (0=autodetect), 'rgba_on_fail'=if try using uncompressed RGBA type if given 'type' is not supported, Exit  on fail
   Bool   create3DTry  (Int w, Int h, Int d, IMAGE_TYPE type,                  Int mip_maps=1, Bool rgba_on_fail=true) {return createTry(w, h, d, type, IMAGE_3D  , mip_maps, rgba_on_fail);} // create hardware 3D   texture, 'mip_maps'=number of mip-maps (0=autodetect), 'rgba_on_fail'=if try using uncompressed RGBA type if given 'type' is not supported, false on fail
   Image& create3D     (Int w, Int h, Int d, IMAGE_TYPE type,                  Int mip_maps=1, Bool rgba_on_fail=true) {return create   (w, h, d, type, IMAGE_3D  , mip_maps, rgba_on_fail);} // create hardware 3D   texture, 'mip_maps'=number of mip-maps (0=autodetect), 'rgba_on_fail'=if try using uncompressed RGBA type if given 'type' is not supported, Exit  on fail
   Bool   createCubeTry(Int w,               IMAGE_TYPE type,                  Int mip_maps=1, Bool rgba_on_fail=true) {return createTry(w, w, 1, type, IMAGE_CUBE, mip_maps, rgba_on_fail);} // create hardware cube texture, 'mip_maps'=number of mip-maps (0=autodetect), 'rgba_on_fail'=if try using uncompressed RGBA type if given 'type' is not supported, false on fail
   Image& createCube   (Int w,               IMAGE_TYPE type,                  Int mip_maps=1, Bool rgba_on_fail=true) {return create   (w, w, 1, type, IMAGE_CUBE, mip_maps, rgba_on_fail);} // create hardware cube texture, 'mip_maps'=number of mip-maps (0=autodetect), 'rgba_on_fail'=if try using uncompressed RGBA type if given 'type' is not supported, Exit  on fail
   Bool   createSoftTry(Int w, Int h, Int d, IMAGE_TYPE type                                                         ) {return createTry(w, h, d, type, IMAGE_SOFT,        1,        false);} // create software        image,                                                                                                                                    false on fail
   Image& createSoft   (Int w, Int h, Int d, IMAGE_TYPE type                                                         ) {return create   (w, h, d, type, IMAGE_SOFT,        1,        false);} // create software        image,                                                                                                                                    Exit  on fail

   Bool   copyTry(Image &dest, Int w=-1, Int h=-1, Int d=-1, Int type=-1, Int mode=-1, Int mip_maps=-1, FILTER_TYPE filter=FILTER_BEST, Bool clamp=true, Bool alpha_weight=false, Bool mtrl_base_1=false, Bool rgba_on_fail=true)C; // copy to 'dest', -1=keep original value, 'type'=IMAGE_TYPE, 'mode'=IMAGE_MODE (this method does not support IMAGE_3D), 'mip_maps'=number of mip-maps (0=autodetect), 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color, 'mtrl_base_1'=if this image is 'Material.base_1' texture, 'rgba_on_fail'=if try using uncompressed RGBA type if given 'type' is not supported, false on fail
   Image& copy   (Image &dest, Int w=-1, Int h=-1, Int d=-1, Int type=-1, Int mode=-1, Int mip_maps=-1, FILTER_TYPE filter=FILTER_BEST, Bool clamp=true, Bool alpha_weight=false, Bool mtrl_base_1=false, Bool rgba_on_fail=true)C; // copy to 'dest', -1=keep original value, 'type'=IMAGE_TYPE, 'mode'=IMAGE_MODE (this method does not support IMAGE_3D), 'mip_maps'=number of mip-maps (0=autodetect), 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color, 'mtrl_base_1'=if this image is 'Material.base_1' texture, 'rgba_on_fail'=if try using uncompressed RGBA type if given 'type' is not supported, Exit  on fail !! returns 'dest' !!

   Bool   toCube(C Image &src, Int size=-1, Int type=-1, FILTER_TYPE filter=FILTER_BEST); // convert from 6x1 'src' image                 (containing in order : left, front, right, back, down, up views) to cube texture, 'size'=desired resolution of the image (-1=keep), 'type'=IMAGE_TYPE (-1=keep), 'filter'=what kind of filtering to use when source is of different size than the target
   Bool fromCube(C Image &src,              Int type=-1, IMAGE_MODE  mode  =IMAGE_SOFT ); // convert from 'src' cube texture to 6x1 image (containing in order : left, front, right, back, down, up views)                ,                                                   'type'=IMAGE_TYPE (-1=keep), 'mode'=IMAGE_MODE

   // lock
   Bool     lock    (LOCK_MODE lock=LOCK_READ_WRITE, Int mip_map=0, DIR_ENUM cube_face=DIRE_RIGHT) ; //   lock image for editing specified 'mip_map', this needs to be called before manual setting/getting pixels/colors on hardware images (IMAGE_SOFT doesn't need locking), 'cube_face'=desired cube face (this is used only for IMAGE_CUBE modes)
   Bool     lockRead(                                Int mip_map=0, DIR_ENUM cube_face=DIRE_RIGHT)C; //   lock image for reading specified 'mip_map', this needs to be called before manual setting/getting pixels/colors on hardware images (IMAGE_SOFT doesn't need locking), 'cube_face'=desired cube face (this is used only for IMAGE_CUBE modes), this method has the same effect as calling "lock(LOCK_READ, mip_map, cube_face)", however unlike 'lock' method it has 'const' modifier and can be called on "const Image" objects
   Image& unlock    (                                                                            ) ; // unlock image                                , this needs to be called after  manual setting/getting pixels/colors on hardware images (IMAGE_SOFT doesn't need locking), if you want the mip maps to be updated according to any change applied during the lock then you must call 'updateMipMaps' after 'unlock'
 C Image& unlock    (                                                                            )C; // unlock image                                , this needs to be called after  manual setting/getting pixels/colors on hardware images (IMAGE_SOFT doesn't need locking), if you want the mip maps to be updated according to any change applied during the lock then you must call 'updateMipMaps' after 'unlock'

   Image& updateMipMaps(FILTER_TYPE filter=FILTER_BEST, Bool clamp=true, Bool alpha_weight=false, Bool increase_mip_alpha=false, Bool mtrl_base_1=false, Byte blur_range=0, Int blur_mip_size=256); // update mip maps basing on 0-th, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color, 'increase_mip_alpha'=if increase alpha channel for sequential mip maps, 'mtrl_base_1'=if this image is 'Material.base_1' texture, 'blur_range'=range of blurring (in pixels) applied to each sequential mip map, 'blur_mip_size'=size of mip map at which blurring is performed (mip maps with bigger size than this value will not be blurred)

   Image& freeOpenGLESData(); // this method is used only under OpenGL ES (on other platforms it is ignored), the method frees the software copy of the GPU data which increases available memory, however after calling this method the data can no longer be accessed on the CPU (can no longer be locked or saved to file)

   // pixel
   UInt  pixel (Int x, Int y)C;   void pixel (Int x, Int y,   UInt   pixel); // get/set pixel UInt value (these methods may not support all compressed types, instead try using 'copy' method first)
   Flt   pixelF(Int x, Int y)C;   void pixelF(Int x, Int y,   Flt    pixel); // get/set pixel Flt  value (these methods may not support all compressed types, instead try using 'copy' method first)
   Color color (Int x, Int y)C;   void color (Int x, Int y, C Color &color); // get/set color Byte color (these methods may not support all compressed types, instead try using 'copy' method first)
   Vec4  colorF(Int x, Int y)C;   void colorF(Int x, Int y, C Vec4  &color); // get/set color Flt  color (these methods may not support all compressed types, instead try using 'copy' method first)

   Flt pixelFLinear      (Flt x, Flt y, Bool clamp=true)C; // get pixel Flt with Linear             interpolation, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color (these methods may not support all compressed types, instead try using 'copy' method first)
   Flt pixelFCubicOrtho  (Flt x, Flt y, Bool clamp=true)C; // get pixel Flt with Cubic   orthogonal interpolation, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color (these methods may not support all compressed types, instead try using 'copy' method first)
   Flt pixelFCubic       (Flt x, Flt y, Bool clamp=true)C; // get pixel Flt with Cubic              interpolation, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color (these methods may not support all compressed types, instead try using 'copy' method first)
   Flt pixelFCubicSharp  (Flt x, Flt y, Bool clamp=true)C; // get pixel Flt with Cubic   sharp      interpolation, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color (these methods may not support all compressed types, instead try using 'copy' method first)
   Flt pixelFLanczosOrtho(Flt x, Flt y, Bool clamp=true)C; // get pixel Flt with Lanczos orthogonal interpolation, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color (these methods may not support all compressed types, instead try using 'copy' method first)
   Flt pixelFLanczos     (Flt x, Flt y, Bool clamp=true)C; // get pixel Flt with Lanczos            interpolation, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color (these methods may not support all compressed types, instead try using 'copy' method first)

   Vec4 colorFLinear      (Flt x, Flt y, Bool clamp=true, Bool alpha_weight=false)C; // get color Vec4 with Linear             interpolation, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color (these methods may not support all compressed types, instead try using 'copy' method first)
   Vec4 colorFCubicOrtho  (Flt x, Flt y, Bool clamp=true, Bool alpha_weight=false)C; // get color Vec4 with Cubic   orthogonal interpolation, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color (these methods may not support all compressed types, instead try using 'copy' method first)
   Vec4 colorFCubic       (Flt x, Flt y, Bool clamp=true, Bool alpha_weight=false)C; // get color Vec4 with Cubic              interpolation, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color (these methods may not support all compressed types, instead try using 'copy' method first)
   Vec4 colorFCubicSharp  (Flt x, Flt y, Bool clamp=true, Bool alpha_weight=false)C; // get color Vec4 with Cubic   sharp      interpolation, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color (these methods may not support all compressed types, instead try using 'copy' method first)
   Vec4 colorFLanczosOrtho(Flt x, Flt y, Bool clamp=true, Bool alpha_weight=false)C; // get color Vec4 with Lanczos orthogonal interpolation, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color (these methods may not support all compressed types, instead try using 'copy' method first)
   Vec4 colorFLanczos     (Flt x, Flt y, Bool clamp=true, Bool alpha_weight=false)C; // get color Vec4 with Lanczos            interpolation, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color (these methods may not support all compressed types, instead try using 'copy' method first)

   // pixel 3D
   UInt  pixel3D (Int x, Int y, Int z)C;   void pixel3D (Int x, Int y, Int z,   UInt   pixel); // get/set pixel 3D UInt value (these methods may not support all compressed types, instead try using 'copy' method first)
   Flt   pixel3DF(Int x, Int y, Int z)C;   void pixel3DF(Int x, Int y, Int z,   Flt    pixel); // get/set pixel 3D Flt  value (these methods may not support all compressed types, instead try using 'copy' method first)
   Color color3D (Int x, Int y, Int z)C;   void color3D (Int x, Int y, Int z, C Color &color); // get/set color 3D Byte color (these methods may not support all compressed types, instead try using 'copy' method first)
   Vec4  color3DF(Int x, Int y, Int z)C;   void color3DF(Int x, Int y, Int z, C Vec4  &color); // get/set color 3D Flt  color (these methods may not support all compressed types, instead try using 'copy' method first)

   Flt pixel3DFLinear (Flt x, Flt y, Flt z, Bool clamp=true)C; // get pixel 3D Flt with Linear  interpolation, 'clamp'=if use clamping when filtering pixels (these methods may not support all compressed types, instead try using 'copy' method first)
   Flt pixel3DFCubic  (Flt x, Flt y, Flt z, Bool clamp=true)C; // get pixel 3D Flt with Cubic   interpolation, 'clamp'=if use clamping when filtering pixels (these methods may not support all compressed types, instead try using 'copy' method first)
   Flt pixel3DFLanczos(Flt x, Flt y, Flt z, Bool clamp=true)C; // get pixel 3D Flt with Lanczos interpolation, 'clamp'=if use clamping when filtering pixels (these methods may not support all compressed types, instead try using 'copy' method first)

   Vec4 color3DFLinear (Flt x, Flt y, Flt z, Bool clamp=true)C; // get color 3D Vec4 with Linear  interpolation, 'clamp'=if use clamping when filtering pixels (these methods may not support all compressed types, instead try using 'copy' method first)
   Vec4 color3DFCubic  (Flt x, Flt y, Flt z, Bool clamp=true)C; // get color 3D Vec4 with Cubic   interpolation, 'clamp'=if use clamping when filtering pixels (these methods may not support all compressed types, instead try using 'copy' method first)
   Vec4 color3DFLanczos(Flt x, Flt y, Flt z, Bool clamp=true)C; // get color 3D Vec4 with Lanczos interpolation, 'clamp'=if use clamping when filtering pixels (these methods may not support all compressed types, instead try using 'copy' method first)

   // pixel area
   Vec4 areaColorAverage     (C Vec2 &pos, C Vec2 &size, Bool clamp=true, Bool alpha_weight=false)C; // get average color Vec4 of specified 'pos' position and 'size' coverage with Average            interpolation, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color (these methods may not support all compressed types, instead try using 'copy' method first)
   Vec4 areaColorLinear      (C Vec2 &pos, C Vec2 &size, Bool clamp=true, Bool alpha_weight=false)C; // get average color Vec4 of specified 'pos' position and 'size' coverage with Linear             interpolation, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color (these methods may not support all compressed types, instead try using 'copy' method first)
   Vec4 areaColorCubicOrtho  (C Vec2 &pos, C Vec2 &size, Bool clamp=true, Bool alpha_weight=false)C; // get average color Vec4 of specified 'pos' position and 'size' coverage with Cubic   orthogonal interpolation, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color (these methods may not support all compressed types, instead try using 'copy' method first)
   Vec4 areaColorCubic       (C Vec2 &pos, C Vec2 &size, Bool clamp=true, Bool alpha_weight=false)C; // get average color Vec4 of specified 'pos' position and 'size' coverage with Cubic              interpolation, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color (these methods may not support all compressed types, instead try using 'copy' method first)
   Vec4 areaColorCubicSharp  (C Vec2 &pos, C Vec2 &size, Bool clamp=true, Bool alpha_weight=false)C; // get average color Vec4 of specified 'pos' position and 'size' coverage with Cubic   sharp      interpolation, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color (these methods may not support all compressed types, instead try using 'copy' method first)
   Vec4 areaColorLanczosOrtho(C Vec2 &pos, C Vec2 &size, Bool clamp=true, Bool alpha_weight=false)C; // get average color Vec4 of specified 'pos' position and 'size' coverage with Lanczos orthogonal interpolation, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color (these methods may not support all compressed types, instead try using 'copy' method first)
   Vec4 areaColorLanczos     (C Vec2 &pos, C Vec2 &size, Bool clamp=true, Bool alpha_weight=false)C; // get average color Vec4 of specified 'pos' position and 'size' coverage with Lanczos            interpolation, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color (these methods may not support all compressed types, instead try using 'copy' method first)

   // operations
   Image& clear                (                                                                                                                                                          ) ; // clear to 0 (transparent black)
   Image& normalize            (               Bool red=true, Bool green=true, Bool blue=true, Bool alpha=true                                                                            ) ; // normalize selected components to 0..1 range
   Image& mulAdd               (               C Vec4 &mul, C Vec4 &add                                                                                                                   ) ; // transform color to "color*mul+add"
   Image& bumpToNormal         (  Image &dest, Flt  scale, Bool high_precision=false                                                                                                      )C; // convert bump map to normal map, 'scale'=bump scaling factor 0..Inf (default=16), 'high_precision'=if create signed float image type, or unsigned byte image type !! returns 'dest' !!
   Image& crop                 (  Image &dest, Int x, Int y, Int z, Int w, Int h, Int d                                                                                                   )C; // crop      image !! returns 'dest' !!
   Image& resize               (               Int w, Int h,        FILTER_TYPE filter=FILTER_BEST, Bool clamp=true, Bool alpha_weight=false, Bool keep_edges=false, Flt sharp_smooth=1.0f) ; // resize    image, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color, 'keep_edges'=if preserve the edges of the image, 'sharp_smooth'=factor affecting sharpness/smoothness (0..Inf, the closer to 0.0 then the sharper result, the bigger than 1.0 then the more blurry result, default=1.0)
   Image& resize3D             (               Int w, Int h, Int d, FILTER_TYPE filter=FILTER_BEST, Bool clamp=true, Bool alpha_weight=false, Bool keep_edges=false                       ) ; // resize 3D image, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color, 'keep_edges'=if preserve the edges of the image
   Image& mirrorX              (                                                                                                                                                          ) ; // mirror    image horizontally
   Image& mirrorY              (                                                                                                                                                          ) ; // mirror    image   vertically
   Image& alphaFromKey         (               C Color &key=PURPLE                                                                                                                        ) ; // transform to ((pixel color==key) ? (0, 0, 0, 0) : (r, g, b, 255))
   Image& alphaFromBrightness  (                                                                                                                                                          ) ; // transform to (r  , g  , b  , brightness)
   Image& divRgbByAlpha        (                                                                                                                                                          ) ; // transform to (r/a, g/a, b/a, a)
   Bool   getMinMaxAvg         (               Vec4 *min=NULL, Vec4 *max=NULL, Vec4 *avg=NULL                                                                                             )C; // get minimum, maximum and average color values in texture, false on fail
   Bool   extractMipMap        (  Image &dest, Int type, Int mode, Int mip_map, DIR_ENUM cube_face=DIRE_RIGHT                                                                             )C; // extract specified mipmap to   'dest' 0-th mipmap, false on fail, 'type'=IMAGE_TYPE (-1=keep), 'mode'=IMAGE_MODE (-1=keep)
   Bool    injectMipMap        (C Image &src ,                     Int mip_map, DIR_ENUM cube_face=DIRE_RIGHT, FILTER_TYPE filter=FILTER_BEST, Bool clamp=true, Bool mtrl_base_1=false    ) ; //  inject specified mipmap from 'src'  0-th mipmap, false on fail, 'filter'=what kind of filtering to use when source is of different size than the target, 'clamp'=if use clamping when filtering pixels, 'mtrl_base_1'=if this image is 'Material.base_1' texture
   Image& downSample           (               FILTER_TYPE filter=FILTER_BEST, Bool clamp=true, Bool alpha_weight=false, Bool increase_mip_alpha=false                                    ) ; // downsample to half resolution size, 'clamp'=if use clamping when filtering pixels, 'alpha_weight'=if use pixel's alpha for weight of pixel's color, 'increase_mip_alpha'=if increase alpha channel for sequential mip maps
   Image& averageX             (               Byte range, Bool clamp                                                                                                                     ) ; // horizontal average      , 'range'=range of blurring (in pixels)
   Image& averageY             (               Byte range, Bool clamp                                                                                                                     ) ; // vertical   average      , 'range'=range of blurring (in pixels)
   Image& averageZ             (               Byte range, Bool clamp                                                                                                                     ) ; // depth      average      , 'range'=range of blurring (in pixels)
   Image& average              (               Byte range, Bool clamp                                                                                                                     ) ; //            average      , 'range'=range of blurring (in pixels)
   Image& blurX                (               Byte range, Bool clamp                                                                                                                     ) ; // horizontal gaussian blur, 'range'=range of blurring (in pixels)
   Image& blurY                (               Byte range, Bool clamp                                                                                                                     ) ; // vertical   gaussian blur, 'range'=range of blurring (in pixels)
   Image& blurZ                (               Byte range, Bool clamp                                                                                                                     ) ; // depth      gaussian blur, 'range'=range of blurring (in pixels)
   Image& blur                 (               Byte range, Bool clamp                                                                                                                     ) ; //            gaussian blur, 'range'=range of blurring (in pixels)
   Image& sharpen              (               Flt  power, Byte range, Bool clamp, Bool blur                                                                                              ) ; // sharpen image, 'power'=0..Inf (default=1.0), 'range'=blurring range, 'clamp'=blurring clamp, 'blur'=if use blur or averaging
   Image& noise                (               Byte red  , Byte green, Byte blue , Byte alpha                                                                                             ) ; // add noise of selected scale per component to image
   Image& RGBToHSB             (                                                                                                                                                          ) ; // convert Red Green Blue image to Hue Saturation Brightness (Alpha will be kept)
   Image& HSBToRGB             (                                                                                                                                                          ) ; // convert Hue Saturation Brightness image to Red Green Blue (Alpha will be kept)
   Image& lumFromAlphaAndLight (               UInt light_dir, Flt density_factor=1                                                                                                       ) ; // set luminance of 3D texture from its voxels alpha and given light direction, 'light_dir'=DIR_FLAG
   Image& tile                 (               Int  range, Bool horizontally=true, Bool vertically=true                                                                                   ) ; // make tileable, 'range'=number of pixels to blend
   Image& minimum              (               Flt  distance                                                                                                                              ) ; // apply minimum filter, 'distance'=pixel range (0..1)
   Image& maximum              (               Flt  distance                                                                                                                              ) ; // apply maximum filter, 'distance'=pixel range (0..1)
   Image& transparentToNeighbor(                                                                                                                                                          ) ; // replace transparent pixels with neighbors
   Bool   getSameColorNeighbors(               Int x, Int y, Memp<VecI2> pixels, Bool diagonal=true                                                                                       )C; // get a list of all neighbor pixels   with the same color, 'diagonal'=if allow diagonal movements, false on fail
   Image& fill                 (               Int x, Int y, C Color    &color , Bool diagonal=true                                                                                       ) ; // fill image at specified coordinates with given    color, 'diagonal'=if allow diagonal movements

   Image& createShadow(C Image &src   , Int blur, Flt shadow_opacity=1.0f, Flt shadow_spread=0.0f, Bool border_padd=true                                                        ); // create shadow image IMAGE_A8 from 'src' alpha channel, 'blur'=blur range (in pixels), 'shadow_opacity'=shadow opacity (0..1), 'shadow_spread'=shadow spread (0..1)
   Image&  applyShadow(C Image &shadow,      C Color &shadow_color  =BLACK,                                               C VecI2 &offset=0, Int image_type=0, Bool combine=true); // apply  shadow image to self, 'offset'=offset in pixels where to apply the shadow, 'image_type'=IMAGE_TYPE (-1=keep, 0=autodetect), 'combine'=if combine on to the color map (if false then alpha will be set to shadow intensity)
   Image&    setShadow(                 Int blur, Flt shadow_opacity=1.0f, Flt shadow_spread=0.0f, Bool border_padd=true, C VecI2 &offset=0, Int image_type=0, Bool combine=true); // create shadow and apply to self

   Bool raycast(C Vec &start, C Vec &move, C Matrix *image_matrix=NULL, Flt *hit_frac=NULL, Vec *hit_pos=NULL, Flt precision=1.0f)C; // perform ray casting from 'start' position along 'move' vector, return true if collision encountered with the image, by default the Image is on XY plane with its pixel values extending it towards the Z axis, 'image_matrix'=image transformation matrix, 'hit_frac'=fraction of the movement where collision occurs, 'hit_pos'=position where collision occurs, 'precision'=affects number of pixels to advance in a single step (lower value makes calculations faster but less precise)

   // following methods do not check for coordinates being out of range, image type matching, and image being locked, use only if you know what you're doing!
   Byte & pixB (Int x, Int y) {return *(Byte *)(_data + x*SIZE(Byte ) + y*_pitch);}   Byte & pixB (C VecI2 &v) {return pixB (v.x, v.y);}
   UInt & pix  (Int x, Int y) {return *(UInt *)(_data + x*SIZE(UInt ) + y*_pitch);}   UInt & pix  (C VecI2 &v) {return pix  (v.x, v.y);}
   VecB4& pix4 (Int x, Int y) {return *(VecB4*)(_data + x*SIZE(VecB4) + y*_pitch);}   VecB4& pix4 (C VecI2 &v) {return pix4 (v.x, v.y);}
   Flt  & pixF (Int x, Int y) {return *(Flt  *)(_data + x*SIZE(Flt  ) + y*_pitch);}   Flt  & pixF (C VecI2 &v) {return pixF (v.x, v.y);}
   Vec2 & pixF2(Int x, Int y) {return *(Vec2 *)(_data + x*SIZE(Vec2 ) + y*_pitch);}   Vec2 & pixF2(C VecI2 &v) {return pixF2(v.x, v.y);}
   Vec  & pixF3(Int x, Int y) {return *(Vec  *)(_data + x*SIZE(Vec  ) + y*_pitch);}   Vec  & pixF3(C VecI2 &v) {return pixF3(v.x, v.y);}
   Vec4 & pixF4(Int x, Int y) {return *(Vec4 *)(_data + x*SIZE(Vec4 ) + y*_pitch);}   Vec4 & pixF4(C VecI2 &v) {return pixF4(v.x, v.y);}

   Byte & pixB (Int x, Int y, Int z) {return *(Byte *)(_data + x*SIZE(Byte ) + y*_pitch + z*_pitch2);}   Byte & pixB (C VecI &v) {return pixB (v.x, v.y, v.z);}
   UInt & pix  (Int x, Int y, Int z) {return *(UInt *)(_data + x*SIZE(UInt ) + y*_pitch + z*_pitch2);}   UInt & pix  (C VecI &v) {return pix  (v.x, v.y, v.z);}
   VecB4& pix4 (Int x, Int y, Int z) {return *(VecB4*)(_data + x*SIZE(VecB4) + y*_pitch + z*_pitch2);}   VecB4& pix4 (C VecI &v) {return pix4 (v.x, v.y, v.z);}
   Flt  & pixF (Int x, Int y, Int z) {return *(Flt  *)(_data + x*SIZE(Flt  ) + y*_pitch + z*_pitch2);}   Flt  & pixF (C VecI &v) {return pixF (v.x, v.y, v.z);}
   Vec2 & pixF2(Int x, Int y, Int z) {return *(Vec2 *)(_data + x*SIZE(Vec2 ) + y*_pitch + z*_pitch2);}   Vec2 & pixF2(C VecI &v) {return pixF2(v.x, v.y, v.z);}
   Vec  & pixF3(Int x, Int y, Int z) {return *(Vec  *)(_data + x*SIZE(Vec  ) + y*_pitch + z*_pitch2);}   Vec  & pixF3(C VecI &v) {return pixF3(v.x, v.y, v.z);}
   Vec4 & pixF4(Int x, Int y, Int z) {return *(Vec4 *)(_data + x*SIZE(Vec4 ) + y*_pitch + z*_pitch2);}   Vec4 & pixF4(C VecI &v) {return pixF4(v.x, v.y, v.z);}

 C Byte & pixB (Int x, Int y)C {return *(Byte *)(_data + x*SIZE(Byte ) + y*_pitch);}   C Byte & pixB (C VecI2 &v)C {return pixB (v.x, v.y);}
 C UInt & pix  (Int x, Int y)C {return *(UInt *)(_data + x*SIZE(UInt ) + y*_pitch);}   C UInt & pix  (C VecI2 &v)C {return pix  (v.x, v.y);}
 C VecB4& pix4 (Int x, Int y)C {return *(VecB4*)(_data + x*SIZE(VecB4) + y*_pitch);}   C VecB4& pix4 (C VecI2 &v)C {return pix4 (v.x, v.y);}
 C Flt  & pixF (Int x, Int y)C {return *(Flt  *)(_data + x*SIZE(Flt  ) + y*_pitch);}   C Flt  & pixF (C VecI2 &v)C {return pixF (v.x, v.y);}
 C Vec2 & pixF2(Int x, Int y)C {return *(Vec2 *)(_data + x*SIZE(Vec2 ) + y*_pitch);}   C Vec2 & pixF2(C VecI2 &v)C {return pixF2(v.x, v.y);}
 C Vec  & pixF3(Int x, Int y)C {return *(Vec  *)(_data + x*SIZE(Vec  ) + y*_pitch);}   C Vec  & pixF3(C VecI2 &v)C {return pixF3(v.x, v.y);}
 C Vec4 & pixF4(Int x, Int y)C {return *(Vec4 *)(_data + x*SIZE(Vec4 ) + y*_pitch);}   C Vec4 & pixF4(C VecI2 &v)C {return pixF4(v.x, v.y);}

   // warning: 'gather' methods are written for speed and not safety, they assume that image is locked and that offsets are in range, these methods set 'pixels/colors' array from image values, coordinates are specified in the 'offset' parameters
   void gather(Flt   *pixels, Int *x_offset, Int x_offsets, Int *y_offset, Int y_offsets)C;
   void gather(Color *colors, Int *x_offset, Int x_offsets, Int *y_offset, Int y_offsets)C;
   void gather(Vec4  *colors, Int *x_offset, Int x_offsets, Int *y_offset, Int y_offsets)C;
   void gather(Color *colors, Int *x_offset, Int x_offsets, Int *y_offset, Int y_offsets, Int *z_offset, Int z_offsets)C;
   void gather(Vec4  *colors, Int *x_offset, Int x_offsets, Int *y_offset, Int y_offsets, Int *z_offset, Int z_offsets)C;

   // fit
   Rect fit        (C Rect &rect, FIT_MODE fit=FIT_FULL)C {return Fit(   aspect(), rect, fit);} // get rectangle that can be used for drawing of the image to the 'rect' destination while preserving image proportions according to specified 'fit' mode
   Rect fitVertical(C Rect &rect, FIT_MODE fit=FIT_FULL)C {return Fit(invAspect(), rect, fit);} // get rectangle that can be used for drawing of the image to the 'rect' destination while preserving image proportions according to specified 'fit' mode

   // draw
   void draw        (                                    C Rect &rect)C;
   void draw        (C Color &color, C Color &color_add, C Rect &rect)C;
   void drawVertical(                                    C Rect &rect)C; // draw with texture coordinates in vertical mode
   void drawVertical(C Color &color, C Color &color_add, C Rect &rect)C; // draw with texture coordinates in vertical mode

   // draw to fit best in given space, while preserving image proportions
   void drawFit        (                                    C Rect &rect)C {return draw        (                  fit        (rect));}
   void drawFit        (C Color &color, C Color &color_add, C Rect &rect)C {return draw        (color, color_add, fit        (rect));}
   void drawFitVertical(C Color &color, C Color &color_add, C Rect &rect)C {return drawVertical(color, color_add, fitVertical(rect));}

   // draw to fullscreen
   void drawFs(                                                FIT_MODE fit=FIT_FULL, Int hq=-1)C; // draw to fullscreen, 'hq'=if use high quality filtering ('Image.drawHQ' will be used instead of 'Image.draw'), this parameter accepts following values: 'true'=enable HQ filtering, 'false'=disable HQ filtering, '-1'=autodetect HQ filtering usage basing on platform (Mobile platforms have it disabled while others have it enabled)
   void drawFs(C Color &color, C Color &color_add=TRANSPARENT, FIT_MODE fit=FIT_FULL, Int hq=-1)C; // draw to fullscreen, 'hq'=if use high quality filtering ('Image.drawHQ' will be used instead of 'Image.draw'), this parameter accepts following values: 'true'=enable HQ filtering, 'false'=disable HQ filtering, '-1'=autodetect HQ filtering usage basing on platform (Mobile platforms have it disabled while others have it enabled)

   // draw only part of the image
   void drawPart        (                                    C Rect &screen_rect, C Rect &tex_rect)C;
   void drawPart        (C Color &color, C Color &color_add, C Rect &screen_rect, C Rect &tex_rect)C;
   void drawPartVertical(                                    C Rect &screen_rect, C Rect &tex_rect)C; // draw with texture coordinates in vertical mode
   void drawPartVertical(C Color &color, C Color &color_add, C Rect &screen_rect, C Rect &tex_rect)C; // draw with texture coordinates in vertical mode

   // draw rotated
   void drawRotate(                                    C Vec2 &center, C Vec2 &size, Flt angle, C Vec2 *rotation_center=NULL)C;
   void drawRotate(C Color &color, C Color &color_add, C Vec2 &center, C Vec2 &size, Flt angle, C Vec2 *rotation_center=NULL)C;

   // draw masked
   void drawMask(C Color &color, C Color &color_add, C Rect &rect, C Image &mask, C Rect &mask_rect)C;

   // draw image as tiled background, 'tex_scale'=texture coordinates scaling
   void drawTile(                                    C Rect &rect, Flt tex_scale=1)C;
   void drawTile(C Color &color, C Color &color_add, C Rect &rect, Flt tex_scale=1)C;

   // draw image as rectangle's border
   void drawBorder(                                    C Rect &rect, Flt border=0.02f, Flt tex_scale=1, Flt tex_offset=0, Bool wrap_mode=false)C;
   void drawBorder(C Color &color, C Color &color_add, C Rect &rect, Flt border=0.02f, Flt tex_scale=1, Flt tex_offset=0, Bool wrap_mode=false)C;

   // draw stretched image from 3x3 parts
   void draw3x3        (C Color &color, C Color &color_add, C Rect &rect, Flt border_size, Flt tex_frac=0.25f)C; // 'color'=color that will be multiplied by the texture, 'color_add'=color that will be added to the texture using following formula "final_color = texture_color * color + color_add", 'rect'=screen rectangle at which the image will be drawn, 'border_size'=size of the border inside the screen 'rect' rectangle that will be drawn as image borders (this value should be less than rectangle dimensions), 'tex_frac'=fraction of the image texture that will be used for drawing the borders (this value should be in range of 0 .. 0.5)
   void draw3x3Vertical(C Color &color, C Color &color_add, C Rect &rect, Flt border_size, Flt tex_frac=0.25f)C; // 'color'=color that will be multiplied by the texture, 'color_add'=color that will be added to the texture using following formula "final_color = texture_color * color + color_add", 'rect'=screen rectangle at which the image will be drawn, 'border_size'=size of the border inside the screen 'rect' rectangle that will be drawn as image borders (this value should be less than rectangle dimensions), 'tex_frac'=fraction of the image texture that will be used for drawing the borders (this value should be in range of 0 .. 0.5), this function will draw with texture coordinates in vertical mode

   // draw with high quality filtering
   void drawHQ(                                    C Rect &rect)C; // this method will draw the image with high quality filtering, the pixel shader for this drawing is very expensive, therefore use it only if performance is not critical and just for few images (for example displaying a slideshow)
   void drawHQ(C Color &color, C Color &color_add, C Rect &rect)C; // this method will draw the image with high quality filtering, the pixel shader for this drawing is very expensive, therefore use it only if performance is not critical and just for few images (for example displaying a slideshow)

   // draw cube face
   void drawCubeFace(C Color &color, C Color &color_add, C Rect &rect, DIR_ENUM face)C;

   // draw in 3D space
   void draw3D(C Color &color, Flt size, Flt angle, C Vec &pos, ALPHA_MODE mode=ALPHA_BLEND_DEC)C; // draw as 3D billboard, this can be called in RM_BLEND mode or outside rendering function (in drawing function), this method supports only IMAGE_2D images, this relies on active object matrix which can be set using 'SetMatrix' function

   void drawVolume(C Color &color, C Color &color_add, C OBox &obox, Flt voxel_density_factor=0.01f, Flt precision=1.0f, Int min_steps=4, Int max_steps=64)C; // draw as 3D volumetric image, 'voxel_density_factor'=density factor of a single voxel (0..1), 'precision'=number of steps per voxel (0..Inf), 'min_steps max_steps'=minimum and maximum number of steps (2..512), this method can be called in RM_CLOUD or RM_BLEND rendering modes, this method supports only IMAGE_3D images

   // io
   void operator=(C Str  &name) ; // load, Exit  on fail
   Bool save     (C Str  &name)C; // save, false on fail
   Bool load     (C Str  &name) ; // load, false on fail
   Bool save     (  File &f   )C; // save, false on fail
   Bool load     (  File &f   ) ; // load, false on fail

   Bool   ImportTry(C Str  &name, Int type=-1, Int mode=-1, Int mip_maps=-1); // import GFX BMP PNG JPG WEBP TGA TIF DDS PSD ICO, 'type'=IMAGE_TYPE, 'mode'=IMAGE_MODE, 'mip_maps'=number of mip-maps (0=autodetect), -1=keep original value, false on fail
   Image& Import   (C Str  &name, Int type=-1, Int mode=-1, Int mip_maps=-1); // import GFX BMP PNG JPG WEBP TGA TIF DDS PSD ICO, 'type'=IMAGE_TYPE, 'mode'=IMAGE_MODE, 'mip_maps'=number of mip-maps (0=autodetect), -1=keep original value, Exit  on fail
   Bool   ImportTry(  File &f   , Int type=-1, Int mode=-1, Int mip_maps=-1); // import GFX BMP PNG JPG WEBP TGA TIF DDS PSD ICO, 'type'=IMAGE_TYPE, 'mode'=IMAGE_MODE, 'mip_maps'=number of mip-maps (0=autodetect), -1=keep original value, false on fail
   Image& Import   (  File &f   , Int type=-1, Int mode=-1, Int mip_maps=-1); // import GFX BMP PNG JPG WEBP TGA TIF DDS PSD ICO, 'type'=IMAGE_TYPE, 'mode'=IMAGE_MODE, 'mip_maps'=number of mip-maps (0=autodetect), -1=keep original value, Exit  on fail

   Bool Export(C Str &name, Flt rgb_quality=-1, Flt alpha_quality=-1, Flt compression_level=-1)C; // export according to extension, false on fail, 'rgb_quality'=color quality 0..1 (-1=default, 0=smallest size, 1=best quality), 'alpha_quality'=alpha quality 0..1 (-1=use 'rgb_quality', 0=smallest size, 1=best quality), 'compression_level'=0..1 (-1=default, 0=fast/biggest size, 1=slow/smallest size)

   Bool   ImportCubeTry(C Image &right, C Image &left, C Image &up, C Image &down, C Image &forward, C Image &back, Int type=-1, Int mip_maps=1, Bool resize_to_pow2=true, FILTER_TYPE filter=FILTER_BEST); // import                                          as cube texture, 'type'=IMAGE_TYPE (-1=keep original value), false on fail
   Bool   ImportCubeTry(C Str   &right, C Str   &left, C Str   &up, C Str   &down, C Str   &forward, C Str   &back, Int type=-1, Int mip_maps=1, Bool resize_to_pow2=true, FILTER_TYPE filter=FILTER_BEST); // import GFX BMP PNG JPG WEBP TGA TIF DDS PSD ICO as cube texture, 'type'=IMAGE_TYPE (-1=keep original value), false on fail
   Image& ImportCube   (C Str   &right, C Str   &left, C Str   &up, C Str   &down, C Str   &forward, C Str   &back, Int type=-1, Int mip_maps=1, Bool resize_to_pow2=true, FILTER_TYPE filter=FILTER_BEST); // import GFX BMP PNG JPG WEBP TGA TIF DDS PSD ICO as cube texture, 'type'=IMAGE_TYPE (-1=keep original value), Exit  on fail

   Bool ImportBMP (C Str  &name                                          ) ; // import    BMP  from file, false on fail
   Bool ImportBMP (  File &f                                             ) ; // import    BMP  from file, false on fail
   Bool ExportBMP (C Str  &name                                          )C; // export as BMP  to   file, false on fail
   Bool ExportBMP (  File &f                                             )C; // export as BMP  to   file, false on fail
   Bool ImportPNG (C Str  &name                                          ) ; // import    PNG  from file, false on fail
   Bool ImportPNG (  File &f                                             ) ; // import    PNG  from file, false on fail
   Bool ExportPNG (C Str  &name, Flt compression_level=-1                )C; // export as PNG  to   file, false on fail, 'compression_level'=0..1 (-1=default, 0=fast/biggest size, 1=slow/smallest size)
   Bool ExportPNG (  File &f   , Flt compression_level=-1                )C; // export as PNG  to   file, false on fail, 'compression_level'=0..1 (-1=default, 0=fast/biggest size, 1=slow/smallest size)
   Bool ImportJPG (C Str  &name                                          ) ; // import    JPG  from file, false on fail
   Bool ImportJPG (  File &f                                             ) ; // import    JPG  from file, false on fail
   Bool ExportJPG (C Str  &name, Flt quality=-1                          )C; // export as JPG  to   file, false on fail, 'quality'=0..1 (-1=default, 0=smallest size, 1=best quality)
   Bool ExportJPG (  File &f   , Flt quality=-1                          )C; // export as JPG  to   file, false on fail, 'quality'=0..1 (-1=default, 0=smallest size, 1=best quality)
   Bool ImportWEBP(C Str  &name                                          ) ; // import    WEBP from file, false on fail
   Bool ImportWEBP(  File &f                                             ) ; // import    WEBP from file, false on fail
   Bool ExportWEBP(C Str  &name, Flt rgb_quality=-1, Flt alpha_quality=-1)C; // export as WEBP to   file, false on fail, 'rgb_quality'=color quality 0..1 (-1=default, 0=smallest size, 1=lossless), 'alpha_quality'=alpha quality 0..1 (-1=use 'rgb_quality', 0=smallest size, 1=lossless)
   Bool ExportWEBP(  File &f   , Flt rgb_quality=-1, Flt alpha_quality=-1)C; // export as WEBP to   file, false on fail, 'rgb_quality'=color quality 0..1 (-1=default, 0=smallest size, 1=lossless), 'alpha_quality'=alpha quality 0..1 (-1=use 'rgb_quality', 0=smallest size, 1=lossless)
   Bool ImportTGA (C Str  &name                                          ) ; // import    TGA  from file, false on fail
   Bool ImportTGA (  File &f                                             ) ; // import    TGA  from file, false on fail
   Bool ExportTGA (C Str  &name                                          )C; // export as TGA  to   file, false on fail
   Bool ExportTGA (  File &f                                             )C; // export as TGA  to   file, false on fail
   Bool ImportTIF (C Str  &name                                          ) ; // import    TIF  from file, false on fail
   Bool ImportTIF (  File &f                                             ) ; // import    TIF  from file, false on fail
   Bool ExportTIF (C Str  &name, Flt compression_level=-1                )C; // export as TIF  to   file, false on fail, 'compression_level'=0..1 (-1=default, 0=fast/biggest size, 1=slow/smallest size)
   Bool ExportTIF (  File &f   , Flt compression_level=-1                )C; // export as TIF  to   file, false on fail, 'compression_level'=0..1 (-1=default, 0=fast/biggest size, 1=slow/smallest size)
   Bool ImportDDS (C Str  &name                                          ) ; // import    DDS  from file, false on fail
   Bool ImportDDS (  File &f                                             ) ; // import    DDS  from file, false on fail
   Bool ExportDDS (C Str  &name                                          )C; // export as DDS  to   file, false on fail
   Bool ImportPSD (C Str  &name                                          ) ; // import    PSD  from file, false on fail
   Bool ImportPSD (  File &f                                             ) ; // import    PSD  from file, false on fail
   Bool ImportICO (C Str  &name                                          ) ; // import    ICO  from file, false on fail
   Bool ImportICO (  File &f                                             ) ; // import    ICO  from file, false on fail
   Bool ExportICO (C Str  &name, Bool as_png=false                       )C; // export as ICO  to   file, false on fail, 'as_png'=if use PNG compression (file size will be smaller, however the icon may not be readable on systems prior to Windows Vista)
   Bool ExportICO (  File &f   , Bool as_png=false                       )C; // export as ICO  to   file, false on fail, 'as_png'=if use PNG compression (file size will be smaller, however the icon may not be readable on systems prior to Windows Vista)
   Bool ExportICNS(C Str  &name, Bool as_png=false                       )C; // export as ICNS to   file, false on fail, 'as_png'=if use PNG compression (file size will be smaller, however the icon may not be readable on systems prior to Mac OS 10.7)
   Bool ExportICNS(  File &f   , Bool as_png=false                       )C; // export as ICNS to   file, false on fail, 'as_png'=if use PNG compression (file size will be smaller, however the icon may not be readable on systems prior to Mac OS 10.7)

  ~Image() {del();}
   Image();
   Image(Int w, Int h, Int d, IMAGE_TYPE type, IMAGE_MODE mode, Int mip_maps=0); // create with specified parameters, Exit on fail, 'mip_maps'=number of mip-maps (0=autodetect)

private:
   Byte  _mms, _samples, _lmm, _lcf, _lock_mode, _byte_pp, _partial;
   Int   _lock_count;
   UInt  _pitch, _pitch2;
   VecI  _size, _hw_size, _lock_size;
   Vec   _part;
   Byte *_data, *_open_gl_es_data;
   Ptr   _surf, _base, _txtr, _vol, _cube, _rdsv;
   IMAGE_TYPE _type, _hw_type;
   IMAGE_MODE _mode;
   NO_COPY_CONSTRUCTOR(Image);
};
/******************************************************************************/
DECLARE_CACHE(Image, Images, ImagePtr); // 'Images' cache storing 'Image' objects which can be accessed by 'ImagePtr' pointer
/******************************************************************************/
struct ImageHeader
{
   VecI       size;
   Int        mip_maps;
   IMAGE_TYPE type;
   IMAGE_MODE mode;

   ImageHeader() {size.zero(); mip_maps=0; type=IMAGE_NONE; mode=IMAGE_2D;}
};
Bool ImageLoadHeader(  File &f   , ImageHeader &header); // load image header from file, this method is faster than 'Image.load' if you're not interested in the Image data, but only in information about it. After reading the header, 'f' file position is reset to the same place before making this call, false on fail
Bool ImageLoadHeader(C Str  &name, ImageHeader &header); // load image header from file, this method is faster than 'Image.load' if you're not interested in the Image data, but only in information about it.                                                                                                 false on fail
/******************************************************************************/
IMAGE_TYPE BytesToImageType(int byte_pp); // get IMAGE_TYPE needed to store 'byte_pp' amount of bytes per pixel, which is 1->IMAGE_I8, 2->IMAGE_I16, 3->IMAGE_I24, 4->IMAGE_I32, other->IMAGE_NONE

Int  GetPVRTCQuality(           ); // get PVRTC compression quality, 0..4
void SetPVRTCQuality(Int quality); // set PVRTC compression quality, 0..4
/******************************************************************************/

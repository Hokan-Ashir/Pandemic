/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'FontMake' to create a base font image.

   Use 'Font' to:
      -create final fonts out of the base font image
      -draw the text

/******************************************************************************/
#define FONT_WIDTH_TEST 8
/******************************************************************************/
enum CHARSET_TYPE
{
   CHARSET_ANSI       =0  ,
   CHARSET_DEFAULT    =1  ,
   CHARSET_EAST_EUROPE=238,
   CHARSET_RUSSIAN    =204,
   CHARSET_SHIFT_JIS  =128,
   CHARSET_HANGEUL    =129,
   CHARSET_HANGUL     =129,
   CHARSET_GB_2312    =134,
   CHARSET_CHINESE    =136,
   CHARSET_GREEK      =161,
   CHARSET_ARABIC     =178,
   CHARSET_TURKISH    =162,
   CHARSET_VIETNAMESE =163,
   CHARSET_THAI       =222,
   CHARSET_BALTIC     =186,
   CHARSET_JOHAB      =130,
   CHARSET_HEBREW     =177,
   CHARSET_MAC        =77 ,
   CHARSET_SYMBOL     =2  ,
   CHARSET_OEM        =255,
};
/******************************************************************************/
enum SPACING_MODE // Text Spacing Mode
{
   SPACING_CONST, // constant spacing, characters are aligned by a constant factor taken from TextStyle::space
   SPACING_FAST , // fast     spacing, characters are aligned by their average width (1        width test  per character)
   SPACING_NICE , // nice     spacing, characters are aligned by their         width (multiple width tests per character performed on different parts of the character)
};
/******************************************************************************/
struct Font
{
   enum MODE
   {
      DEFAULT  , // anti-aliased
      SMOOTHED , // anti-aliased with extra smoothing but no sub-pixel precision
      SUB_PIXEL, // anti-aliased with extra smoothing and    sub-pixel precision, Warning: enabling this option will increase font quality only if it will be drawn with correct scale (in other case font quality will be worse), using this option also disables font shadows
   };
   struct Params // font creation parameters
   {
      Str          system_font    , // name of the font
                   characters     ; // characters to include in the font
      Bool         shadow_diagonal; // if set shadows in diagonal mode            , true/false
      Byte         mip_maps       ; // amount of desired mip maps for the textures,   0..8 (0=autodetect and create full mip-map chain)
      Int          size           ; // font size (in pixels)                      ,   1..Inf
      Flt          shadow_blur    , // amount of shadow blurring                  ,   0..1
                   shadow_opacity , // shadow opacity                             ,   0..1
                   shadow_spread  , // shadow spread                              ,   0..1
                   weight         , // font weight                                ,   0..1
                   minimum_filter ; // distance in pixels for the minimum filter  ,   0..1
      Int          max_image_size ; // maximum allowed image size to be generated
      MODE         mode           ;
      IMAGE_TYPE   image_type     ; // image format                               , recommended types are: DXT5 (slightly worse quality on shadows), L8A8 (full quality but 2x bigger size than DXT5), PVRTC (can be used on iOS to reduce size, this wil automatically disable mip-maps since font mip-maps in PVRTC format have too low quality)
      CHARSET_TYPE charset        ; // charset type

      Params() {shadow_diagonal=true; mip_maps=3; size=48; shadow_blur=0.04f; shadow_opacity=1.0f; shadow_spread=0.0f; weight=0; minimum_filter=0; max_image_size=2048; mode=DEFAULT; image_type=IMAGE_DXT5; charset=CHARSET_DEFAULT;}

      void adjustForOpenGLES(IMAGE_TYPE type=IMAGE_DXT5) {image_type=type; if(mip_maps!=1)mip_maps=0; MIN(max_image_size, 2048);} // OpenGL ES requires a full chain of mip-maps (however when using PVRTC mip-maps will be automatically disabled), maximum image size is 2048
   };

   // manage
   Bool create(C Params &params); // create font using specified 'params', false on fail

   // get
   Bool is    ()C {return _height>0;} // if  is a valid font
   Int  height()C {return _height  ;} // get font height in pixels

   Bool hasChar(Char8 c)C; // if font supports 'c' character
   Bool hasChar(Char  c)C; // if font supports 'c' character

   UInt memUsage()C; // get approximate memory size usage of the font images

   Int charWidth(CChar  c)C; // get width of character (in pixels)
   Int charWidth(CChar8 c)C; // get width of character (in pixels)

   Int textWidth(SPACING_MODE spacing, CChar  *text, Int max_length=-1)C; // get width of text (in pixels)
   Int textWidth(SPACING_MODE spacing, CChar8 *text, Int max_length=-1)C; // get width of text (in pixels)

   // operations
   Font& freeOpenGLESData   (                                   ); // this method is used only under OpenGL ES (on other platforms it is ignored), the method frees the software copy of the GPU data which increases available memory, however after calling this method the data can no longer be accessed on the CPU (can no longer be locked or saved to file)
   Bool  optimizeForOpenGLES(IMAGE_TYPE type=IMAGE_DXT5         ); // this method will optimize the font for OpenGL ES, convert textures to desired type (recommended DXT5, L8A8 or PVRTC4-iOS), resize and generate mip maps if needed, returns true if any changes were applied to the font, and false if no changes were applied
   Font& replace            (Char src, Char dest, Bool permanent); // replace original 'src' character to be drawn as the 'dest' character, 'permanent'=if apply the change permanently (will be included in 'save') or just temporarily

   // io
   void operator=(C Str &name) ; // load, Exit  on fail
   Bool save     (C Str &name)C; // save, false on fail
   Bool load     (C Str &name) ; // load, false on fail

   Bool save(File &f)C; // save, false on fail
   Bool load(File &f) ; // load, false on fail

   Font& del(); // delete manually
   Font();

   // direct access to font character data
      struct Chr // single character data
      {
         Char chr   ; // character which this data is assigned to
         Byte image , // image index from the 'images' container that includes this character
              offset, // vertical offset - number of pixels that need to be added from the top when drawing this character
              width , // full width  of this character in pixels (this does not include the shadow padding)
              height, // full height of this character in pixels (this does not include the shadow padding and 'offset')
              width2[FONT_WIDTH_TEST][2];
         Rect tex   ; // texture coordinates covering the font pixels in the image (this already includes the shadow padding)
      };

      C Mems<Chr  >& chrs  ()C {return _chrs  ;} // get list of characters supported in this Font
      C Mems<Image>& images()C {return _images;} // get list of images used for storing character data, these images have data packed in channels: Green=Shadow Intensity, Alpha=Character Intensity, Red/Blue=Unused, please keep in mind that these images are IMAGE_2D hardware textures with possibly compressed texture formats, which are not suitable for software processing, when wanting to do software drawing it's recommended to first copy the images to separate software copies

      Int charIndex(Char8 c)C; // get 'c' character index in the 'chrs' container, -1 if it's not included
      Int charIndex(Char  c)C; // get 'c' character index in the 'chrs' container, -1 if it's not included

      // get character image shadow padding - amount of pixels on each side that is used only for shadows and does not contain the actual font char pixels
      Int paddingL()C {return _padd.x;} // get left   padding
      Int paddingT()C {return _padd.y;} // get top    padding
      Int paddingR()C {return _padd.z;} // get right  padding
      Int paddingB()C {return _padd.w;} // get botton padding

private:
   Bool        _sub_pixel;
   Byte        _height;
   VecB4       _padd;
   UShort      _char_to_font[  0x100],
               _wide_to_font[0x10000];
   Mems<Chr  > _chrs;
   Mems<Image> _images;
};
/******************************************************************************/
DECLARE_CACHE(Font, Fonts, FontPtr); // 'Fonts' cache storing 'Font' objects which can be accessed by 'FontPtr' pointer
/******************************************************************************/

/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Video' to display video files.

/******************************************************************************/
enum VIDEO_CODEC
{
   VIDEO_NONE  ,
   VIDEO_THEORA, // doesn't support random seeking
   VIDEO_VP9   , // doesn't support random seeking
};
/******************************************************************************/
struct Video // Video Decoder
{
   // manage
   void del   (                                                ); // delete manually
   Bool create(C Str &name, Bool loop=false, Bool texture=false); // create from 'name' file name   , 'loop'=if this video should be looped, 'texture'=if video will be accessable as a texture through the 'image' method (warning: this will slow down video processing, if you wish to just draw the video on screen then don't enable this), false on fail
   Bool create(C UID &id  , Bool loop=false, Bool texture=false); // create from 'id'   file name id, 'loop'=if this video should be looped, 'texture'=if video will be accessable as a texture through the 'image' method (warning: this will slow down video processing, if you wish to just draw the video on screen then don't enable this), false on fail

   // get
   Bool        is       ()C {return _codec!=VIDEO_NONE;} // if  created
   VIDEO_CODEC codec    ()C {return _codec            ;} // get video codec
   CChar8*     codecName()C;                             // get video codec name
   Flt         time     ()C {return _time             ;} // get current time position of the video
   Int         width    ()C {return _w                ;} // get video width
   Int         height   ()C {return _h                ;} // get video height
   Flt         aspect   ()C {return Flt(_w)/_h        ;} // get video aspect ratio "width/height"
   Int         bitRate  ()C {return _br               ;} // get video bit rate
   Flt         fps      ()C {return _fps              ;} // get video frames per second

 C Image& image()C; // get video as image, this will be valid only if the video was created with the 'texture' parameter set to true, you may no longer use this image once the video got deleted

   // update
   Bool update(Flt time); // update to 'time' video time, returns false when finished playing, some codecs don't support random seeking, only continuous playback is supported

   // fit
   Rect fit(C Rect &rect, FIT_MODE fit=FIT_FULL)C {return Fit(aspect(), rect, fit);} // get rectangle that can be used for drawing of the video to the 'rect' destination while preserving video proportions according to specified 'fit' mode

   // draw
   void drawFs (FIT_MODE fit=FIT_FULL)C; // draw full screen
   void drawFit(C Rect &rect         )C; // draw to fit best in given space, while preserving video proportions
   void draw   (C Rect &rect         )C; // draw to specified rectangle

  ~Video() {del();}
   Video();

private:
   Enum1<VIDEO_CODEC> _codec;
   Bool  _loop, _texture;
   Int   _w, _h, _br;
   Flt   _time, _time_past, _fps;
   File  _file;
   Image _lum, _u, _v, _tex, *_tex_ptr;
   Ptr   _d;
   NO_COPY_CONSTRUCTOR(Video);
};
/******************************************************************************/
CChar8* CodecName(VIDEO_CODEC codec);
/******************************************************************************/

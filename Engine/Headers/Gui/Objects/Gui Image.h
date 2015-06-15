/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
const_mem_addr STRUCT(GuiImage , GuiObj) // Gui Image !! must be stored in constant memory address !!
//{
   Bool       fit       ; // if maintain proportions of the image, default=false
   ALPHA_MODE alpha_mode; // alpha blending mode                 , default=ALPHA_BLEND
   Color      rect_color, // rectangle color                     , default=Gui.borderColor
              color     , // image     color                     , default=WHITE
              color_add ; // image     color add                 , default=TRANSPARENT
   ImagePtr   image     ; // image

   // manage
   GuiImage& del   (                                        );                                      // delete
   GuiImage& create(                  C ImagePtr &image=NULL);                                      // create
   GuiImage& create(C Rect     &rect, C ImagePtr &image=NULL) {create(image).rect(rect); return T;} // create
   GuiImage& create(C GuiImage &src                         );                                      // create from 'src'

   // set
   GuiImage& set(C ImagePtr &image); // set image

   // main
   virtual void draw(C GuiPC &gpc); // draw object

  ~GuiImage() {del();}
   GuiImage();

protected:
   virtual void save(File &f, CChar *path=NULL)C;
   virtual Bool load(File &f, CChar *path=NULL) ;

   NO_COPY_CONSTRUCTOR(GuiImage);
};
/******************************************************************************/
